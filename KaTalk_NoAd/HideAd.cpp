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

	RECT rect;
	GetWindowRect(hwnd, &rect);

	HWND childAD = FindWindowEx(hwnd, nullptr, "EVA_Window", nullptr);
	ShowWindow(childAD, SW_HIDE);
	SetWindowPos(childAD, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOMOVE);

	HWND mainview = FindWindowEx(hwnd, nullptr, "EVA_ChildWindow", nullptr);
	while (mainview != nullptr)
	{
		TCHAR name[15] = "";
		GetWindowText(mainview, name, 15);
		if (0 == _tcscmp(name, "OnlineMainView"))
		{
			MoveWindow(mainview, 0, 30, (rect.right - rect.left), (rect.bottom - rect.top - 30), TRUE);
			break;
		}
	}

	// �������� �˾��Ǵ� ������ �ϴ��� ���� ����
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
	HWND hWnd = FindWindow(NULL, "īī����");

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

	//MessageBox(nullptr, "īī������ �� ����˴ϴ�. �α��� �� �ٽ� �����ϼ���.", "Ȯ��", MB_OK);


	return false;
}


