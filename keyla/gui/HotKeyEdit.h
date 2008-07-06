#pragma once

#include "Menu.h"
#include "../util/HotKey.h"
#include "../../win32pp/WinCore.h"

//
// ����� �������� ���������� ��� ����� ��������� ������
//
// ������� ���������� ����� ������� � ������� ������ Create
// ��� ��������� � ������������� ���� ����� � ������� Attach.
// ��� ������������� Create ������� ���������� �������� ���������.
// ��� ������������� Attach ��������������, ��� ���� ����� ��������� (disabled)
//
class HotKeyEdit : public CWnd{
public:

	// �����������
	HotKeyEdit();

	// ���������� ��������� ������
	void setHotKey(const HotKey & hotKey);

	// ���������� ��������� ������.
	// �������� ���������� ��. � ������������ � ������ HotKey::set
	void setHotKey(unsigned int vk, unsigned int modifiers);

	// �������� ��������� ������.
	// �������� ���������� ��. � ������������ � ������ HotKey::set
	void clearHotKey();

	// �������� ������ �� ������, � ������� �������� ������������� ��������� ������
	const HotKey & hotKey() const;

protected:

	virtual void PreCreate(CREATESTRUCT & cs);
	virtual LRESULT WndProc(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
	virtual BOOL OnCommand(WPARAM wparam, LPARAM lparam);

private:

	// ���������������� ������� ����������
	void initialize();

	// ��������, ������� ������������ ��� ����������� �������������
	// ������ ������ initialize � ������� ����
	HWND m_lastInitializedHwnd;

	// ������������� ��������� ������
	HotKey m_hotKey;


	// ��������� �� ��������� ������, ������� ������������� �������� ����������,
	// �� ������� � ��������� ������ ��������� �����. ��� ������� ���������
	static HotKeyEdit * ActiveInstance;


	// ��� �� ����������. ������ ��� ���� WH_KEYBOARD_LL, ��������� ������
	// � ��� ������� ����� �������� ����� "���������" ��������� ������, ��� Win-D
	static LRESULT CALLBACK keyboardHook(int code, WPARAM wparam, LPARAM lparam);

	// ��� �� ����������
	static HHOOK KeyboardHook;

	// ������������, ������� ������� �� ����� �������� ����
	// (����� ������ HotKey::Modifiers)
	static unsigned int Modifiers;

	// ����������� ����
	static Menu ContextMenu;
};