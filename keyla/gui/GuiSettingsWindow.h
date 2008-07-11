#pragma once

#include "GuiLayoutList.h"
#include "GuiHotKey.h"
#include "../../win32xx/PropertySheet.h"

class GuiSettingsWindow : public CPropertySheet {
public:

	// ����������
	GuiSettingsWindow();

	// ��������� ��������� ���������. ����� ���������� �� ������� ������ FirstPage
	void apply();

private:

	// �����, �� �������� ������ ������������� ����� ������ ��������
	class Page : public CPropertyPage {
	public:

		// �����������
		Page(GuiSettingsWindow & parent, int resourceId, LPCTSTR title);

		virtual void OnSetActive();
		virtual void OnApply();
		virtual void OnOK();

		// ��������� ��������� ���������. ����� ���������� �� ������� ������ GuiSettingsWindow
		virtual void apply() = 0;

	private:

		GuiSettingsWindow * m_parent;
	};

	class CommonPropsPage : public Page {
	public:

		CommonPropsPage(GuiSettingsWindow & parent);

		virtual BOOL OnInitDialog();

		virtual void apply();

	private:		

		GuiHotKey m_mainKeyEdit;
	};

	class LayoutPropsPage : public Page {
	public:

		LayoutPropsPage(GuiSettingsWindow & parent);

		virtual BOOL OnInitDialog();

		virtual void apply();

	private:

		GuiLayoutList m_layoutList;
	};
};
