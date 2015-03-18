#ifndef _SYNC_H_
#define _SYNC_H_

#include <string>

class Sync
{
public:
	Sync(const std::string& n);
	Sync(const Sync& rhs);
	Sync(Sync&& rhs);
	Sync& operator=(const Sync& rhs);
	bool isSync();
private:
	enum class Action{ Set, Check, Unknown };

	std::string name;
	Action lastAction = Action::Unknown;
};

#endif