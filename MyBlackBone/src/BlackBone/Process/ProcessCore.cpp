
#include "../Config.h"
#include "ProcessCore.h"


namespace blackbone
{
	ProcessCore::ProcessCore()
	{
		//LOAD_IMPORT("GetProcessDEPPolicy", L"kernel32.dll");

	}
	ProcessCore::~ProcessCore()
	{
		//Close();
	}
//���ӵ����еĽ���
	NTSTATUS ProcessCore::Open(DWORD Pid, DWORD Access)
	{
		//��ֹ���й© �����ȹر�һ��
		Close();
		//��ͬ�ش���ǰ����
		return 1;
	}


//�رվ�� ָ��
	void ProcessCore::Close()
	{
		if (_hProcess)
		{
			CloseHandle(_hProcess);

			_hProcess = NULL;
			_pid = 0;
			//_native.reset(nullptr);
		}
	}



}