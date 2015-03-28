#include "chan.h"

Chan::Chan()
{
}

Chan::Chan( std::string n) : name(n), turn(Chan::Turn::Sender), wcs(false), wcr(false), acs(false), acr(false)
{
	assert(n.size() != 0);
}

Chan::Chan(const Chan& rhs) : name(rhs.name), turn(rhs.turn), wcs(rhs.wcs), wcr(rhs.wcr), acs(rhs.acs), acr(rhs.acr)
{
	assert(name.size() != 0);
}

Chan::Chan(Chan&& rhs) : name(std::move(rhs.name)), turn(std::move(rhs.turn)), wcs(std::move(rhs.wcs)),
						 wcr(std::move(rhs.wcr)), acs(std::move(rhs.acs)), acr(std::move(rhs.acr))
{
	
}

Chan::~Chan()
{
	
}

Chan& Chan::operator=(const Chan& rhs)
{
	name=rhs.name;
	turn = rhs.turn;
	wcs = rhs.wcs;
	wcr = rhs.wcr;
	acs = rhs.acs;
	acr = rhs.acr;
	return *this;
}

bool Chan::operator==(const Chan& rhs)
{
	return name == rhs.name;
}

std::string Chan::getName() const
{
	return name;
}

std::ostream& operator<<(std::ostream& o, const Chan& c)
{
	o << "Chan " << c.getName();
	return o;
}

bool Chan::isSenderSync()
{
	if ( ( wcs == true ) && ( wcr == true ) )
	{
		if ( turn == Chan::Turn::Sender )
		{
			wcs = false;
			turn = Chan::Turn::Receiver;
			acr = true;
			return true;
		}
	}
	if ( acs == true )
	{
		turn = Chan::Turn::Receiver;
		acs = false;
		wcs = false;
		return true;
	}
	return false;
}

bool Chan::isReceiverSync()
{
	if ( ( wcs == true ) && ( wcr == true ) )
	{
		if ( turn == Chan::Turn::Receiver )
		{
			wcr = false;
			turn = Chan::Turn::Sender;
			acs = true;
			return true;
		}
	}
	if ( acr == true )
	{
		turn = Chan::Turn::Sender;
		acr = false;
		wcr = false;
		return true;
	}
	return false;
}

void Chan::wantSender()
{
	wcs = true;
}

void Chan::wantReceiver()
{
	wcr = true;
}
