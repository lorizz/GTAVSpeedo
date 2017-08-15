#define NOMINMAX
#include <string>

#include "inc/main.h"
#include "script.h"
#include "menu.h"

#include "ScriptSettings.hpp"
#include "Util/Util.hpp"
#include "Util/Versions.h"
#include "inc/natives.h"
#include "menukeyboard.h"

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

	}

	menu.EndMenu();
}
