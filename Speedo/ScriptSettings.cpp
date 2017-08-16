#include "ScriptSettings.hpp"

#include <vector>
#include <simpleini/SimpleIni.h>

#include "Util/Util.hpp"

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
	
	settingsGeneral.SetValue("SPEEDO", "Name", SpeedoSettings.SpeedoName.c_str());
	settingsGeneral.SetDoubleValue("SPEEDO", "RPMBgXpos", SpeedoSettings.RPMBgXpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "RPMBgYpos", SpeedoSettings.RPMBgYpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "RPMBgSize", SpeedoSettings.RPMBgSize);

	settingsGeneral.SetDoubleValue("SPEEDO", "RPMNumXpos", SpeedoSettings.RPMNumXpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "RPMNumYpos", SpeedoSettings.RPMNumYpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "RPMNumSize", SpeedoSettings.RPMNumSize);

	settingsGeneral.SetDoubleValue("SPEEDO", "RPMDialXpos", SpeedoSettings.RPMDialXpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "RPMDialYpos", SpeedoSettings.RPMDialYpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "RPMDialSize", SpeedoSettings.RPMDialSize);

	settingsGeneral.SetDoubleValue("SPEEDO", "TurboBgXpos", SpeedoSettings.TurboBgXpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "TurboBgYpos", SpeedoSettings.TurboBgYpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "TurboBgSize", SpeedoSettings.TurboBgSize);
	
	settingsGeneral.SetDoubleValue("SPEEDO", "TurboNumXpos", SpeedoSettings.TurboNumXpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "TurboNumYpos", SpeedoSettings.TurboNumYpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "TurboNumSize", SpeedoSettings.TurboNumSize);

	settingsGeneral.SetDoubleValue("SPEEDO", "TurboDialXpos", SpeedoSettings.TurboDialXpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "TurboDialYpos", SpeedoSettings.TurboDialYpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "TurboDialSize", SpeedoSettings.TurboDialSize);

	settingsGeneral.SetDoubleValue("SPEEDO", "SpeedXpos", SpeedoSettings.SpeedXpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "SpeedYpos", SpeedoSettings.SpeedYpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "SpeedSize", SpeedoSettings.SpeedSize);

	settingsGeneral.SetDoubleValue("SPEEDO", "UnitXpos", SpeedoSettings.UnitXpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "UnitYpos", SpeedoSettings.UnitYpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "UnitSize", SpeedoSettings.UnitSize);


	settingsGeneral.SetDoubleValue("SPEEDO", "GearXpos", SpeedoSettings.GearXpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "GearYpos", SpeedoSettings.GearYpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "GearSize", SpeedoSettings.GearSize);

	settingsGeneral.SaveFile(settingsGeneralFile.c_str());
}

void ScriptSettings::parseSettingsGeneral() {
	if (!FileExists(settingsGeneralFile)) {
		SaveGeneral();
	}
	CSimpleIniA settingsGeneral;
	settingsGeneral.SetUnicode();
	settingsGeneral.LoadFile(settingsGeneralFile.c_str());

	SpeedoSettings.SpeedoName = settingsGeneral.GetValue("SPEEDO", "Name");
	SpeedoSettings.RPMBgXpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "RPMBgXpos"));
	SpeedoSettings.RPMBgYpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "RPMBgYpos"));
	SpeedoSettings.RPMBgSize = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "RPMBgSize"));

	SpeedoSettings.RPMNumXpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "RPMNumXpos"));
	SpeedoSettings.RPMNumYpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "RPMNumYpos"));
	SpeedoSettings.RPMNumSize = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "RPMNumSize"));

	SpeedoSettings.RPMDialXpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "RPMDialXpos"));
	SpeedoSettings.RPMDialYpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "RPMDialYpos"));
	SpeedoSettings.RPMDialSize = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "RPMDialSize"));

	SpeedoSettings.TurboBgXpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "TurboBgXpos"));
	SpeedoSettings.TurboBgYpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "TurboBgYpos"));
	SpeedoSettings.TurboBgSize = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "TurboBgSize"));
	
	SpeedoSettings.TurboNumXpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "TurboNumXpos"));
	SpeedoSettings.TurboNumYpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "TurboNumYpos"));
	SpeedoSettings.TurboNumSize = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "TurboNumSize"));

	SpeedoSettings.TurboDialXpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "TurboDialXpos"));
	SpeedoSettings.TurboDialYpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "TurboDialYpos"));
	SpeedoSettings.TurboDialSize = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "TurboDialSize"));

	SpeedoSettings.SpeedXpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "SpeedXpos"));
	SpeedoSettings.SpeedYpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "SpeedYpos"));
	SpeedoSettings.SpeedSize = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "SpeedSize"));

	SpeedoSettings.UnitXpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "UnitXpos"));
	SpeedoSettings.UnitYpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "UnitYpos"));
	SpeedoSettings.UnitSize = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "UnitSize"));

	SpeedoSettings.GearXpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "GearXpos"));
	SpeedoSettings.GearYpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "GearYpos"));
	SpeedoSettings.GearSize = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "GearSize"));
}
