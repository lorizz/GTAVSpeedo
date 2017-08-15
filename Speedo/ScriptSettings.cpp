#include "ScriptSettings.hpp"

#include <string>

#include "simpleini/SimpleIni.h"
#include "Util/Logger.hpp"

#include "Util/Versions.h"

ScriptSettings::ScriptSettings() { }

void ScriptSettings::SetFiles(const std::string &general) {
	settingsGeneralFile = general;
}

void ScriptSettings::Read() {
	parseSettingsGeneral();
}

void ScriptSettings::SaveGeneral() const {
	CSimpleIniA settingsGeneral;
	settingsGeneral.SetUnicode();
	settingsGeneral.LoadFile(settingsGeneralFile.c_str());
	
	

	settingsGeneral.SaveFile(settingsGeneralFile.c_str());
}

void ScriptSettings::parseSettingsGeneral() {
#pragma warning(push)
#pragma warning(disable: 4244) // Make everything doubles later...
	CSimpleIniA settingsGeneral;
	settingsGeneral.SetUnicode();
	settingsGeneral.LoadFile(settingsGeneralFile.c_str());

	
#pragma warning(pop)

}
