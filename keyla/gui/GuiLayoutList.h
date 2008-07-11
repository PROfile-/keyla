#pragma once

#include "GuiHotKey.h"
#include "../../win32xx/WinCore.h"

#include <vector>

class GuiLayoutList;

//
// �������������� ����� �������� ���������� ��� ������ ��������� ������
// ��� ����� ��������� � ������
//
class HotKeyEditDelegate : public GuiHotKey {
public:

	// �����������
	HotKeyEditDelegate();

	// ��������������� ������ �������� ������. ����� ������ ���������
	// �� ������ HWND ������������� ����, �� ������ �� GuiLayoutList
	HWND Create(GuiLayoutList & layoutList);

protected:

	virtual LRESULT WndProc(HWND window, UINT message, WPARAM wparam, LPARAM lparam);

private:

	// ������ �� ������ ���������, ������� ������� ���������
	GuiLayoutList * m_layoutList;
};

//
// ����� �������� ���������� ��� ������ ������ ���������
// � �������������� ��� ������ �� ��� ��������� ������
//
// ������� ���������� ������������ � �������������
// �������� ���������� ListView � ������� Attach.
// ��������������, ��� ������� ���������� ����� ����� Report.
//
class GuiLayoutList : public CWnd{
public:

	// �����������
	GuiLayoutList();

	// ���������������� ���������� �������� ����������.
	// ����� update ���������� �������������
	// settingsWindow - ����, � ������� ���������� ������� ����������
	void initialize();

	// �������� ���������� �������� ����������
	void update();

	// ��������� ��������� ��������� (������ �� � ���������� ���������)
	void apply();

	// ����� ���������� �� ������� m_delegate, ����� � �������� ��� ���� �����.
	// �������� ���������� ������� � �������, � ������� ��������
	void delegateDeactivated();

protected:

	virtual LRESULT WndProc(HWND window, UINT message, WPARAM wparam, LPARAM lparam);

private:

	// ��������� ����� �������� ��������� ������ ��� ���������
	std::vector<HotKey> m_layoutHotKeys;

	// ������, ������� ���������������, ���� ��� ������������� ��������� ������
	// (������� � ������� �������)
	bool m_delegateActive;

	// �������������� ����� �������� ���������� ��� ������ ��������� ������
	// ��� ����� ��������� � ������
	HotKeyEditDelegate m_delegate;
	
	// ���, � ������� ������������� �������, ��� 0, ���� � ������ ������ ������� �����
	unsigned int m_delegateRow;
};