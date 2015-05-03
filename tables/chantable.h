#ifndef _CHAN_TABLE_H_
#define _CHAN_TABLE_H_

#include <map>
#include <vector>
#include <memory>
#include "../variables/chan.h"

class ChanTable
{
public:
	static ChanTable& getInstance();
	void addEntries( const std::vector<std::shared_ptr<Chan> >& v);
	Chan::ChanType getType(std::string name);
	bool existsEntry( const std::string& name);
	bool isSenderSync(std::string name);
	bool isReceiverSync(std::string name);

private:
	ChanTable();
	ChanTable(const ChanTable& rhs) = delete;
	ChanTable(ChanTable&& rhs) = delete;
	ChanTable& operator=(const ChanTable& rhs) = delete;

	std::map<std::string,std::shared_ptr<Chan> > table;
};

#endif