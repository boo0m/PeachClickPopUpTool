// WindowsHwnd.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <Windows.h>  
#include <stdio.h>  
#include <tchar.h>  
#include <string.h>  
#include <iostream>  
#include <winuser.h>





void CloseMyWindow(int x,int y)
{
	double fScreenWidth = ::GetSystemMetrics(SM_CXSCREEN) - 1;
	double fScreenHeight = ::GetSystemMetrics(SM_CYSCREEN) - 1;
	double fx = x * (65535.0f / fScreenWidth);
	double fy = y * (65535.0f / fScreenHeight);
	printf("%f\n", fx);
	printf("%f\n", fy);

	INPUT  Input = { 0 };
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE | MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP;
	Input.mi.dx = fx;
	Input.mi.dy = fy;
	SendInput(1, &Input, sizeof(INPUT));

}

int GetWindowPos(HWND hWnd,int *x,int *y)
{
	RECT rc;

	if (GetWindowRect(hWnd, &rc) == NULL)
		return 0;

	*x = rc.left + 10;
	*y = rc.bottom - 5;

	printf("%d\n", rc.left);
	printf("%d\n", rc.bottom);

	/*
	POINT  pt;
	GetCursorPos(&pt);   // ȡ��ַ
	printf("%ld %ld\n", pt.x, pt.y);
	��ȡ����ַ
	*/
	
	

	return 1;
}



//EnumChildWindows�ص�������hwndΪָ���ĸ�����  
BOOL CALLBACK EnumChildWindowsProc(HWND hWnd, LPARAM lParam)
{
	//RECT rc;
	int PosX = 0;
	int PosY = 0;
	char WindowTitle[100] = { 0 };

	GetWindowText(hWnd, WindowTitle, 100);
	printf("%s\n", WindowTitle);
	if (strstr(WindowTitle, "fuzzed"))
	{
		printf("%s\n", WindowTitle);
		if (GetWindowPos(hWnd, &PosX, &PosY))
			CloseMyWindow(PosX, PosY);
	}
	//printf("%s\n", WindowTitle);
	//GetWindowRect(hWnd, &rc);
	//printf("%d\n", rc.left);
	return true;
}

//EnumWindows�ص�������hwndΪ���ֵĶ��㴰��  
BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam)
{
	if (GetParent(hWnd) == NULL && IsWindowVisible(hWnd))  //�ж��Ƿ񶥲㴰�ڲ��ҿɼ�  
	{
		char WindowTitle[100] = { 0 };
		GetWindowText(hWnd, WindowTitle, 100);
		//printf("%s\n", WindowTitle);
		if (strstr(WindowTitle, "Soda PDF 8"))
		{
			printf("%s\n", WindowTitle);
			
			EnumChildWindows(hWnd, EnumChildWindowsProc, NULL); //��ȡ�����ڵ������Ӵ���  
			/*�رմ��ڣ�ΪSoda
			Sleep(3000);
			SendMessage(hWnd, WM_CLOSE, 0, 0);
			*/
		}
	}
	return true;
}


int main()
{
	//��ȡ��Ļ�����еĶ��㴰��,ÿ����һ�����ھ͵��ûص�����һ��  
	while (true)
	{
		EnumWindows(EnumWindowsProc, NULL);
		Sleep(3000);
	}

	getchar();
	return 0;
}

