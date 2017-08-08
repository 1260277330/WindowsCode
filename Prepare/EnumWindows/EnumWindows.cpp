// EnumWindows.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

///////////////1��ö�����崰��
///////////////2��ö�ٴ������µ��Ӵ���


#include <Stdio.h>
#include <Windows.h>

BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam);
BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam );

int main( int argc, char* argv[] )
{
    HWND m_htest = FindWindow("TXGuiFoundation",NULL);//(1,lpclassname 2,lpwindowsname)
    //   EnumWindows( EnumWindowsProc, NULL );
    if(m_htest==NULL)
    {
        printf("No find something!!\n");
    }
    
    EnumChildWindows(m_htest,EnumChildProc,NULL);
    return 0;
}

HWND m_hwndFind[1000] = {0};
int  m_num = 0;


BOOL CALLBACK EnumChildProc(HWND hWnd, LPARAM lParam )
{
    //         if(::GetWindowLong(hWnd,GWL_STYLE) & WS_VISIBLE)
    //   {
    
    char sBuf[256];
    ::GetClassName(hWnd,NULL,254);
//    ::GetWindowText(aHwnd,WndCaption,254);
    ::GetWindowText( hWnd, sBuf, 256 );
    printf( "%s\n", sBuf );
    m_hwndFind[m_num] = hWnd;
    m_num++;
    //  }
    return 1;
    
}



BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam)
{
    if(::GetWindowLong(hWnd,GWL_STYLE) & WS_VISIBLE)
    {
        char sBuf[256];
        //��ȡ���ڱ���
        ::GetWindowText( hWnd, sBuf, 256 );
        if ( strcmp( sBuf, "�ҵĵ���" ) == 0 )
        {
            //�ڷ����ҵĵ���ʱ���������Ϊwww.a3gs.com
            ::SetWindowText( hWnd, "www.a3gs.com" );
        }
        printf( "%s\n", sBuf );
        m_hwndFind[m_num] = hWnd;
        m_num++;
    }
    return 1;
}

/////////////////////////////////////////////////



#include <windows.h>
BOOL CALLBACK EnumChildProc(HWND hWnd,LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
    char className[]="TXGuiFoundation";

    HWND hWnd=::FindWindow(className,NULL);
    if(hWnd)
    {
        ::EnumChildWindows(hWnd,EnumChildProc,0);
        return 0;
    }
    MessageBox(NULL,"fail!","fail",MB_OK);
    return 0;
}


BOOL CALLBACK EnumChildProc(HWND hWnd,LPARAM lParam)
{
    char temp1[256],temp2[256];
    ::GetWindowText(hWnd,temp1,255);


    wsprintf(temp2,"hwnd:%x text: %s",hWnd,temp1);
    MessageBox(NULL,temp2,"cwnd",MB_OK);
    return true;
} 

int main()
{
    return 0;
}

