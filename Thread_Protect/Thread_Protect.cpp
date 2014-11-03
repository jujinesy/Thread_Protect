#include "Thread_Protect.h"
#include <thread>

Thread_Protect::Thread_Protect()
{
	Threadcnt = 0;
	Thread_Protect::MapStart();
}

Thread_Protect::~Thread_Protect()
{
}

int Thread_Protect::InsertThread(ThreadMap* tm, std::list<std::string>* li)
{
	std::list<std::string>::iterator i_list = li->begin();
	ThreadMap T;
	//(*li).size();
	//for (i_list = li->begin(); i_list != li->end(); i_list++)
	//{
	//	cout << *i_list << endl;	
	//}
	//for (std::string i : *li) {
	//	aa=std::stoul(i.c_str(), nullptr, 0);
	//}

	//스레드 정보를 넘기는 방법1 HANDLE
	ThreadMaps[tm->ThreadNUMBER] = ThreadMap(tm->ThreadNUMBER, tm->ThreadHANDLE, tm->ThreadTID, tm->ThreadFUNCTION, tm->ThreadNAME);
	//스레드 정보 및 기타 확장성을 위해서 만들어놓음
	T = ThreadMap((int)std::stoul(*i_list, nullptr, 0), (HANDLE)std::stoul(*(i_list++), nullptr, 0), (DWORD)std::stoul(*(i_list++), nullptr, 0), (PFUNCTION)std::stoul(*(i_list++), nullptr, 0), *(i_list++));
	ThreadMaps[(int)std::stoul(*i_list, nullptr, 0)] = T;
	return 0;
}

void Thread_Protect::MapRun(std::map<int, ThreadMap>* TM)
{
	std::map<int, ThreadMap>::iterator itMap;
	while (1)
	{
		Sleep(1000);
		for (itMap = TM->begin(); itMap != TM->end(); itMap++)
		{
			if (ResumeThread(OpenThread(THREAD_SUSPEND_RESUME, FALSE, itMap->second.ThreadTID)) == -1)
				//if ( ResumeThread(itMap->second.threadhw) == -1)
			{
				itMap->second.ThreadFUNCTION();
			}
		}
		//서버로 내용전달 할 부분
	}
}

void Thread_Protect::MapStart()
{
	MainhThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Thread_Protect::MapRun, &ThreadMaps, 0, NULL);
}

void Thread_Protect::MapStop()
{
	TerminateThread(MainhThread, NULL);
}

void tt()
{
	printf("스레드함수\n");
}

int main()
{
	char* ThreadFunc = (char*)malloc(sizeof(char)*10);
	std::list<std::string> Tli;
	Tli.push_front("0");//스레드 번호
	Tli.push_front("3333333333");//스레드 핸들
	Tli.push_front("4100000000");//스레드 아이디
	sprintf_s(ThreadFunc, 11, "%d", tt);
	Tli.push_front(ThreadFunc);//스레드 실행할 함수	
	Tli.push_front("Teststringssssssssssss");//스레드 이름

	Thread_Protect::Instance()->InsertThread(&ThreadMap((int)1, (HANDLE)7436, (DWORD)123123, (PFUNCTION)tt, "Teststring"), &Tli);
	Sleep(2000);
	Thread_Protect::Instance()->InsertThread(&ThreadMap((int)2, (HANDLE)5892, (DWORD)5892, (PFUNCTION)tt, "Teststring"), &Tli);
	getchar();
	return 0;
}