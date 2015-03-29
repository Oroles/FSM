#include "parser.h"

#include "../utils/utils.h"
#include "../tables/symboltable.h"
#include "../tables/chantable.h"
#include "../tables/clocktable.h"
#include "../tables/localtable.h"
#include "stringparser.h"

void Parser::generateFSM(FSM* fsm)
{
	pugi::xml_node modules = doc.child("nta");
	for ( const pugi::xml_node node : modules )
	{
		if ( std::string(node.name()) == "template" )
		{
			fsm->addTemplate( this->processTemplate( node ) );
		}
		if ( std::string(node.name()) == "declaration" )
		{
			StringParser parser(node.child_value());
			ChanTable::getInstance().addEntries( parser.generateChannels() );
			ClockTable::getInstance().addEntries( parser.generateClocks() );
			SymbolTable::getInstance().addEntries( parser.generateSymbols() );
		}
		if ( std::string(node.name()) == "system" )
		{
			StringParser parser(node.child_value());
			fsm->addModules( parser.generateModules() ); 
		}
	}
}

Module Parser::processTemplate(const pugi::xml_node& nodes )
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
		if ( std::string(node.name()) == "declaration" )
		{
			StringParser parser( node.child_value() );
			LocalTable::getInstance().addEntries(rez.getName(), parser.generateSymbols() );
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
	this->processLabels( &tranz, node );
	return tranz;
}

void Parser::processLabels(Tranzition* t, const pugi::xml_node& node)
{
	for ( auto it = node.begin(); it != node.end(); ++it )
	{
		if ( (it->name() == std::string("label") ) && ( it->attribute("kind").value() == std::string("guard") ) )
		{
			std::string data = it->child_value();
			std::vector<std::string> expressions = splitString(data,"&&");
			for ( auto it : expressions )
			{
				Expression ex(it);
				t->addGuard( ex );
				display(DebugMessagePriority::Parser, "Guard founded: ", ex, "\n" );	
			}
		}
		if ( ( it->name() == std::string("label") ) && ( it->attribute("kind").value() == std::string("assignment") ) )
		{
			std::string data = it->child_value();
			std::vector<std::string> expressions = splitString(data,",");
			for ( auto it : expressions )
			{
				Expression ex(it);
				t->addUpdate( ex );
				display(DebugMessagePriority::Parser, "Update founded: ", ex, "\n" );
			}
		}
		if ( (it->name() == std::string("label") ) && ( it->attribute("kind").value() == std::string("synchronisation") ) )
		{
			Sync rez( it->child_value() );
			display(DebugMessagePriority::Parser, "Syncs founded: ", rez, "\n" );
			t->setSync( rez );
		}
	}
}

std::string Parser::processName(const pugi::xml_node& node)
{
	std::string name = node.child_value();
	return name;
}