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

	//������ ������ �ѱ�� ���1 HANDLE
	ThreadMaps[tm->ThreadNUMBER] = ThreadMap(tm->ThreadNUMBER, tm->ThreadHANDLE, tm->ThreadTID, tm->ThreadFUNCTION, tm->ThreadNAME);
	//������ ���� �� ��Ÿ Ȯ�强�� ���ؼ� ��������
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
		//������ �������� �� �κ�
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
	printf("�������Լ�\n");
}

int main()
{
	char* ThreadFunc = (char*)malloc(sizeof(char)*10);
	std::list<std::string> Tli;
	Tli.push_front("0");//������ ��ȣ
	Tli.push_front("3333333333");//������ �ڵ�
	Tli.push_front("4100000000");//������ ���̵�
	sprintf_s(ThreadFunc, 11, "%d", tt);
	Tli.push_front(ThreadFunc);//������ ������ �Լ�	
	Tli.push_front("Teststringssssssssssss");//������ �̸�

	Thread_Protect::Instance()->InsertThread(&ThreadMap((int)1, (HANDLE)7436, (DWORD)123123, (PFUNCTION)tt, "Teststring"), &Tli);
	Sleep(2000);
	Thread_Protect::Instance()->InsertThread(&ThreadMap((int)2, (HANDLE)5892, (DWORD)5892, (PFUNCTION)tt, "Teststring"), &Tli);
	getchar();
	return 0;
}