//
// ��������������� ������ HOTKEY ������������� ����� HotKey
//

#pragma once

// ����� ��� �������� ��������� ������
class HotKey {
public:

	// ������������ ������
	enum Modifiers {
		// ����� Ctrl
		LControl  = 1,
		// ����� Alt
		LAlt      = 2,
		// ����� Shift
		LShift    = 4,
		// ������ Ctrl
		RControl  = 8,
		// ������ Alt
		RAlt      = 16,
		// ������ Shift
		RShift    = 32,
		// ������ "����������� �������"
		Extended  = 128,
	};

	// �������� �������� ������� ��� ����������� ������������
	// vk - ����������� ��� �������
	// extended - ���� "����������� �������"
	static tstring keyName(unsigned int vk, bool extended = false);


	// �����������
	HotKey();

	// �����������
	// vk - ����������� ��� �������
	// modifiers - ����� ������ �� ������������ Modifiers
	HotKey(unsigned int vk, unsigned int modifiers);


	bool operator==(const HotKey & other) const;


	// �����-"������"
	// vk - ����������� ��� �������
	// modifiers - ����� ������ �� ������������ Modifiers
	void set(unsigned int vk, unsigned int modifiers);

	// �������� ��������� ������
	void clear();


	// �������� ����������� ��� �������
	unsigned int vk() const;

	// �������� ������������ - ����� ������ �� ������������ Modifiers
	unsigned int modifiers() const;

	// �������� ������, ����������� ��������� ������, ��� ������ ������������
	const tstring & text() const;
	

	// ��������� ������ �� �������
	// hkey - ���� ��� ������ ������� (HKEY_CURRENT_USER)
	// key - ������� �������
	void loadFromRegistry(HKEY hkey, const tstring & key);

	// ��������� ������ � ������
	// hkey - ���� ��� ������ ������� (HKEY_CURRENT_USER)
	// key - ������� �������
	void saveToRegistry(HKEY hkey, const tstring & key);

private:

	// ��������� m_text �������� m_vk � m_modifiers
	void makeText();
	
	// ����������� ��� �������
	unsigned int m_vk;

	// ����� ������ �� ������������ Modifiers
	unsigned int m_modifiers;

	// ������, ����������� ��������� ������, ��� ������ ������������
	// NOTE: ��������� ��� ��������� m_modifiers �/��� m_vk
	tstring m_text;

	// ����������� � ��������� ������������� ��������� ������
	static const tstring Separator;
};
