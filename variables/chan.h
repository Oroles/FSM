#ifndef _CHAN_H_
#define _CHAN_H_

#include <string>
#include <iostream>
#include <cassert>

class Chan
{
public:
	Chan();
	Chan( std::string n);
	Chan(const Chan& rhs);
	Chan(Chan&& rhs);
	Chan& operator=(const Chan& rhs);
	bool operator==(const Chan& rhs);
	friend std::ostream& operator<<(std::ostream& o, const Chan& c);

	std::string getName() const;
	bool isSenderSync();
	bool isReceiverSync();
	void wantSender();
	void wantReceiver();

	~Chan();

private:
	enum class Turn { Sender, Receiver };
	std::string name;
	Turn turn;
	bool wcs;
	bool wcr;
	bool acs;
	bool acr;
	
};

#endif