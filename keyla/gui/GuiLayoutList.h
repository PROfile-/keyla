#pragma once

#include "HotKeyEdit.h"
#include "../../win32pp/WinCore.h"

class LayoutList;
class SettingsDialog;

//
// �������������� ����� �������� ���������� ��� ������ ��������� ������
// ��� ����� ��������� � ������
//
class HotKeyEditDelegate : public HotKeyEdit {
public:

	// �����������
	HotKeyEditDelegate();

	// ��������������� ������ �������� ������. ����� ������ ���������
	// �� ������ HWND ������������� ����, �� ������ �� LayoutList
	HWND Create(LayoutList & layoutList);

protected:

	virtual LRESULT WndProc(HWND window, UINT message, WPARAM wparam, LPARAM lparam);

private:

	// ������ �� ������ ���������, ������� ������� ���������
	LayoutList * m_layoutList;
};

//
// ����� �������� ���������� ��� ������ ������ ���������
// � �������������� ��� ������ �� ��� ��������� ������
//
// ������� ���������� ������������ � �������������
// �������� ���������� ListView � ������� Attach.
// ��������������, ��� ������� ���������� ����� ����� Report.
//
class LayoutList : public CWnd{
public:

	// �����������
	LayoutList();

	// ���������������� ���������� �������� ����������.
	// ����� update ���������� �������������
	// settingsWindow - ����, � ������� ���������� ������� ����������
	void initialize(SettingsDialog & settingsDialog);

	// �������� ���������� �������� ����������
	void update();

	// ����� ���������� �� ������� m_delegate, ����� � �������� ��� ���� �����.
	// �������� ���������� ������� � �������, � ������� ��������
	void delegateDeactivated();

protected:

	virtual LRESULT WndProc(HWND window, UINT message, WPARAM wparam, LPARAM lparam);

private:

	// ���������� ����, �������� �����������
	SettingsDialog * m_settingsDialog;

	// ������, ������� ���������������, ���� ��� ������������� ��������� ������
	// (������� � ������� �������)
	bool m_delegateActive;

	// �������������� ����� �������� ���������� ��� ������ ��������� ������
	// ��� ����� ��������� � ������
	HotKeyEditDelegate m_delegate;
	
	// ���, � ������� ������������� �������, ��� 0, ���� � ������ ������ ������� �����
	unsigned int m_delegateRow;
};