#ifndef _PIN_H_
#define _PIN_H_

#include <string>

class Pin
{
public:
	Pin();
	Pin( std::string n, std::string s, int p );
	Pin( const Pin& rhs );
	Pin( const Pin&& rhs );
	Pin& operator=(const Pin& rhs);
	int getValue() const;
	void update();
	void setValue( int value );
	std::string getName() const;

private:
	std::string name;
	std::string status;
	int port;
	int value;
};

#endif