//
// ������������ ����, ������� ���������� �� ��� ����� � �������� �����
// ���������� ����� ������������ ������������ ����� � ���������� ��������������� ������.
//

#pragma once

#define _WIN32_WINNT 0x0400
#define _WIN32_IE  0x0500

#include <windows.h>
#include <tchar.h>

// ���������� ����������� ���� � ��� �����, ��� ������ ��������� ������ ����.
// ��-�� ����������� ������� TrackPopupMenu ���������� ���� ������ ���������
// ������������ �������, ������� ���������� � ����� ����������
// 
// menu - ����, ��. ����������� ����
// window - ����, �������� ��� ������ ������ ���� ����� ��������� WM_COMMAND
//
void showContextMenu(HMENU menu, HWND window);

#include <cassert>
#ifdef _DEBUG
#define verify(e) assert(e)
#else
#define verify(e) ;e;
#endif

#include <string>
#ifdef _UNICODE
typedef std::wstring tstring;
#else
typedef std::string tstring;
#endif

#include <sstream>
#ifdef _UNICODE
typedef std::wstringstream tstringstream;
#else
typedef std::stringstream tstringstream;
#endif
