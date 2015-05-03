#ifndef _SYNC_H_
#define _SYNC_H_

#include <string>
#include <iostream>

class Sync
{
public:
	Sync();
	Sync(const std::string& n);
	Sync(const Sync& rhs);
	Sync(Sync&& rhs);
	const Sync& operator=(const Sync& rhs);
	bool isSync() const;
	std::string getName() const;
private:
	friend std::ostream& operator<<(std::ostream&, const Sync& s);

	std::string name;
};

#endif