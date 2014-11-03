#include <windows.h>
#include <stdio.h>
#include <tlhelp32.h>
#include <tchar.h>

//  Forward declarations:
BOOL ListProcessThreads(DWORD dwOwnerPID);
void printError(TCHAR* msg);

DWORD FindProcessID(LPCTSTR szProcessName)
{
	DWORD dwPID = 0xFFFFFFFF;
	HANDLE hSnapShot = INVALID_HANDLE_VALUE;        //�׳� �ʱ�ȭ�Ѱ�
	PROCESSENTRY32 pe;

	// Get the snapshot of the system
	pe.dwSize = sizeof(PROCESSENTRY32);              // ����ϱ� ���� ����� �����Ѵ�.
	hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);   //���� �������� �ڵ�� ����

	// find process
	Process32First(hSnapShot, &pe);                           //������ ���Ѵ�.
	do
	{
		if (!_stricmp(szProcessName, pe.szExeFile))     //���ϰ��� �ϴ� ���μ�������  ������
		{
			dwPID = pe.th32ProcessID;                            // PID �� �����Ѵ�.
			break;
		}
	} while (Process32Next(hSnapShot, &pe));                // ���� ����Ʈ�˻�

	CloseHandle(hSnapShot);

	return dwPID;
}

int main(void)
{
	DWORD pid;
	pid = FindProcessID("mspaint.exe");
	ListProcessThreads(pid);
	return 0;
}

BOOL ListProcessThreads(DWORD dwOwnerPID)
{
	HANDLE hThreadSnap = INVALID_HANDLE_VALUE;
	THREADENTRY32 te32;
	int test;

	// Take a snapshot of all running threads  
	hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	if (hThreadSnap == INVALID_HANDLE_VALUE)
		return(FALSE);

	// Fill in the size of the structure before using it. 
	te32.dwSize = sizeof(THREADENTRY32);

	// Retrieve information about the first thread,
	// and exit if unsuccessful
	if (!Thread32First(hThreadSnap, &te32))
	{
		printError(TEXT("Thread32First"));  // Show cause of failure
		CloseHandle(hThreadSnap);     // Must clean up the snapshot object!
		return(FALSE);
	}

	// Now walk the thread list of the system,
	// and display information about each thread
	// associated with the specified process
	do
	{
		if (te32.th32OwnerProcessID == dwOwnerPID)
		{
			//_tprintf(TEXT("\n     THREAD ID      = 0x%08X"), te32.th32ThreadID);
			_tprintf(TEXT("\n     THREAD ID      = %d"), te32.th32ThreadID);
			//_tprintf(TEXT("\n     base priority  = %d"), te32.tpBasePri);
			//_tprintf(TEXT("\n     delta priority = %d"), te32.tpDeltaPri);
			if (te32.th32ThreadID == 7644)
			{
				HANDLE hThread = OpenThread(THREAD_SUSPEND_RESUME, FALSE, te32.th32ThreadID);
				test = ResumeThread(hThread);
				SuspendThread(hThread);
				//Sleep(5000);
				test = ResumeThread(hThread);
			}

		}
	} while (Thread32Next(hThreadSnap, &te32));

	_tprintf(TEXT("\n"));

	//  Don't forget to clean up the snapshot object.
	CloseHandle(hThreadSnap);
	return(TRUE);
}

void printError(TCHAR* msg)
{
	DWORD eNum;
	TCHAR sysMsg[256];
	TCHAR* p;

	eNum = GetLastError();
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, eNum,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		sysMsg, 256, NULL);

	// Trim the end of the line and terminate it with a null
	p = sysMsg;
	while ((*p > 31) || (*p == 9))
		++p;
	do { *p-- = 0; } while ((p >= sysMsg) &&
		((*p == '.') || (*p < 33)));

	// Display the message
	_tprintf(TEXT("\n  WARNING: %s failed with error %d (%s)"), msg, eNum, sysMsg);
}













#include <windows.h>
#include <stdio.h>
#include <tlhelp32.h>
#include <tchar.h>

//  Forward declarations:
BOOL ListProcessThreads(DWORD dwOwnerPID);
void printError(TCHAR* msg);

DWORD FindProcessID(LPCTSTR szProcessName)
{
	DWORD dwPID = 0xFFFFFFFF;
	HANDLE hSnapShot = INVALID_HANDLE_VALUE;        //�׳� �ʱ�ȭ�Ѱ�
	PROCESSENTRY32 pe;

	// Get the snapshot of the system
	pe.dwSize = sizeof(PROCESSENTRY32);              // ����ϱ� ���� ����� �����Ѵ�.
	hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);   //���� �������� �ڵ�� ����

	// find process
	Process32First(hSnapShot, &pe);                           //������ ���Ѵ�.
	do
	{
		if (!_stricmp(szProcessName, pe.szExeFile))     //���ϰ��� �ϴ� ���μ�������  ������
		{
			dwPID = pe.th32ProcessID;                            // PID �� �����Ѵ�.
			break;
		}
	} while (Process32Next(hSnapShot, &pe));                // ���� ����Ʈ�˻�

	CloseHandle(hSnapShot);

	return dwPID;
}

int main(void)
{
	DWORD pid;
	pid = FindProcessID("mspaint.exe");
	ListProcessThreads(pid);
	return 0;
}

BOOL ListProcessThreads(DWORD dwOwnerPID)
{
	HANDLE hThreadSnap = INVALID_HANDLE_VALUE;
	THREADENTRY32 te32;
	int test;

	// Take a snapshot of all running threads  
	hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	if (hThreadSnap == INVALID_HANDLE_VALUE)
		return(FALSE);

	// Fill in the size of the structure before using it. 
	te32.dwSize = sizeof(THREADENTRY32);

	// Retrieve information about the first thread,
	// and exit if unsuccessful
	if (!Thread32First(hThreadSnap, &te32))
	{
		printError(TEXT("Thread32First"));  // Show cause of failure
		CloseHandle(hThreadSnap);     // Must clean up the snapshot object!
		return(FALSE);
	}

	// Now walk the thread list of the system,
	// and display information about each thread
	// associated with the specified process
	do
	{
		if (te32.th32OwnerProcessID == dwOwnerPID)
		{
			//_tprintf(TEXT("\n     THREAD ID      = 0x%08X"), te32.th32ThreadID);
			_tprintf(TEXT("\n     THREAD ID      = %d"), te32.th32ThreadID);
			//_tprintf(TEXT("\n     base priority  = %d"), te32.tpBasePri);
			//_tprintf(TEXT("\n     delta priority = %d"), te32.tpDeltaPri);
			if (te32.th32ThreadID == 7644)
			{
				HANDLE hThread = OpenThread(THREAD_SUSPEND_RESUME, FALSE, te32.th32ThreadID);
				test = ResumeThread(hThread);
				SuspendThread(hThread);
				//Sleep(5000);
				test = ResumeThread(hThread);
			}

		}
	} while (Thread32Next(hThreadSnap, &te32));

	_tprintf(TEXT("\n"));

	//  Don't forget to clean up the snapshot object.
	CloseHandle(hThreadSnap);
	return(TRUE);
}

void printError(TCHAR* msg)
{
	DWORD eNum;
	TCHAR sysMsg[256];
	TCHAR* p;

	eNum = GetLastError();
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, eNum,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		sysMsg, 256, NULL);

	// Trim the end of the line and terminate it with a null
	p = sysMsg;
	while ((*p > 31) || (*p == 9))
		++p;
	do { *p-- = 0; } while ((p >= sysMsg) &&
		((*p == '.') || (*p < 33)));

	// Display the message
	_tprintf(TEXT("\n  WARNING: %s failed with error %d (%s)"), msg, eNum, sysMsg);
}




#include <map>
#include <string>
#include <stdio.h>
#include <iostream>

using namespace std;

int main()
{
	map<int, int, int> iMapa;
	map<int, string> iMap;

	//iMapa.insert(map <int, int, int> ::value_type(1, 10, 1));
	iMap[5] = "5������� ������"; //��ҿ� ���� �����͸� ���� ������ �߰�
	iMap[3] = "3������� ������";
	iMap[9] = "9������� ������";

	map<int, string>::iterator itMap;

	printf("iMap\n");
	for (itMap = iMap.begin(); itMap != iMap.end(); itMap++)
		printf("%d : %s\n", itMap->first, itMap->second.c_str()); //���ĵ� ����
	printf("\n");

	iMap[9] = "�ȳ��ϼ���!"; //���� �����

	printf("iMap\n");
	for (itMap = iMap.begin(); itMap != iMap.end(); itMap++)
		printf("%d : %s\n", itMap->first, itMap->second.c_str());
	printf("\n");

	printf("iMap[5] = %s\n\n", iMap[5].c_str()); //�ε����� ���� ����

	map<char*, string> sMap; //char*�� string �Ѵ� ���ڿ�������
	//char*�� ���ĵ��� �ʴ´�.

	sMap["�̱�"] = "United State of America";
	sMap["�߱�"] = "China";
	sMap["�Ϻ�"] = "Japan";
	sMap["�ѱ�"] = "Korea, Republic";

	map<char*, string>::iterator itStrMap;

	printf("sMap\n");
	cout << sMap.find("�̱�")->second << endl;
	for (itStrMap = sMap.begin(); itStrMap != sMap.end(); itStrMap++)
		printf("%s : %s\n", itStrMap->first, itStrMap->second.c_str());
	printf("\n"); //���������� ���� �ѱ��� ���� ���� ��µ�

	sMap.erase("�Ϻ�"); //�Ϻ��� ����

	printf("sMap\n");
	for (itStrMap = sMap.begin(); itStrMap != sMap.end(); itStrMap++)
		printf("%s : %s\n", itStrMap->first, itStrMap->second.c_str());
	printf("\n");

	return 0;
}






#include <map>#include <windows.h>
#include <stdio.h>
#include <tlhelp32.h>
#include <tchar.h>

//  Forward declarations:
BOOL ListProcessThreads(DWORD dwOwnerPID);
void printError(TCHAR* msg);

DWORD FindProcessID(LPCTSTR szProcessName)
{
	DWORD dwPID = 0xFFFFFFFF;
	HANDLE hSnapShot = INVALID_HANDLE_VALUE;        //�׳� �ʱ�ȭ�Ѱ�
	PROCESSENTRY32 pe;

	// Get the snapshot of the system
	pe.dwSize = sizeof(PROCESSENTRY32);              // ����ϱ� ���� ����� �����Ѵ�.
	hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);   //���� �������� �ڵ�� ����

	// find process
	Process32First(hSnapShot, &pe);                           //������ ���Ѵ�.
	do
	{
		if (!_stricmp(szProcessName, pe.szExeFile))     //���ϰ��� �ϴ� ���μ�������  ������
		{
			dwPID = pe.th32ProcessID;                            // PID �� �����Ѵ�.
			break;
		}
	} while (Process32Next(hSnapShot, &pe));                // ���� ����Ʈ�˻�

	CloseHandle(hSnapShot);

	return dwPID;
}

int main(void)
{
	DWORD pid;
	pid = FindProcessID("mspaint.exe");
	ListProcessThreads(pid);
	return 0;
}

BOOL ListProcessThreads(DWORD dwOwnerPID)
{
	HANDLE hThreadSnap = INVALID_HANDLE_VALUE;
	THREADENTRY32 te32;
	int test;

	// Take a snapshot of all running threads  
	hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	if (hThreadSnap == INVALID_HANDLE_VALUE)
		return(FALSE);

	// Fill in the size of the structure before using it. 
	te32.dwSize = sizeof(THREADENTRY32);

	// Retrieve information about the first thread,
	// and exit if unsuccessful
	if (!Thread32First(hThreadSnap, &te32))
	{
		printError(TEXT("Thread32First"));  // Show cause of failure
		CloseHandle(hThreadSnap);     // Must clean up the snapshot object!
		return(FALSE);
	}

	// Now walk the thread list of the system,
	// and display information about each thread
	// associated with the specified process
	do
	{
		if (te32.th32OwnerProcessID == dwOwnerPID)
		{
			//_tprintf(TEXT("\n     THREAD ID      = 0x%08X"), te32.th32ThreadID);
			_tprintf(TEXT("\n     THREAD ID      = %d"), te32.th32ThreadID);
			//_tprintf(TEXT("\n     base priority  = %d"), te32.tpBasePri);
			//_tprintf(TEXT("\n     delta priority = %d"), te32.tpDeltaPri);
			if (te32.th32ThreadID == 7644)
			{
				HANDLE hThread = OpenThread(THREAD_SUSPEND_RESUME, FALSE, te32.th32ThreadID);
				test = ResumeThread(hThread);
				SuspendThread(hThread);
				//Sleep(5000);
				test = ResumeThread(hThread);
			}

		}
	} while (Thread32Next(hThreadSnap, &te32));

	_tprintf(TEXT("\n"));

	//  Don't forget to clean up the snapshot object.
	CloseHandle(hThreadSnap);
	return(TRUE);
}

void printError(TCHAR* msg)
{
	DWORD eNum;
	TCHAR sysMsg[256];
	TCHAR* p;

	eNum = GetLastError();
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, eNum,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		sysMsg, 256, NULL);

	// Trim the end of the line and terminate it with a null
	p = sysMsg;
	while ((*p > 31) || (*p == 9))
		++p;
	do { *p-- = 0; } while ((p >= sysMsg) &&
		((*p == '.') || (*p < 33)));

	// Display the message
	_tprintf(TEXT("\n  WARNING: %s failed with error %d (%s)"), msg, eNum, sysMsg);
}













#include <windows.h>
#include <stdio.h>
#include <tlhelp32.h>
#include <tchar.h>

//  Forward declarations:
BOOL ListProcessThreads(DWORD dwOwnerPID);
void printError(TCHAR* msg);

DWORD FindProcessID(LPCTSTR szProcessName)
{
	DWORD dwPID = 0xFFFFFFFF;
	HANDLE hSnapShot = INVALID_HANDLE_VALUE;        //�׳� �ʱ�ȭ�Ѱ�
	PROCESSENTRY32 pe;

	// Get the snapshot of the system
	pe.dwSize = sizeof(PROCESSENTRY32);              // ����ϱ� ���� ����� �����Ѵ�.
	hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);   //���� �������� �ڵ�� ����

	// find process
	Process32First(hSnapShot, &pe);                           //������ ���Ѵ�.
	do
	{
		if (!_stricmp(szProcessName, pe.szExeFile))     //���ϰ��� �ϴ� ���μ�������  ������
		{
			dwPID = pe.th32ProcessID;                            // PID �� �����Ѵ�.
			break;
		}
	} while (Process32Next(hSnapShot, &pe));                // ���� ����Ʈ�˻�

	CloseHandle(hSnapShot);

	return dwPID;
}

int main(void)
{
	DWORD pid;
	pid = FindProcessID("mspaint.exe");
	ListProcessThreads(pid);
	return 0;
}

BOOL ListProcessThreads(DWORD dwOwnerPID)
{
	HANDLE hThreadSnap = INVALID_HANDLE_VALUE;
	THREADENTRY32 te32;
	int test;

	// Take a snapshot of all running threads  
	hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	if (hThreadSnap == INVALID_HANDLE_VALUE)
		return(FALSE);

	// Fill in the size of the structure before using it. 
	te32.dwSize = sizeof(THREADENTRY32);

	// Retrieve information about the first thread,
	// and exit if unsuccessful
	if (!Thread32First(hThreadSnap, &te32))
	{
		printError(TEXT("Thread32First"));  // Show cause of failure
		CloseHandle(hThreadSnap);     // Must clean up the snapshot object!
		return(FALSE);
	}

	// Now walk the thread list of the system,
	// and display information about each thread
	// associated with the specified process
	do
	{
		if (te32.th32OwnerProcessID == dwOwnerPID)
		{
			//_tprintf(TEXT("\n     THREAD ID      = 0x%08X"), te32.th32ThreadID);
			_tprintf(TEXT("\n     THREAD ID      = %d"), te32.th32ThreadID);
			//_tprintf(TEXT("\n     base priority  = %d"), te32.tpBasePri);
			//_tprintf(TEXT("\n     delta priority = %d"), te32.tpDeltaPri);
			if (te32.th32ThreadID == 7644)
			{
				HANDLE hThread = OpenThread(THREAD_SUSPEND_RESUME, FALSE, te32.th32ThreadID);
				test = ResumeThread(hThread);
				SuspendThread(hThread);
				//Sleep(5000);
				test = ResumeThread(hThread);
			}

		}
	} while (Thread32Next(hThreadSnap, &te32));

	_tprintf(TEXT("\n"));

	//  Don't forget to clean up the snapshot object.
	CloseHandle(hThreadSnap);
	return(TRUE);
}

void printError(TCHAR* msg)
{
	DWORD eNum;
	TCHAR sysMsg[256];
	TCHAR* p;

	eNum = GetLastError();
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, eNum,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		sysMsg, 256, NULL);

	// Trim the end of the line and terminate it with a null
	p = sysMsg;
	while ((*p > 31) || (*p == 9))
		++p;
	do { *p-- = 0; } while ((p >= sysMsg) &&
		((*p == '.') || (*p < 33)));

	// Display the message
	_tprintf(TEXT("\n  WARNING: %s failed with error %d (%s)"), msg, eNum, sysMsg);
}




#include <map>
#include <string>
#include <stdio.h>
#include <iostream>

using namespace std;

int main()
{
	map<int, int, int> iMapa;
	map<int, string> iMap;

	//iMapa.insert(map <int, int, int> ::value_type(1, 10, 1));
	iMap[5] = "5������� ������"; //��ҿ� ���� �����͸� ���� ������ �߰�
	iMap[3] = "3������� ������";
	iMap[9] = "9������� ������";

	map<int, string>::iterator itMap;

	printf("iMap\n");
	for (itMap = iMap.begin(); itMap != iMap.end(); itMap++)
		printf("%d : %s\n", itMap->first, itMap->second.c_str()); //���ĵ� ����
	printf("\n");

	iMap[9] = "�ȳ��ϼ���!"; //���� �����

	printf("iMap\n");
	for (itMap = iMap.begin(); itMap != iMap.end(); itMap++)
		printf("%d : %s\n", itMap->first, itMap->second.c_str());
	printf("\n");

	printf("iMap[5] = %s\n\n", iMap[5].c_str()); //�ε����� ���� ����

	map<char*, string> sMap; //char*�� string �Ѵ� ���ڿ�������
	//char*�� ���ĵ��� �ʴ´�.

	sMap["�̱�"] = "United State of America";
	sMap["�߱�"] = "China";
	sMap["�Ϻ�"] = "Japan";
	sMap["�ѱ�"] = "Korea, Republic";

	map<char*, string>::iterator itStrMap;

	printf("sMap\n");
	cout << sMap.find("�̱�")->second << endl;
	for (itStrMap = sMap.begin(); itStrMap != sMap.end(); itStrMap++)
		printf("%s : %s\n", itStrMap->first, itStrMap->second.c_str());
	printf("\n"); //���������� ���� �ѱ��� ���� ���� ��µ�

	sMap.erase("�Ϻ�"); //�Ϻ��� ����

	printf("sMap\n");
	for (itStrMap = sMap.begin(); itStrMap != sMap.end(); itStrMap++)
		printf("%s : %s\n", itStrMap->first, itStrMap->second.c_str());
	printf("\n");

	return 0;
}






#include <map>
#include <string>
#include <Windows.h>

typedef struct category {
	category() : id(0), name("dd") {}
	category(int newId, std::string newName)
		: id(newId), name(newName) {}

	HWND threadhw;
	int id;
	std::string name;
}CATEGORY, *CATEGORY;

std::map<int, category> categories;

int main() {
	categories[1] = category(1, "First category");
	categories[2] = category(2, "Second category");
	categories[3] = category();

	return 0;
}
#include <string>
#include <Windows.h>

typedef struct category {
	category() : id(0), name("dd") {}
	category(int newId, std::string newName)
		: id(newId), name(newName) {}

	HWND threadhw;
	int id;
	std::string name;
}CATEGORY, *CATEGORY;

std::map<int, category> categories;

int main() {
	categories[1] = category(1, "First category");
	categories[2] = category(2, "Second category");
	categories[3] = category();

	return 0;
}