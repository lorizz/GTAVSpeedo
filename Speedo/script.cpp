#define NOMINMAX
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>

#include "../../ScriptHookV_SDK/inc/natives.h"
#include "../../ScriptHookV_SDK/inc/enums.h"
#include "../../ScriptHookV_SDK/inc/main.h"
#include "../../ScriptHookV_SDK/inc/types.h"

#include "script.h"

#include "ScriptSettings.hpp"

#include "Util/Logger.hpp"
#include "Util/Util.hpp"
#include "Util/Paths.h"

#include "menu.h"
#include "../../GTAVManualTransmission/Gears/Memory/NativeMemory.hpp"
#include "Util/MathExt.h"
#include "../../GTAVManualTransmission/Gears/Memory/VehicleExtensions.hpp"

std::string settingsGeneralFile;
std::string settingsMenuFile;

NativeMenu::Menu menu;
ScriptSettings settings;

Player player;
Ped playerPed;
Vehicle vehicle;
VehicleExtensions ext;

int prevNotification = 0;


void update() {
	///////////////////////////////////////////////////////////////////////////
	//                     Are we in a supported vehicle?
	///////////////////////////////////////////////////////////////////////////
	player = PLAYER::PLAYER_ID();
	playerPed = PLAYER::PLAYER_PED_ID();

	if (!ENTITY::DOES_ENTITY_EXIST(playerPed) ||
		!PLAYER::IS_PLAYER_CONTROL_ON(player) ||
		ENTITY::IS_ENTITY_DEAD(playerPed) ||
		PLAYER::IS_PLAYER_BEING_ARRESTED(player, TRUE)) {
		return;
	}

	vehicle = PED::GET_VEHICLE_PED_IS_IN(playerPed, false);

	if (!vehicle || !ENTITY::DOES_ENTITY_EXIST(vehicle) || 
		playerPed != VEHICLE::GET_PED_IN_VEHICLE_SEAT(vehicle, -1)) {
		return;
	}

}

enum eDecorType
{
	DECOR_TYPE_FLOAT = 1,
	DECOR_TYPE_BOOL,
	DECOR_TYPE_INT,
	DECOR_TYPE_UNK,
	DECOR_TYPE_TIME
};

// @Unknown Modder
BYTE* g_bIsDecorRegisterLockedPtr = nullptr;
bool setupGlobals() {
	auto addr = mem::FindPattern("\x40\x53\x48\x83\xEC\x20\x80\x3D\x00\x00\x00\x00\x00\x8B\xDA\x75\x29",
								 "xxxxxxxx????xxxxx");
	if (!addr)
		return false;

	g_bIsDecorRegisterLockedPtr = (BYTE*)(addr + *(int*)(addr + 8) + 13);
	*g_bIsDecorRegisterLockedPtr = 0;

	if (!DECORATOR::DECOR_IS_REGISTERED_AS_TYPE("mt_gear", DECOR_TYPE_INT)) {
		DECORATOR::DECOR_REGISTER("mt_gear", DECOR_TYPE_INT);
		logger.Write("DECOR: Registered \"mt_gear\" as DECOR_TYPE_INT");
	}

	*g_bIsDecorRegisterLockedPtr = 1;
	return true;
}

void main() {
	logger.Write("Script started");

	logger.Write("Setting up globals");
	if (!setupGlobals()) {
		logger.Write("Global setup failed!");
	}

	std::string absoluteModPath = Paths::GetModuleFolder(Paths::GetOurModuleHandle()) + modDir;
	settingsGeneralFile = absoluteModPath + "\\settings_general.ini";
	settingsMenuFile = absoluteModPath + "\\settings_menu.ini";

	settings.SetFiles(settingsGeneralFile);

	menu.RegisterOnMain(std::bind(menuInit));
	menu.RegisterOnExit(std::bind(menuClose));
	menu.SetFiles(settingsMenuFile);
	
	while (true) {
		update();
		update_menu();
		WAIT(0);
	}
}

void ScriptMain() {
	srand(GetTickCount());
	main();
}
