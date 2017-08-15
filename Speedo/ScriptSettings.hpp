#pragma once
#include <Windows.h>

#include <vector>
#include "simpleini/SimpleIni.h"

class Logger;

class ScriptSettings {
public:
	ScriptSettings();
	void SetFiles(const std::string &general);
	void Read();
	void SaveGeneral() const;

private:
	void parseSettingsGeneral();

	std::string settingsGeneralFile;
	std::string settingsMenuFile;
};
