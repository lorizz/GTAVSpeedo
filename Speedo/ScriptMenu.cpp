#define NOMINMAX

#include "script.h"
#include "menu.h"

#include "ScriptSettings.hpp"
#include "Util/Versions.h"

extern ScriptSettings settings;
extern std::string settingsGeneralFile;

extern NativeMenu::Menu menu;

extern ScriptSettings settings;


///////////////////////////////////////////////////////////////////////////////
//                             Menu stuff
///////////////////////////////////////////////////////////////////////////////
void menuInit() {

}

void menuClose() {
	settings.SaveGeneral();
}

void update_menu() {
	menu.CheckKeys();

	/* Yes hello I am root */
	if (menu.CurrentMenu("mainmenu")) {
		menu.Title("Speedometer");
		menu.Subtitle(DISPLAY_VERSION, false);
		if (menu.Option("Reload pos") ) {
			settings.Read();
		}
		int currUnit = (int)settings.Unit;
		if (menu.StringArray("Units", { "km/h", "mph" }, currUnit)) {
			if (currUnit != (int)settings.Unit) {
				settings.Unit = (UnitType)currUnit;
			}
		}
		
		menu.MenuOption("RPM", "rpmposmenu");
		menu.MenuOption("Turbo", "turboposmenu");
		menu.MenuOption("Speed", "speedposmenu");
		menu.MenuOption("Gear", "gearposmenu");
	}

	if (menu.CurrentMenu("rpmposmenu")) {
		menu.Title("RPM");
		menu.Subtitle(DISPLAY_VERSION, false);
		menu.FloatOption("RPMBgXpos", settings.SpeedoSettings.RPMBgXpos, 0.0f, 1.0f, 0.001f);
		menu.FloatOption("RPMBgYpos", settings.SpeedoSettings.RPMBgYpos, 0.0f, 1.0f, 0.001f);
		menu.FloatOption("RPMBgSize", settings.SpeedoSettings.RPMBgSize, 0.0f, 1.0f, 0.001f);
		menu.FloatOption("RPMNumXpos", settings.SpeedoSettings.RPMNumXpos, 0.0f, 1.0f, 0.001f);
		menu.FloatOption("RPMNumYpos", settings.SpeedoSettings.RPMNumYpos, 0.0f, 1.0f, 0.001f);
		menu.FloatOption("RPMNumSize", settings.SpeedoSettings.RPMNumSize, 0.0f, 1.0f, 0.001f);
		menu.FloatOption("RPMDialXpos", settings.SpeedoSettings.RPMDialXpos, 0.0f, 1.0f, 0.001f);
		menu.FloatOption("RPMDialYpos", settings.SpeedoSettings.RPMDialYpos, 0.0f, 1.0f, 0.001f);
		menu.FloatOption("RPMDialSize", settings.SpeedoSettings.RPMDialSize, 0.0f, 1.0f, 0.001f);
	}

	if (menu.CurrentMenu("turboposmenu")) {
		menu.Title("Turbo");
		menu.Subtitle(DISPLAY_VERSION, false);
		menu.FloatOption("TurboBgXpos", settings.SpeedoSettings.TurboBgXpos, 0.0f, 1.0f, 0.001f);
		menu.FloatOption("TurboBgYpos", settings.SpeedoSettings.TurboBgYpos, 0.0f, 1.0f, 0.001f);
		menu.FloatOption("TurboBgSize", settings.SpeedoSettings.TurboBgSize, 0.0f, 1.0f, 0.001f);
		menu.FloatOption("TurboNumXpos", settings.SpeedoSettings.TurboNumXpos, 0.0f, 1.0f, 0.001f);
		menu.FloatOption("TurboNumYpos", settings.SpeedoSettings.TurboNumYpos, 0.0f, 1.0f, 0.001f);
		menu.FloatOption("TurboNumSize", settings.SpeedoSettings.TurboNumSize, 0.0f, 1.0f, 0.001f);
		menu.FloatOption("TurboDialXpos", settings.SpeedoSettings.TurboDialXpos, 0.0f, 1.0f, 0.001f);
		menu.FloatOption("TurboDialYpos", settings.SpeedoSettings.TurboDialYpos, 0.0f, 1.0f, 0.001f);
		menu.FloatOption("TurboDialSize", settings.SpeedoSettings.TurboDialSize, 0.0f, 1.0f, 0.001f);
	}

	if (menu.CurrentMenu("speedposmenu")) {
		menu.Title("Speed");
		menu.Subtitle(DISPLAY_VERSION, false);
		menu.FloatOption("SpeedXpos", settings.SpeedoSettings.SpeedXpos, 0.0f, 1.0f, 0.001f);
		menu.FloatOption("SpeedYpos", settings.SpeedoSettings.SpeedYpos, 0.0f, 1.0f, 0.001f);
		menu.FloatOption("SpeedSize", settings.SpeedoSettings.SpeedSize, 0.0f, 1.0f, 0.001f);

		menu.FloatOption("UnitXpos", settings.SpeedoSettings.UnitXpos, 0.0f, 1.0f, 0.001f);
		menu.FloatOption("UnitYpos", settings.SpeedoSettings.UnitYpos, 0.0f, 1.0f, 0.001f);
		menu.FloatOption("UnitSize", settings.SpeedoSettings.UnitSize, 0.0f, 1.0f, 0.001f);
	}

	if (menu.CurrentMenu("gearposmenu")) {
		menu.Title("Gear");
		menu.Subtitle(DISPLAY_VERSION, false);
		menu.FloatOption("GearXpos", settings.SpeedoSettings.GearXpos, 0.0f, 1.0f, 0.001f);
		menu.FloatOption("GearYpos", settings.SpeedoSettings.GearYpos, 0.0f, 1.0f, 0.001f);
		menu.FloatOption("GearSize", settings.SpeedoSettings.GearSize, 0.0f, 1.0f, 0.001f);
	}

	menu.EndMenu();
}
