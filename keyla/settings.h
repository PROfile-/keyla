//
// ������ SETTINGS �������� ������� �������� ��������� �� ���������������� ������
// � ������� �������� ��������� � ���. ��� ����� ������ ������������� ������� load � save
//

#pragma once

#include "gui/Icon.h"
#include "util/HotKey.h"

#include <vector>

namespace settings {

	//
	// ������������ ������, �������� ��������� ���������.
	// ���������������� � ������ load
	//
	extern struct SettingsStruct {
		SettingsStruct();

		// ��������� ������ ��� ������������ �� ��������� ���������
		HotKey mainHotKey;
		// ��������� ������������ ��� ������������ ��������� ������, ������������� � �������
		bool skipSystemHotKey;
		// ������������ �� ���� ���������� ���������, � �� ���� ��� ������� ����
		bool globalLayout;
		// ��������� ������ ��� ������������ �� ���������� ���������
		std::vector<HotKey> layoutHotKeys;
		// ������� ������ ����������
		Icon mainIcon;
	} Settings;

	void load();

	void save();
}