#include "../common.h"
#include "GuiLayoutList.h"
#include "HotKeyEdit.h"
#include "SettingsDialog.h"
#include "../settings.h"
#include "../res/resource.h"

#include <algorithm>
using namespace std;

static HotKeyEdit MainKeyEdit;
static LayoutList MyLayoutList;

Brush SettingsDialog::BackgroundBrush(GetSysColor(COLOR_3DHILIGHT));

SettingsDialog::SettingsDialog() : CDialog(IDD_SETTINGS) {
}

/* virtual */ BOOL SettingsDialog::OnInitDialog() {
	CDialog::OnInitDialog();

	// ��������� ������ � ���������
	SendMessage(GetHwnd(), WM_SETICON, ICON_SMALL,
		        reinterpret_cast<LPARAM>(static_cast<HICON>(settings::Settings.mainIcon)));

	// ������������� �������
	HWND tabs = GetDlgItem(ID_SETTINGS_TABS);
	TCITEM tci = {TCIF_TEXT};
	tci.pszText = TEXT("�����");
	TabCtrl_InsertItem(tabs, 0, &tci);
	tci.pszText = TEXT("���������");
	TabCtrl_InsertItem(tabs, 1, &tci);

	// ����������� ��������� ����������
	verify(MainKeyEdit.Attach(GetDlgItem(ID_SETTINGS_EDIT_KEY)));
	verify(MyLayoutList.Attach(GetDlgItem(ID_SETTINGS_LIST_LAYOUTS)));

	// ���������� ��������� ����� ��������
	m_settings = settings::Settings;

	// ��������� ��������� ���������� � ������������ � �����������
	MainKeyEdit.setHotKey(m_settings.mainHotKey);
	if (m_settings.globalLayout) {
		CheckDlgButton(GetHwnd(), ID_SETTINGS_CHECK_GLOBALLAYOUT, BST_CHECKED);
	}
	if (m_settings.skipSystemHotKey) {
		CheckDlgButton(GetHwnd(), ID_SETTINGS_CHECK_EATWINDOWSKEY, BST_CHECKED);
	}
	MyLayoutList.initialize(*this);

	// ��������� ������� ������� ������� ���������� � ���������� �� ���� �����
	return TRUE;
}

/* virtual */ BOOL SettingsDialog::DialogProc(HWND window, UINT message, WPARAM wparam, LPARAM lparam) {
	
	switch (message) {

		// �������� ������� ���� ��������� ����������, ����� �� �� ��������� �� ����� ���� �������
		case WM_CTLCOLORBTN:
		case WM_CTLCOLOREDIT:
		case WM_CTLCOLORLISTBOX:
		case WM_CTLCOLORSCROLLBAR:
		case WM_CTLCOLORSTATIC:			
			return (BOOL)static_cast<HBRUSH>(BackgroundBrush);

		case WM_KILLFOCUS:
			MyLayoutList.delegateDeactivated();
			return TRUE;
		case WM_DESTROY:
			MainKeyEdit.Detach();
			MyLayoutList.Detach();
			return TRUE;
	}
	return CDialog::DialogProc(window, message, wparam, lparam);
}

/* virtual */ BOOL SettingsDialog::OnCommand(WPARAM wparam, LPARAM lparam) {
	unsigned int code = HIWORD(wparam);
	unsigned int id = LOWORD(wparam);
	HWND hwnd = reinterpret_cast<HWND>(lparam);

	// ��������� � ������� ������
	if (code == BN_CLICKED)
		switch (id) {
			case ID_SETTINGS_BUTTON_APPLY:
				apply();
				return TRUE;
			case ID_SETTINGS_BUTTON_OK:
				apply();
				EndDialog(0);
				return TRUE;
			case ID_SETTINGS_BUTTON_CANCEL:
				EndDialog(0);
				return TRUE;
		}
	return FALSE;
}

/* virtual */ LRESULT SettingsDialog::OnNotify(WPARAM wparam, LPARAM lparam) {
	const NMHDR * p = reinterpret_cast<const NMHDR *>(lparam);
	if (p == 0) return FALSE;
	
	// ��������� �� Tab-Control'�
	if (p->idFrom == ID_SETTINGS_TABS) {
		switch (p->code) {
			// ����� ������������� ������� �������� ����������, ��������� � ������� ��������, ��������
			case TCN_SELCHANGING:
                switch (TabCtrl_GetCurFocus(p->hwndFrom)) {
					case 0: // �����
						ShowWindow(GetDlgItem(ID_SETTINGS_COMMON_STATIC1),      SW_HIDE);
						ShowWindow(GetDlgItem(ID_SETTINGS_EDIT_KEY),            SW_HIDE);
						ShowWindow(GetDlgItem(ID_SETTINGS_CHECK_EATWINDOWSKEY), SW_HIDE);
						ShowWindow(GetDlgItem(ID_SETTINGS_CHECK_GLOBALLAYOUT),  SW_HIDE);
						break;
					case 1: // ���������
						ShowWindow(GetDlgItem(ID_SETTINGS_LIST_LAYOUTS),        SW_HIDE);
						break;
				}
				break;
			// ����� ����� ������������ ������� �������� ����������, ��������� � ����� ��������, ����������
			case TCN_SELCHANGE:
				switch (TabCtrl_GetCurFocus(p->hwndFrom)) {
					case 0: // �����
						ShowWindow(GetDlgItem(ID_SETTINGS_COMMON_STATIC1),      SW_SHOW);
						ShowWindow(GetDlgItem(ID_SETTINGS_EDIT_KEY),            SW_SHOW);
						ShowWindow(GetDlgItem(ID_SETTINGS_CHECK_EATWINDOWSKEY), SW_SHOW);
						ShowWindow(GetDlgItem(ID_SETTINGS_CHECK_GLOBALLAYOUT),  SW_SHOW);
						SetFocus(GetDlgItem(ID_SETTINGS_EDIT_KEY));
						break;
					case 1: // ���������
						ShowWindow(GetDlgItem(ID_SETTINGS_LIST_LAYOUTS),        SW_SHOW);
						SetFocus(GetDlgItem(ID_SETTINGS_LIST_LAYOUTS));
						break;
				}
				break;
		}
		return TRUE;
	}
	return CDialog::OnNotify(wparam, lparam);
}

void SettingsDialog::apply() {
	
	// ��������� �������� � ������������ � ���������� ��������� ����������
	
	settings::Settings.mainHotKey = MainKeyEdit.hotKey();
	settings::Settings.globalLayout = (IsDlgButtonChecked(GetHwnd(), ID_SETTINGS_CHECK_GLOBALLAYOUT) != 0);
	settings::Settings.skipSystemHotKey = (IsDlgButtonChecked(GetHwnd(), ID_SETTINGS_CHECK_EATWINDOWSKEY) != 0);
	swap(settings::Settings.layoutHotKeys, m_settings.layoutHotKeys);

	settings::save();
}
