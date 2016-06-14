// WindowsHwnd.cpp : 定义控制台应用程序的入口点。
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
	GetCursorPos(&pt);   // 取地址
	printf("%ld %ld\n", pt.x, pt.y);
	获取鼠标地址
	*/
	
	

	return 1;
}



//EnumChildWindows回调函数，hwnd为指定的父窗口  
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

//EnumWindows回调函数，hwnd为发现的顶层窗口  
BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam)
{
	if (GetParent(hWnd) == NULL && IsWindowVisible(hWnd))  //判断是否顶层窗口并且可见  
	{
		char WindowTitle[100] = { 0 };
		GetWindowText(hWnd, WindowTitle, 100);
		//printf("%s\n", WindowTitle);
		if (strstr(WindowTitle, "Soda PDF 8"))
		{
			printf("%s\n", WindowTitle);
			
			EnumChildWindows(hWnd, EnumChildWindowsProc, NULL); //获取父窗口的所有子窗口  
			/*关闭窗口，为Soda
			Sleep(3000);
			SendMessage(hWnd, WM_CLOSE, 0, 0);
			*/
		}
	}
	return true;
}


int main()
{
	//获取屏幕上所有的顶层窗口,每发现一个窗口就调用回调函数一次  
	while (true)
	{
		EnumWindows(EnumWindowsProc, NULL);
		Sleep(3000);
	}

	getchar();
	return 0;
}

