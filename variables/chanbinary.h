#ifndef _CHAN_BINARY_H_
#define _CHAN_BINARY_H_

#include <string>
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

	Chan::ChanType getType() const;
	~ChanBinary();

private:
};

#endif