// BlackBoneTest.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include"../BlackBoneTest/Process/Process.h"

int main()
{
	Process Process;
	Process.Attach(GetCurrentProcessId());


    return 0;
}

