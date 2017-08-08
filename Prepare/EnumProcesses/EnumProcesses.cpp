// EnumProcesses.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<windows.h>
#include<iostream>
#include <TlHelp32.h>
#include<psapi.h>
#pragma comment(lib,"psapi.lib")

using namespace std;


// ��ӡ������Ϣ
VOID PrintError(LPTSTR msg)
{
	DWORD eNum;
	TCHAR sysMsg[256];
	TCHAR* p;

	eNum = GetLastError();
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, eNum,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		sysMsg, 256, NULL);
	p = sysMsg;
	while ((*p > 31) || (*p == 9))
		++p;
	do { *p-- = 0; } while ((p >= sysMsg) &&
		((*p == '.') || (*p < 33)));
	printf("\n  WARNING: %s failed with error %d (%s)", msg, eNum, sysMsg);
}




VOID ListProcessModulesl(DWORD dwPID);
/*

EnumProcesses �������̲���
ListProcessModulesl������
ListProcessThreads �����о�ģ����߳�

*/
VOID WINAPI EnumProcess1()
{
	DWORD Processes[1024], Needed, ProcessCount;
	unsigned int i;
	//��ʼ����

	if (!EnumProcesses(Processes, sizeof(Processes), &Needed))
		return;

	ProcessCount=Needed / sizeof(DWORD);
	for (i = 0; i < ProcessCount; i++)
	{
		printf("\n\n************************************************");
		printf("\nPROCESS: %u \n\n ", Processes[i]);
		ListProcessModulesl(Processes[i]);
		ListProcessThreads(Processes[i]);
	}
}

int main()
{
	EnumProcess1();
    return 0;
}

/*

ͨ�����������ҽ���ID

*/
BOOL GetProcessIdByName(LPSTR ProcessName, LPWORD lpPID)
{
	//��������ʼ��
	STARTUPINFO Start;
	PROCESS_INFORMATION pInformation;
	PROCESSENTRY32 Process;
	HANDLE SnaphotHandle;
	ZeroMemory(&Start, sizeof(STARTUPINFO));
	ZeroMemory(&pInformation, sizeof(PROCESS_INFORMATION));
	Start.cb = sizeof(STARTUPINFO);
	ZeroMemory(&Process, sizeof(PROCESSENTRY32));
	Process.dwSize = sizeof(PROCESSENTRY32);

	//��������

	SnaphotHandle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (SnaphotHandle == INVALID_HANDLE_VALUE);
	{
		return FALSE;
	}
	if (!Process32First(SnaphotHandle, &Process))
	{
		return FALSE;
	}
	do
	{
		if (lstrcmpi(Process.szExeFile,L"explorer.exe") == 0)
		{
			*lpPID = Process.th32ProcessID;
			CloseHandle(SnaphotHandle);
			return TRUE;
		}
	} while (Process32Next(SnaphotHandle, &Process));

	CloseHandle(SnaphotHandle);
	return FALSE;
}
/*
����  ����EnumProcessModules����
�оٺ���ʾ���̼��ص�ģ��

*/
VOID ListProcessModulesl(DWORD dwPID)
{
	HMODULE ModuleHandle[1024];
	HANDLE ProcessHandle;
	DWORD Needed;
	unsigned int i;
	printf("[+]\nListProcessModulesl Process ID %u \n", dwPID);
	//�򿪽��� ��þ��
	ProcessHandle = OpenProcess(PROCESS_QUERY_INFORMATION|
		PROCESS_VM_READ,
		FALSE,dwPID);
	if (ProcessHandle == FALSE)
		return;
	//��ʼ����EnumProcessModules
	if (EnumProcessModules(ProcessHandle, ModuleHandle, sizeof(ModuleHandle), &Needed))
	{
		for (i = 0; i < (Needed / sizeof(HMODULE)); i++)
		{
			TCHAR ModuleName[MAX_PATH];
			if (GetModuleFileNameExA(ProcessHandle, ModuleHandle[i], (LPSTR)ModuleName,
				sizeof(ModuleName) / sizeof(TCHAR)))
			{
				printf("\t %s (0x%08X)\n", ModuleName, ModuleHandle[i]);
			}
		}
	}
	CloseHandle(ProcessHandle);
}

/*ͨ�������оٽ���ģ��
��ʵ��˵��ͨ��CreateToolhelp32Snapshot��Module32First��Module32Next�Ⱥ�����ȡ���̼��ص�ģ����Ϣ��
*/

VOID ListProcessModules2(DWORD dwPID)
{
	HANDLE ModuleSnapHandle = INVALID_HANDLE_VALUE;
	MODULEENTRY32 Module32;
	printf("[+]\nListProcessModules2 Process ID %u \n", dwPID);

	ModuleSnapHandle = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPID);
	if (ModuleSnapHandle == INVALID_HANDLE_VALUE)
	{
		printf("[-]CreateToolhelp32Snapshot of(module)");

		return ;
	}
	//���ò����ṹ��Ĵ�С
	Module32.dwSize = sizeof(MODULEENTRY32);
	//��ʼ��ȡģ����Ϣ
	if (!Module32First(ModuleSnapHandle, &Module32))
	{
		PrintError(L"Module32First");  // Show cause of failure
		CloseHandle(ModuleSnapHandle);     // Must clean up the snapshot object!
		return;
	}
	do
	{
		printf("\n\n     MODULE NAME:     %s", Module32.szModule);
		printf("\n     executable     = %s", Module32.szExePath);
		printf("\n     process ID     = 0x%08X", Module32.th32ProcessID);
		printf("\n     ref count (g)  =     0x%04X", Module32.GlblcntUsage);
		printf("\n     ref count (p)  =     0x%04X", Module32.ProccntUsage);
		printf("\n     base address   = 0x%08X", (DWORD)Module32.modBaseAddr);
		printf("\n     base size      = %d", Module32.modBaseSize);
	} while (Module32Next(ModuleSnapHandle, &Module32));

	CloseHandle(ModuleSnapHandle);	// �رվ��
	return;


}

/*************************************
* VOID ListProcessThreads( DWORD dwPID )
* ����	����Thread32First��Thread32Next
*		��ʾһ�����̵��߳�
*
* ����	DWORD dwPID	����PID
**************************************/
VOID ListProcessThreads(DWORD dwPID)
{
	HANDLE ThreadSnapHandle = INVALID_HANDLE_VALUE;
	THREADENTRY32 Thread32;

	printf("\\ListProcessThreads Process ID %u\n", dwPID);


	ThreadSnapHandle = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	if (ThreadSnapHandle == INVALID_HANDLE_VALUE)
	{
		printf("[-]ThreadSnapHandle error\r\n");
		return;
	}
	Thread32.dwSize = sizeof(THREADENTRY32);


	//��ʼ��ȡ��Ϣ

	if (!Thread32First(ThreadSnapHandle, &Thread32))
	{
		PrintError(L"Thread32First");  // Show cause of failure
		CloseHandle(ThreadSnapHandle);     // Must clean up the snapshot object!
		return;
	}
	do
	{
		if (Thread32.th32OwnerProcessID == dwPID)
		{
			//��ʾ�����Ϣ
			printf("\n   THREAD ID = 0x%08X", Thread32.th32ThreadID);
			printf("\t   base priority = %d", Thread32.tpBasePri);
			printf("\t   delta priority = %d", Thread32.tpDeltaPri);
		}
	} while (Thread32Next(ThreadSnapHandle, &Thread32));

	CloseHandle(ThreadSnapHandle);
	return;
}