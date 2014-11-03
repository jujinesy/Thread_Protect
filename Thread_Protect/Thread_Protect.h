#pragma once
#include <string>
#include <Windows.h>
#include "Singletone.h"
#include <map>
#include <list>
#include <string>

typedef void(*PFUNCTION)();
struct ThreadMap {
	//ThreadMap() : id(0), name("dd") {}
	ThreadMap() {}
	ThreadMap(int newThreadNUMBER, HANDLE newThreadHANDLE, DWORD newThreadTID, PFUNCTION newThreadFUNCTION, std::string newThreadNAME)
	: ThreadNUMBER(newThreadNUMBER), ThreadHANDLE(newThreadHANDLE), ThreadTID(newThreadTID), ThreadFUNCTION(newThreadFUNCTION), ThreadNAME(newThreadNAME) {}

	int ThreadNUMBER;
	HANDLE ThreadHANDLE;
	DWORD ThreadTID;	
	PFUNCTION ThreadFUNCTION;
	std::string ThreadNAME;
};

class Thread_Protect : public CppSingleton <Thread_Protect>
{
public:
	Thread_Protect();
	virtual ~Thread_Protect();
	int InsertThread(ThreadMap* tm, std::list<std::string>* li);
	void MapStart();
	void MapStop();	
private:
	static void MapRun(std::map<int, ThreadMap>* TM);
	std::map<int, ThreadMap> ThreadMaps;
	HANDLE MainhThread;
	int Threadcnt;
};