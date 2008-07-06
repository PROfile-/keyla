//
// ������ LAYOUT_LIST ���������� ��������� ������ ���������,
// ���������� ������������� � �������
// 

#pragma once

#include <vector>

namespace layoutList {

	// ������ ��� �������� ������ ���������
	extern std::vector<HKL> LayoutList;

	// ��������� ������ ���������
	void load();

	// ��������������� �������, ������������ language id ��������� � ���� ������
	tstring layoutLangId(HKL layout);

	// ��������������� �������, ������������ �������� �����, ���������������� ���������
	tstring layoutLanguage(HKL layout);
}