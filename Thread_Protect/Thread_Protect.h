#pragma once
#include <string>
#include <Windows.h>
#include "Singletone.h"
#include <map>
#include <list>
#include <string>


typedef void(*createth)();
struct ThreadMap {
	ThreadMap() : id(0), name("dd") {}
	ThreadMap(HANDLE newthreadhw, DWORD newthreadid, createth newcreateths, int newId, std::string newName)
		: threadhw(newthreadhw), threadid(newthreadid), createths(newcreateths), id(newId), name(newName) {}

	HANDLE threadhw;
	DWORD threadid;
	//LPVOID createth;
	int id;
	std::string name;
	createth createths;

};

class Thread_Protect : public CppSingleton <Thread_Protect>
{
public:
	std::map<int, ThreadMap> ThreadMaps;
	Thread_Protect();
	virtual ~Thread_Protect();


	int InsertThread(ThreadMap* tm, std::list<std::string>* li);
	void MapStart();
	void MapStop();
private:
	int Threadcnt;
	static void MapRun(std::map<int, ThreadMap>* TM);

};