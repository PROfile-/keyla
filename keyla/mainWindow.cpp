#include "common.h"
#include "core.h"
#include "mainWindow.h"
#include "res/resource.h"
#include "settingsWindow.h"
#include "trayIcon.h"
#include "../win32xx/WinCore.h"

class MainWindow : public CWnd {
protected:

	virtual void PreRegisterClass(WNDCLASS & wc) {
		CWnd::PreRegisterClass(wc);

		// ���������� ����������� ����� ����, ����� �� ��� ��������
		// � ������ ���� ������ ���������� ����������
		wc.lpszClassName = TEXT("keyla main window");
	}

	virtual void PreCreate(CREATESTRUCT & cs) {
		// ���� ���������� ������ ���������� ���������. � �������������
		// �������� �� ���������������, ������� ������ ���� ������
		cs.style &= ~WS_VISIBLE;

		// NOTE: ����� ���������� �������� ������ �� ������ ��������� � ������,
		// ����� ���������� cs.style != 0
		cs.style |= WS_BORDER;

		// NOTE: ������� �������� ���������, ����� �������� ����� �������� ������.
		// ���� ������� ���������� ������ CWnd
		CWnd::PreCreate(cs);
	}

	virtual void OnCreate() {
		CWnd::OnCreate();
		trayIcon::create(GetHwnd());
	}

	virtual LRESULT WndProc(HWND window, UINT message, WPARAM wparam, LPARAM lparam) {

		// ��������� �� ������ � ����
		if (message == mainWindow::TrayIconMessage && wparam == mainWindow::TrayIconId)
			// NOTE: �� ��������� �������������, �� ��������� ������������ ������, ����� ������� ���� ��������
			switch (lparam) {
				case WM_CONTEXTMENU:
				case WM_RBUTTONUP:
					if (settingsWindow::isShown()) 
						MessageBeep(-1);
					else
						trayIcon::showMenu();
					return 0;
				case NIN_KEYSELECT:
				case NIN_SELECT:
				case WM_LBUTTONUP:
					if (settingsWindow::isShown()) 
						MessageBeep(-1);
					else
						settingsWindow::show();
					return 0;
			}
		
		if (message == WM_DESTROY) {
		
			// ��������������� ������ � ����. Ÿ ������ ���������� � ������ MAIN,
			// �.�. ������ ��������� � HWND ����, � � ������ MAIN ��� �������� �� ���������
			trayIcon::destroy();

			// ���������� ����������
			PostQuitMessage(0);
			return 0;
		}

		return CWnd::WndProc(window, message, wparam, lparam);
	}

	virtual BOOL OnCommand(WPARAM wparam, LPARAM lparam) {
		unsigned int code = HIWORD(wparam);
		unsigned int id = LOWORD(wparam);
		HWND hwnd = reinterpret_cast<HWND>(lparam);

		// ��������� �� ���� (������ � ����)
		if (hwnd == 0 && code == 0)
			switch (id) {
				case ID_TRAYICONMENU_SETTINGS:
					settingsWindow::show();
					return 0;
				case ID_TRAYICONMENU_EXIT:
					DestroyWindow();
					return 0;
			}
		return CWnd::OnCommand(wparam, lparam);
	}

} MyMainWindow;

namespace mainWindow {

	void create() {
		MyMainWindow.Create();
	}

}