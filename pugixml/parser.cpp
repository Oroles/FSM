#include "parser.h"

#include "../utils/utils.h"
#include "stringparser.h"

void Parser::generateFSM(FSM* fsm)
{
	pugi::xml_node modules = doc.child("nta");
	for ( const pugi::xml_node node : modules )
	{
		if ( std::string(node.name()) == "template" )
		{
			fsm->addModule( this->processModule( node ) );
		}
		if ( std::string(node.name()) == "declaration" )
		{
			StringParser parser(node.child_value());
			fsm->addChannels( parser.generateChannels() );
			fsm->addClocks( parser.generateClocks() );
		}
		if ( std::string(node.name()) == "system" )
		{
			StringParser parser(node.child_value());
			parser.generateModules();
		}
	}
}

Module Parser::processModule(const pugi::xml_node& nodes )
{
	Module rez;
	for( const pugi::xml_node node : nodes )
	{
		if ( std::string(node.name()) == "location" )
		{
			rez.addState( this->processState(node) );
		}
		if ( std::string(node.name()) == "transition" )
		{
			rez.addTranzition( this->processTranzition(node) );
		}
		if ( std::string(node.name()) == "init" )
		{
			rez.setCurrentState( this->processCurrentState(node) );
		}
		if ( std::string(node.name()) == "name" )
		{
			rez.setName( this->processName(node) );
		}
	}
	return rez;
}

State Parser::processState(const pugi::xml_node& node)
{
	std::string id = node.attribute("id").value();
	State state(id);
	return state;
}

State Parser::processCurrentState(const pugi::xml_node& node)
{
	std::string id = node.attribute("ref").value();
	State state(id);
	return state;
}

Tranzition Parser::processTranzition(const pugi::xml_node& node)
{
	State source( node.child("source").attribute("ref").value() );
	State destination( node.child("target").attribute("ref").value() );
	Tranzition tranz(source,destination);
	tranz.setGuards( this->processGuards(node) );
	tranz.setSyncs( this->processSyncs(node) );
	return tranz;
}

std::vector<Expression> Parser::processGuards(const pugi::xml_node& node)
{
	std::vector<Expression> rez;
	for ( auto it = node.begin(); it != node.end(); ++it )
	{
		if ( (it->name() == std::string("label") ) && ( it->attribute("kind").value() == std::string("guard") ) )
		{
			std::string expressions = it->child_value();
			Expression ex( expressions );
			rez.push_back( ex );
			display(DebugMessagePriority::Parser, "Guard founded: ", ex );
		}
	}
	return rez;
}

std::vector<std::string> Parser::processSyncs(const pugi::xml_node& node)
{
	std::vector<std::string> rez;
	for ( auto it = node.begin(); it != node.end(); ++it )
	{
		if ( (it->name() == std::string("label") ) && ( it->attribute("kind").value() == std::string("synchronisation") ) )
		{
			std::string expressions = it->child_value();
			rez.push_back( expressions );
			display(DebugMessagePriority::Parser, "Syncs founded: ", expressions, "\n" );
		}
	}
	return rez;
}

std::string Parser::processName(const pugi::xml_node& node)
{
	std::string name = node.child_value();
	return name;
}