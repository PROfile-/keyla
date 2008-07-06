//
// ��������������� ������ FATAL_ERROR ������������� ��������� FatalError
//

#pragma once

#include <exception>

// ����������, ������� ������� ��������� � ������ ������������ ������,
// �������������� ����������� ���������������� ���������. ����������
// ����� ����������� � ������ MAIN, ������� ������� ���� ��������������
class FatalError : public std::exception {
public:

	// �������� ��������� �������� ��������� ������ � ���������� Win32 (��. GetLastError)
	static tstring lastWin32Error();

	// �����������
	// message - �������� ������
	FatalError(const tstring & message) : m_message(message) {
	}

	// �������� �������� ������
	const tstring & message() const {
		return m_message;
	}

private:

	// �������� ������
	const tstring m_message;
};


