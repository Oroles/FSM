#include "observer.h"
#include "../utils/utils.h"

#include "template.h"
#include "../variables/chan.h"
#include "../tables/chantable.h"

void Observer::addObservable(Template* rhs)
{
	for ( auto& t : (*rhs) )
	{
		if ( t.hasSync() )
		{
			std::string channelName = t.getChannelName();
			if ( channelName.find("!") != std::string::npos )
			{
				senders.push_back( Data{  rhs,
										  std::shared_ptr<Edge>( std::make_shared<Edge>( t ) ),
										  std::string( channelName ) } );
			}
			else
			{
				receivers.push_back( Data{  rhs,
										  std::shared_ptr<Edge>( std::make_shared<Edge>( t ) ),
										  std::string( channelName ) } );
			}
		}
	}
}

bool Observer::isAvailable(const Template& temp, const Edge& trans, const std::string channelName )
{
	if ( channelName.find("!") != std::string::npos )
	{
		//search in receivers
		std::string chan = channelName.substr( 0, channelName.size() - 1 );
		if ( Chan::ChanType::Binary == ChanTable::getInstance().getType(chan) )
		{
			/* Here the channel is binary, so it has to find first receiver which can advance
			* and make him to advance, after that it has to advance. If doesn't find any receivers
			* it can not advance.
			*/
			chan += "?";
			for( auto& d : receivers )
			{
				if ( d.name == chan )
				{
					//we found the sender, we have to check if is available
					if (  d.temp->availableTransition( d.trans.get() ) == Edge::TransitionAvailableStatus::Available )
					{
						//now me make the other template to advance
						d.temp->channelAdvance( d.trans.get() );
						return true;
					}
				}
			}
		}
		else
		{
			/* Here the channel is broadcast so it has to go to all the other receivers
			* and check if they can advance, if they can they advance otherwise they stay
			* in the same state, and the sender after that it has to advance
			*/
			chan += "?";
			for( auto& d : receivers )
			{
				if ( d.name == chan )
				{
					//we found the sender, we have to check if is available
					if (  d.temp->availableTransition( d.trans.get() ) == Edge::TransitionAvailableStatus::Available )
					{
						//now me make the other template to advance
						d.temp->channelAdvance( d.trans.get() );
					}
				}
			}
			return true;
		}
	}
	else
	{
		//search in senders
		std::string chan = channelName.substr( 0, channelName.size() - 1 );
		if ( Chan::ChanType::Binary == ChanTable::getInstance().getType(chan) )
		{
			/* Here the channel binary so it has to check in senders if the sender is 
			* can advance, if so it make him to advance an after that it will advnace
			*/
			chan += "!";
			for( auto& d : senders )
			{
				if ( d.name == chan )
				{
					//we found the sender, we have to check if is available
					if (  d.temp->availableTransition( d.trans.get() ) == Edge::TransitionAvailableStatus::Available )
					{
						//now me make the other template to advance
						d.temp->channelAdvance( d.trans.get() );
						return true;
					}
				}
			}
		}
		else
		{
			/* Here the channel is broadcast so it has to find if the sender will advance, so 
			* when will find the sender it checks if can advance and if yes than it would
			* not make him to advance, because his turn will come in the current step and will advance
			* anyway therefore only the receiver will advance.
			*/
			chan += "!";
			for( auto& d : senders )
			{
				if ( d.name == chan )
				{
					//we found the sender, we have to check if is available
					if (  d.temp->availableTransition( d.trans.get() ) == Edge::TransitionAvailableStatus::Available )
					{
						//returns only true, the sender will advance later
						return true;
					}
				}
			}
		}
	}
	return false;
}