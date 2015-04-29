#ifndef _PLAIN_DATA_H_
#define _PLAIN_DATA_H_

/*
The purpose of this class is to transmit information from string parser to symbol table
*/

struct PlainData
{
	std::string name;
	int size;
	int defaultValue;
};

#endif