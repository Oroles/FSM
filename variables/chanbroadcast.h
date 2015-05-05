#ifndef _CHAN_BROADCAST_H_
#define _CHAN_BROADCAST_H_

#include <string>
#include "chan.h"

class ChanBroadcast : public Chan
{
public:
	ChanBroadcast(const std::string n);
	ChanBroadcast(const ChanBroadcast& c);
	ChanBroadcast(ChanBroadcast&& c);
	const ChanBroadcast& operator=(const ChanBroadcast& c);
	bool operator==(const ChanBroadcast& c);
	friend std::ostream& operator<<(std::ostream& o, const ChanBroadcast& c);

	Chan::ChanType getType() const;

	~ChanBroadcast();

private:
};

#endif