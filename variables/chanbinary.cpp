#include "chanbinary.h"

ChanBinary::ChanBinary( std::string n) : Chan(n), turn(ChanBinary::Turn::Sender), wcs(false), wcr(false), acs(false), acr(false)
{
	assert(n.size() != 0);
}

ChanBinary::ChanBinary(const ChanBinary& rhs) : Chan(rhs.name), turn(rhs.turn), wcs(rhs.wcs), wcr(rhs.wcr), acs(rhs.acs), acr(rhs.acr)
{
	assert(name.size() != 0);
}

ChanBinary::ChanBinary(ChanBinary&& rhs) : Chan(std::move(rhs.name)), turn(std::move(rhs.turn)), wcs(std::move(rhs.wcs)),
						 wcr(std::move(rhs.wcr)), acs(std::move(rhs.acs)), acr(std::move(rhs.acr))
{
	
}

ChanBinary::~ChanBinary()
{
	
}

Chan::ChanType ChanBinary::getType() const
{
	return Chan::ChanType::Binary;
}

const ChanBinary& ChanBinary::operator=(const ChanBinary& rhs)
{
	Chan::operator=(rhs);
	turn = rhs.turn;
	wcs = rhs.wcs;
	wcr = rhs.wcr;
	acs = rhs.acs;
	acr = rhs.acr;
	return *this;
}

bool ChanBinary::operator==(const ChanBinary& rhs)
{
	return name == rhs.name;
}

std::ostream& operator<<(std::ostream& o, const ChanBinary& c)
{
	o << "ChanBinary " << c.getName();
	return o;
}

bool ChanBinary::isSenderSync()
{
	this->wantSender();
	if ( ( wcs == true ) && ( wcr == true ) )
	{
		if ( turn == ChanBinary::Turn::Sender )
		{
			wcs = false;
			turn = ChanBinary::Turn::Receiver;
			acr = true;
			return true;
		}
	}
	if ( acs == true )
	{
		turn = ChanBinary::Turn::Receiver;
		acs = false;
		wcs = false;
		return true;
	}
	return false;
}

bool ChanBinary::isReceiverSync()
{
	this->wantReceiver();
	if ( ( wcs == true ) && ( wcr == true ) )
	{
		if ( turn == ChanBinary::Turn::Receiver )
		{
			wcr = false;
			turn = ChanBinary::Turn::Sender;
			acs = true;
			return true;
		}
	}
	if ( acr == true )
	{
		turn = ChanBinary::Turn::Sender;
		acr = false;
		wcr = false;
		return true;
	}
	return false;
}

void ChanBinary::wantSender()
{
	wcs = true;
}

void ChanBinary::wantReceiver()
{
	wcr = true;
}
