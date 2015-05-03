#ifndef _CHAN_BINARY_H_
#define _CHAN_BINARY_H_

#include <string>
#include <iostream>
#include <cassert>
#include "chan.h"

class ChanBinary : public Chan
{
public:
	ChanBinary(const std::string n);
	ChanBinary(const ChanBinary& rhs);
	ChanBinary(ChanBinary&& rhs);
	const ChanBinary& operator=(const ChanBinary& rhs);
	bool operator==(const ChanBinary& rhs);
	friend std::ostream& operator<<(std::ostream& o, const ChanBinary& c);

	bool isSenderSync();
	bool isReceiverSync();
	Chan::ChanType getType() const;

	~ChanBinary();

private:
	void wantSender();
	void wantReceiver();

	enum class Turn { Sender, Receiver };
	Turn turn;
	bool wcs;
	bool wcr;
	bool acs;
	bool acr;
	
};

#endif