// SetWindowsEx.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<windows.h>
#include<iostream>

using namespace std;


int main()
{
	//����DLL
	HMODULE Dll = LoadLibrary(L"Inject.dll");
	if (!Dll)
	{
		printf("Cannot fing Dll\r\n");
		getchar();
		return FALSE;
	}
	//�õ�HOOK������
	HOOKPROC Address = (HOOKPROC)GetProcAddress(Dll, "Inject");
	if (Address = NULL)
	{
		printf("Cannot find function");
		getchar();
		return FALSE;
	}
	//��HOOK���ص�HOOK����
	//��������Ϊ0��ʾ����ȫ���߳�
	HHOOK HookHandle = SetWindowsHookEx(WH_KEYBOARD, Address, Dll, 0);
	if (HookHandle == NULL)
	{
		printf("Couldn't hook the keyboard");
	}
	printf("Hooked the program, hit enter to exit");
	getchar();
	UnhookWindowsHookEx(HookHandle);

    return 0;
}

