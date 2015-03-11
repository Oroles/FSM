#include "parser.h"

#include <memory>

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
	}
}

Module Parser::processModule(const pugi::xml_node& nodes)
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
	return tranz;
}

std::string Parser::processName(const pugi::xml_node& node)
{
	std::string name = node.child_value();
	return name;
}