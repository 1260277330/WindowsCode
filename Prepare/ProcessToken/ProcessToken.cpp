// ProcessToken.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<windows.h>
#include<iostream>
using namespace std;
VOID TestProcessToken();
int main()
{
	TestProcessToken();
    return 0;
}



VOID TestProcessToken()
{
	BOOL fResult;
	TOKEN_PRIVILEGES tkp;
	HANDLE hToken;
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
	{
		printf("OpenProcessToken failed!"); //��ý��̾��ʧ��
	}
	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid); //��ñ��ػ�Ψһ�ı�ʶ
	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0); //������õ�Ȩ��
	if (GetLastError() != ERROR_SUCCESS)
	{
		printf("AdjustTokenPrivileges enable failed!"); //�޸�Ȩ��ʧ��
	}
	fResult = InitiateSystemShutdown(
		NULL, // Ҫ�صļ�����û���
		L"����ϵͳ���ȶ���WINDOWS���������ʱ���ڹػ��������ñ��湤��!", // ��ʾ��Ϣ
		0, // �ػ������ʱ��
		FALSE, // �Ƿ���ʾ�û�
		FALSE //��ΪTRUEΪ������ΪFALSEΪ�ػ�

		);
}