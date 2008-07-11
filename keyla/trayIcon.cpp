#include "common.h"
#include "layoutList.h"
#include "mainWindow.h"
#include "res/resource.h"
#include "settings.h"
#include "trayIcon.h"

#include <algorithm>
#include <map>
using namespace std;

// ���� ������ � ����
static HMENU Menu = 0;

// HWND �������� ����. ��������� � ������ create
static HWND Window = 0;

// ����������� ��������� � ������
static const LPCTSTR Tooltip = TEXT("keyla - ������������� ��������� ����������");

// ������� � �������� ��� ������ ���������
// ���� - ��������� ������������� language id ��������
// �������� - ��������� ������
static map<tstring, HICON> LayoutIcons; 

namespace trayIcon {

	void create(HWND mainWindow) {
		Window = mainWindow;

		// ��������� �� �������� ���� ������ � ����
		Menu = LoadMenu(GetModuleHandle(0), MAKEINTRESOURCE(IDM_TRAYICONMENU));
		assert(Menu != 0);

		// ��������� ������ � ����.
		// ����� �������� ���������, �� ������������� ����� ��������,
		// ������� ��� � indicateLayout ��-������
		NOTIFYICONDATA nid = {sizeof nid};
		nid.hWnd = Window;
		nid.uID = mainWindow::TrayIconId;
		nid.uFlags = NIF_MESSAGE | NIF_TIP;
		nid.uCallbackMessage = mainWindow::TrayIconMessage;
		_tcsncpy(nid.szTip, Tooltip, sizeof(nid.szTip) / sizeof(TCHAR));
		verify(Shell_NotifyIcon(NIM_ADD, &nid));
	}

	void showMenu() {
		showContextMenu(Menu, Window);
	}

	void indicateLayout(HKL layout) {
		HICON icon = 0;
		tstring langid = layoutList::layoutLangId(layout);
		map<tstring, HICON>::const_iterator it = LayoutIcons.find(langid);
		if (it != LayoutIcons.end()) {
			// ������ ��� ���� ���������
			icon = it->second;
		} else {
			// ��������� ������
			tstring path = TEXT("icons\\") + langid + TEXT(".ico");
			icon = static_cast<HICON>(LoadImage(0, path.c_str(), IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_LOADTRANSPARENT));
			if (icon == 0) {
				// ������ �� �������. ���������� ���� ����������� ������
				assert(false);
				icon = settings::Settings.mainIcon;
			} else {
				// ������ ���������. ��������� � � �������
				// NOTE: ���������, �������� � insert ������ ��������� ������� �������???
				LayoutIcons.insert(make_pair(langid, icon));
			}
		}
		// ���������� �������� ������
		NOTIFYICONDATA nid = {sizeof nid};
		nid.hWnd = Window;
		nid.uID = mainWindow::TrayIconId;
		nid.uFlags = NIF_ICON;
		nid.hIcon = icon;
		verify(Shell_NotifyIcon(NIM_MODIFY, &nid));
	}

	void destroy() {
		NOTIFYICONDATA nid = {sizeof nid};
		nid.hWnd = Window;
		nid.uID = mainWindow::TrayIconId;
		verify(Shell_NotifyIcon(NIM_DELETE, &nid));
		Window = 0;

		verify(DestroyMenu(Menu));
		Menu = 0;

		map<tstring, HICON>::const_iterator it = LayoutIcons.begin();
		map<tstring, HICON>::const_iterator end = LayoutIcons.end();
		for (; it != end; ++it)
			DestroyIcon(it->second);
		LayoutIcons.clear();
	}

}