// CreateToolhelp32Snapshot.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<windows.h>
#include <TlHelp32.h>
#include<stdio.h>
#include<psapi.h>
#pragma comment(lib,"psapi.lib")

int main()
{
	//���̽ṹ
	PROCESSENTRY32 Pe32;  
	//��֮ǰҪ֪����С
	Pe32.dwSize = sizeof(Pe32);
	//�������̿���
	HANDLE ProcessSnapHandle=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,
		0);
	HANDLE ModuleSnapHandle = NULL;
	if (ProcessSnapHandle == INVALID_HANDLE_VALUE)
	{
		printf("[-]ProcessSnapHandle Error!\r\n");
		int Error = GetLastError();
		printf("Error is : %d\r\n", Error);
		return -1;
	}
	BOOL NextProcess = Process32First(ProcessSnapHandle,&Pe32);

	HANDLE ProcessHandle = 0;
	WCHAR ProcessPath[MAX_PATH] = { 0 };
	MODULEENTRY32 pModule;  //ģ��Ľṹ

	pModule.dwSize = sizeof(MODULEENTRY32);
	BOOL Return = FALSE;
	//׼������  ��ʼ����
	while (NextProcess)
	{
		//�ȴ򿪽��̶���õ����
		ProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, Pe32.th32ParentProcessID);
		//�õ�ģ���·��
		GetModuleFileNameEx(ProcessHandle, NULL, ProcessPath, _MAX_PATH);
		wprintf(_T("ProcessPath:%s\n ProcessName : %s\t\t ProcessID : %d\n\n"), ProcessPath, Pe32.szExeFile, Pe32.th32ProcessID);

		//����ģ��Ŀ���
		ModuleSnapHandle = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE,
			Pe32.th32ProcessID);

		Return = Module32First(ModuleSnapHandle, &pModule);

		while (Return)
		{
			//ö�����
			wprintf(_T("\t\tModual:%s\tBase:%2x\n"), pModule.szExePath, pModule.modBaseAddr);
			Return = ::Module32Next(ModuleSnapHandle, &pModule);

		}

		CloseHandle(ModuleSnapHandle);
		NextProcess = Process32Next(ProcessSnapHandle, &Pe32);
	}
	CloseHandle(ProcessSnapHandle);
    return 0;
}

