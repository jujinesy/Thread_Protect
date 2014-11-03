#include "Thread_Protect.h"
#include <thread>

Thread_Protect::Thread_Protect()
{
	Threadcnt = 0;
	//Thread_Protect::MapStart();
}

Thread_Protect::~Thread_Protect()
{
}

int Thread_Protect::InsertThread(ThreadMap* tm, std::list<std::string>* li)
{
	std::list<std::string>::iterator i_list = li->begin();
	//(*li).size();
	//for (i_list = li->begin(); i_list != li->end(); i_list++)
	//{
	//	cout << *i_list << endl;	
	//}
	//for (std::string i : *li) {
	//	aa=std::stoul(i.c_str(), nullptr, 0);
	//}

	//스레드 정보를 넘기는 방법1
	ThreadMaps[Threadcnt++] = ThreadMap(tm->threadhw, tm->threadid, tm->createths, tm->id, tm->name);
	//스레드 정보 및 기타 확장성을 위해서 만들어놓음
	ThreadMaps[Threadcnt++] = ThreadMap((HWND)std::stoul(*i_list, nullptr, 0), (DWORD)std::stoul(*(i_list++), nullptr, 0), (createth)std::stoul(*(i_list++), nullptr, 0), (int)std::stoul(*(i_list++), nullptr, 0), *(i_list++));
	return 0;
}

void Thread_Protect::MapRun(std::map<int, ThreadMap>* TM)
{
	std::map<int, ThreadMap>::iterator itMap;
	while (1)
	{
		Sleep(1000);
		//itMap = TM->begin();
		//itMap->second.createths();
		for (itMap = TM->begin(); itMap != TM->end(); itMap++)
		{
			if (ResumeThread(OpenThread(THREAD_SUSPEND_RESUME, FALSE, itMap->second.threadid)) == -1)
				//if ( ResumeThread(itMap->second.threadhw) == -1)
			{
				itMap->second.createths();
			}
		}
		//서버로 내용전달 할 부분
	}
}

void Thread_Protect::MapStart()
{
	std::thread MainThread(Thread_Protect::MapRun, &ThreadMaps);
	MainThread.join();
	MainThread.detach();
	//MainThread.
	//return 0;
}

void Thread_Protect::MapStop()
{

	//return 0;
}

void tt()
{
	printf("스레드함수\n");
	//return 0;
}

int main()
{
	std::list<std::string> Tli;
	Tli.push_front("3333333333");//스레드 핸들
	Tli.push_front("4100000000");//스레드 아이디
	Tli.push_front("1200000000");//스레드 실행할 함수
	Tli.push_front("1");//테스트용 인티저
	Tli.push_front("Teststringssssssssssss");//테스트용 스크링

	Thread_Protect::Instance()->InsertThread(&ThreadMap((HANDLE)7436, (DWORD)123123, (createth)tt, (int)1, "Teststring"), &Tli);
	Thread_Protect::Instance()->Thread_Protect::MapStart();
	return 0;
}