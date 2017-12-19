#include "stdafx.h"
#include "HideAd.h"
BOOL CALLBACK EnumWindowProc(HWND hwnd, LPARAM lParam)
{
	TCHAR classname[100] = { 0 };
	TCHAR titlename[100] = { 0 };

	GetClassName(hwnd, (LPTSTR)&classname, 100);
	GetWindowText(hwnd, (LPTSTR)&titlename, 256);

	return true;
}


HideAd::HideAd()
{
	//	EnumWindows(EnumWindowProc, 0);
	isExecution();

	HWND hwnd = KaTalkHWnd();

	if (IsWindowVisible(hwnd))
	{
		RECT rect;
		GetWindowRect(hwnd, &rect);
		HWND friendList = FindWindowEx(hwnd, nullptr, "#32770", nullptr);
		HWND childAD = FindWindowEx(hwnd, nullptr, "EVA_Window", nullptr);
		ShowWindow(childAD, SW_HIDE);

		SetWindowPos(childAD, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOMOVE);
		SetWindowPos(friendList, HWND_BOTTOM, 0, 0, (rect.right - rect.left), (rect.bottom - rect.top - 36), SWP_NOMOVE);
	}

	// 랜덤으로 팝업되는 오른쪽 하단의 투명 광고
	HWND hwnd_fake = FindWindow(NULL, "FAKE_WND_REACHPOP");
	if (hwnd_fake != NULL) SendMessage(hwnd_fake, WM_CLOSE, 0, 0);

	HWND hwnd_eva = FindWindow(NULL, "EVA_Window");
	if (hwnd_eva != NULL) SendMessage(hwnd_eva, WM_CLOSE, 0, 0);
}


HideAd::~HideAd()
{
}

HWND HideAd::KaTalkHWnd()
{
	HWND hWnd = FindWindow(NULL, "카카오톡");

	return hWnd;
}

bool HideAd::isExecution()
{
	HWND hWnd = KaTalkHWnd();
	SHELLEXECUTEINFO sInfo;
	if (hWnd == NULL)
	{
		ZeroMemory(&sInfo, sizeof(SHELLEXECUTEINFO));
		sInfo.cbSize = sizeof(SHELLEXECUTEINFO);
		sInfo.nShow = SW_SHOW;
		sInfo.lpFile = "C:\\Program Files (x86)\\Kakao\\KakaoTalk\\KakaoTalk.exe";
		ShellExecuteEx(&sInfo);
		Sleep(10000);
	}
	
	return false;
}


