#include "parser.h"

#include <cassert>

#include "../utils/utils.h"
#include "../tables/symboltable.h"
#include "../tables/chantable.h"
#include "../tables/clocktable.h"
#include "../tables/localtable.h"
#include "../tables/pintable.h"
#include "stringparser.h"

void Parser::generateFSM(TimedAutomata* timedAutomata)
{
	pugi::xml_node templates = doc.child("nta");
	for ( const pugi::xml_node node : templates )
	{
		if ( std::string(node.name()) == "template" )
		{
			timedAutomata->addTemplate( this->processTemplate( node ) );
		}
		if ( std::string(node.name()) == "declaration" )
		{
			StringParser parser(node.child_value());
			ChanTable::getInstance().addEntries( parser.generateChannels() );
			ClockTable::getInstance().addEntries( parser.generateClocks() );
			PinTable::getInstance().addEntries( parser.generatePins() );
			SymbolTable::getInstance().addEntries( parser.generateSymbols() );
		}
		if ( std::string(node.name()) == "system" )
		{
			StringParser parser(node.child_value());
			timedAutomata->addSystems( parser.generateSystems() ); 
		}
	}
}

Template Parser::processTemplate(const pugi::xml_node& nodes )
{
	Template rez;
	for( const pugi::xml_node node : nodes )
	{
		if ( std::string(node.name()) == "transition" )
		{
			rez.addTransition( this->processTransition(node) );
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

State Parser::processCurrentState(const pugi::xml_node& node)
{
	std::string id = node.attribute("ref").value();
	State state(id);
	return state;
}

Transition Parser::processTransition(const pugi::xml_node& node)
{
	State source( node.child("source").attribute("ref").value() );
	State destination( node.child("target").attribute("ref").value() );
	Transition tranz(source,destination);
	this->processLabels( &tranz, node );
	return tranz;
}

void Parser::processLabels(Transition* t, const pugi::xml_node& node)
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
				if ( ex.isValidGuard() )
				{
					t->addGuard( ex );
					display(DebugMessagePriority::Parser, "Guard founded: ", ex, "\n" );
				}
				else
				{
					assert(!"Invalid guard!");
				}
			}
		}
		if ( ( it->name() == std::string("label") ) && ( it->attribute("kind").value() == std::string("assignment") ) )
		{
			std::string data = it->child_value();
			std::vector<std::string> expressions = splitString(data,",");
			for ( auto it : expressions )
			{
				Expression ex(it);
				if ( ex.isValidUpdate() )
				{
					t->addUpdate( ex );
					display(DebugMessagePriority::Parser, "Update founded: ", ex, "\n" );
				}
				else
				{
					assert(!"Invalid update");
				}
			}
		}
		if ( (it->name() == std::string("label") ) && ( it->attribute("kind").value() == std::string("synchronisation") ) )
		{
			Sync rez( it->child_value() );
			display(DebugMessagePriority::Parser, "Syncs founded: ", rez, "\n" );
			t->setSync( rez );
		}
		if ( (it->name() == std::string("label") ) && ( it->attribute("kind").value() == std::string("select") ) )
		{
			std::string data( it->child_value() );
			std::string name( data.substr(0, data.find(":") - 1 ) );
			t->addSelect( name );
		}
	}
}

std::string Parser::processName(const pugi::xml_node& node)
{
	std::string name = node.child_value();
	return name;
}