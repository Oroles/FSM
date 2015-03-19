#ifndef _CHAN_TABLE_H_
#define _CHAN_TABLE_H_

#include <map>
#include <vector>
#include "../variables/chan.h"

class ChanTable
{
public:
	static ChanTable& getInstance();
	void addEntry(const Chan& c);
	void addEntries( const std::vector<Chan>& v);

	bool isSenderSync(std::string name);
	bool isReceiverSync(std::string name);
	void wantSender(std::string name);
	void wantReceiver(std::string name);

private:
	ChanTable();
	ChanTable(const ChanTable& rhs) = delete;
	ChanTable(ChanTable&& rhs) = delete;
	ChanTable& operator=(const ChanTable& rhs) = delete;

	std::map<std::string,Chan> table;
};

#endif