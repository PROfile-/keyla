//
// ������ LAYOUT_LIST ���������� ��������� ������ ���������,
// ���������� ������������� � �������
// 

#pragma once

#include <vector>

namespace layoutList {

	// ������ ��� �������� ������ ���������
	extern std::vector<HKL> GuiLayoutList;

	// ��������� ������ ���������
	void load();

	// ��������������� �������, ������������ language id ��������� � ���� ������
	tstring layoutLangId(HKL layout);

	// ��������������� �������, ������������ �������� �����, ���������������� ���������
	tstring layoutLanguage(HKL layout);
}