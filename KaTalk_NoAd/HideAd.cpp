#include "stdafx.h"
#include "HideAd.h"
BOOL CALLBACK EnumWindowProc(HWND hwnd, LPARAM lParam)
{
	TCHAR classname[100] = { 0 };
	TCHAR titlename[100] = { 0 };

	GetClassName(hwnd, (LPTSTR)& classname, 100);
	GetWindowText(hwnd, (LPTSTR)& titlename, 256);

	return true;
}


HideAd::HideAd()
{
	HWND hwnd = KaTalkHWnd();
	
	if (hwnd == nullptr)
	{
		ExecuteKaKao();
		return;
	}

	ShowWindow(hwnd, SW_NORMAL);
	BringWindowToTop(hwnd);

	auto katalk_processId = GetWindowTask(hwnd);
	{
		HWND hWnd2 = FindWindowW(L"EVA_Window_Dblclk", L"");
		
		auto processId2 = GetWindowTask(hWnd2);
		if(katalk_processId == processId2)
		{
			ShowWindow(hWnd2, SW_HIDE);
			//SetWindowPos(childAD, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOMOVE);
		}
	}

	RECT rect;
	GetWindowRect(hwnd, &rect);

	HWND mainview = FindWindowEx(hwnd, nullptr, "EVA_ChildWindow", nullptr);
	if (mainview != nullptr)
	{
		TCHAR name[15] = "";
		GetWindowText(mainview, name, 15);
		if (0 == _tcscmp(name, "OnlineMainView"))
		{
			MoveWindow(mainview, 0, 30, (rect.right - rect.left), (rect.bottom - rect.top - 30), TRUE);
		}
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
	HWND hWnd = FindWindowW(NULL, L"카카오톡");


	return hWnd;
}

bool HideAd::ExecuteKaKao()
{
	
	SHELLEXECUTEINFO sInfo;
	
	ZeroMemory(&sInfo, sizeof(SHELLEXECUTEINFO));
	sInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	sInfo.nShow = SW_SHOW;
	sInfo.lpFile = "C:\\Program Files (x86)\\Kakao\\KakaoTalk\\KakaoTalk.exe";
	ShellExecuteEx(&sInfo);

	//MessageBox(nullptr, "카카오톡이 곧 실행됩니다. 로그인 후 다시 시작하세요.", "확인", MB_OK);


	return false;
}


