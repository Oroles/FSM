#ifndef _CHAN_H_
#define _CHAN_H_

#include <iostream>
#include <string>

class Chan
{
public:
	enum class ChanType : int { Binary, Broadcast, Urgent };
	Chan(const std::string n);
	Chan(const Chan& c);
	Chan(Chan&& c);
	const Chan& operator=(const Chan& c);
	bool operator==(const Chan& c);
	friend std::ostream& operator<<(std::ostream& o, const Chan& c);

	virtual ~Chan();
	virtual ChanType getType() const = 0;
	std::string getName() const;

protected:
	std::string name;
};

#endif