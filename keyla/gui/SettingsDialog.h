#pragma once

#include "Brush.h"
#include "../settings.h"
#include "../../win32pp/Dialog.h"

class SettingsDialog : public CDialog {

	friend class LayoutList;

public:

	// �����������
	SettingsDialog();

protected:

	virtual BOOL OnInitDialog();
	virtual BOOL DialogProc(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
	virtual BOOL OnCommand(WPARAM wparam, LPARAM lparam);
	virtual LRESULT OnNotify(WPARAM wparam, LPARAM lparam);

private:

	// ��������� ��������� ���������
	void apply();

	// ��������� ����� ��������
	settings::SettingsStruct m_settings;

	// ����� ��� ���� ��������� ����������. �����, ���������
	// ��� ������� ���������� �� ���� ����������� ����
	static Brush BackgroundBrush;
	
};