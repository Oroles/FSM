#ifndef _CHAN_URGENT_H_
#define _CHAN_URGENT_H_

#include <string>
#include "chan.h"

class ChanUrgent : public Chan
{
public:
	ChanUrgent(std::string n);
	ChanUrgent(const ChanUrgent& rhs);
	ChanUrgent(ChanUrgent&& rhs);
	const ChanUrgent& operator=(const ChanUrgent& rhs);
	bool operator==(const ChanUrgent& rhs);

	friend std::ostream& operator<<(std::ostream& o, const ChanUrgent& rhs);

	Chan::ChanType getType() const;
	~ChanUrgent();
};

#endif