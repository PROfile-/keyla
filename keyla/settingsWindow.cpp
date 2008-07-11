#include "common.h"

#include "gui/GuiSettingsWindow.h"
#include "mainWindow.h"
#include "settingsWindow.h"

// ������ ���������������, ����� ���� �������� �������
static bool shown = false;

namespace settingsWindow {

	void show() {
		assert(!shown);

		shown = true;
		GuiSettingsWindow().DoModal();
		shown = false;
	}

	bool isShown() {
		return shown;
	}

}