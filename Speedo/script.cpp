#define NOMINMAX
#include "script.h"

#include <string>
#include <sstream>
#include <iomanip>

#include <lodepng/lodepng.h>
#include <menu.h>

#include "../../GTAVManualTransmission/Gears/Memory/NativeMemory.hpp"
#include "../../GTAVManualTransmission/Gears/Memory/VehicleExtensions.hpp"

#include "Util/Logger.hpp"
#include "Util/Util.hpp"
#include "Util/Paths.h"
#include "Util/MathExt.h"

#include "ScriptSettings.hpp"

struct WTFABColor {
	float r;
	float g;
	float b;
	float a;
};

struct SpriteInfo {
	int Id;
	unsigned Width;
	unsigned Height;
};

std::string settingsGeneralFile;
std::string settingsMenuFile;
std::string skinDir;

SpriteInfo spriteRPMBg;
SpriteInfo spriteRPMNum;
SpriteInfo spriteRPMDial;

SpriteInfo spriteTurboBg;
SpriteInfo spriteTurboNum;
SpriteInfo spriteTurboDial;

SpriteInfo spriteN0;
SpriteInfo spriteN1;
SpriteInfo spriteN2;
SpriteInfo spriteN3;
SpriteInfo spriteN4;
SpriteInfo spriteN5;
SpriteInfo spriteN6;
SpriteInfo spriteN7;
SpriteInfo spriteN8;
SpriteInfo spriteN9;
SpriteInfo spriteNN;
SpriteInfo spriteNR;
SpriteInfo spriteNE;

SpriteInfo spriteKMH;
SpriteInfo spriteMPH;

float displayRPM = 0.0f;

NativeMenu::Menu menu;
ScriptSettings settings;

Player player;
Ped playerPed;
Vehicle vehicle;
VehicleExtensions ext;
bool hasDashSpeedo = false;

int prevNotification = 0;

float turboalpha = 0.0f;

void drawSpeedo(UnitType type, bool turboActive, bool engineOn) {
	float speed = ext.GetDashSpeed(vehicle);
	if (speed > 0.0f && !hasDashSpeedo) {
		hasDashSpeedo = true;
	}
	if (!hasDashSpeedo) {
		speed = ENTITY::GET_ENTITY_SPEED(vehicle);
	}

	float turbo = ext.GetTurbo(vehicle);
	float rpm = ext.GetCurrentRPM(vehicle);
	int gear = ext.GetGearCurr(vehicle);

	if (!engineOn) rpm = 0.0f;
	SpriteInfo spriteUnit;

	if (type == UnitType::Imperial) {
		speed = speed / 0.44704f;
		spriteUnit = spriteMPH;
	}
	else {
		speed = speed * 3.6f; 
		spriteUnit = spriteKMH;
	}

	float screencorrection = invoke<float>(0xF1307EF624A80D87, FALSE);
	float alpha = 1.0f;

	drawTexture(spriteUnit.Id, 0, -9999, 100,
		settings.SpeedoSettings.UnitSize, static_cast<float>(spriteUnit.Height) * (settings.SpeedoSettings.UnitSize / static_cast<float>(spriteUnit.Width)),
		0.5f, 0.5f,
		settings.SpeedoSettings.UnitXpos, settings.SpeedoSettings.UnitYpos,
		0.0f, screencorrection, 0.54f, 0.69f, 0.93f, 1.0f);

	displayRPM = lerp(displayRPM, rpm, 10.0f * GAMEPLAY::GET_FRAME_TIME());
	float rpmRot = displayRPM / 2.0f + 0.125f;
	float turboRot = turbo / 4.0f + 0.320f;

	drawTexture(spriteRPMBg.Id, 0, -9999, 100, 
		settings.SpeedoSettings.RPMBgSize, static_cast<float>(spriteRPMBg.Height) * (settings.SpeedoSettings.RPMBgSize / static_cast<float>(spriteRPMBg.Width)),
		0.5f, 0.5f, 
		settings.SpeedoSettings.RPMBgXpos, settings.SpeedoSettings.RPMBgYpos,
		0.0f, screencorrection, 1.0f, 1.0f, 1.0f, alpha);
	drawTexture(spriteRPMNum.Id, 0, -9999, 100,
		settings.SpeedoSettings.RPMNumSize, static_cast<float>(spriteRPMNum.Height) * (settings.SpeedoSettings.RPMNumSize / static_cast<float>(spriteRPMNum.Width)),
		0.5f, 0.5f,
		settings.SpeedoSettings.RPMNumXpos, settings.SpeedoSettings.RPMNumYpos,
		0.0f, screencorrection, 0.1f, 0.6f, 0.82f, alpha);
	drawTexture(spriteRPMDial.Id, 0, -9998, 100, 
		settings.SpeedoSettings.RPMDialSize, static_cast<float>(spriteRPMDial.Height) * (settings.SpeedoSettings.RPMDialSize / static_cast<float>(spriteRPMDial.Width)),
		0.5f, 0.5f,
		settings.SpeedoSettings.RPMDialXpos, settings.SpeedoSettings.RPMDialYpos,
		rpmRot, screencorrection, 1.0f, 1.0f, 1.0f, alpha);

	drawTexture(spriteTurboBg.Id, 0, -9999, 100,
		settings.SpeedoSettings.TurboBgSize, static_cast<float>(spriteTurboBg.Height) * (settings.SpeedoSettings.TurboBgSize / static_cast<float>(spriteTurboBg.Width)),
		0.5f, 0.5f,
		settings.SpeedoSettings.TurboBgXpos, settings.SpeedoSettings.TurboBgYpos,
		0.0f, screencorrection, 1.0f, 1.0f, 1.0f, turboalpha);
	drawTexture(spriteTurboNum.Id, 0, -9999, 100,
		settings.SpeedoSettings.TurboNumSize, static_cast<float>(spriteTurboNum.Height) * (settings.SpeedoSettings.TurboNumSize / static_cast<float>(spriteTurboNum.Width)),
		0.5f, 0.5f,
		settings.SpeedoSettings.TurboNumXpos, settings.SpeedoSettings.TurboNumYpos,
		0.0f, screencorrection, 0.1f, 0.6f, 0.82f, turboalpha);
	drawTexture(spriteTurboDial.Id, 0, -9998, 100,
		settings.SpeedoSettings.TurboDialSize, static_cast<float>(spriteTurboDial.Height) * (settings.SpeedoSettings.TurboDialSize / static_cast<float>(spriteTurboDial.Width)),
		0.5f, 0.5f,
		settings.SpeedoSettings.TurboDialXpos, settings.SpeedoSettings.TurboDialYpos,
		turboRot, screencorrection, 1.0f, 1.0f, 1.0f, turboalpha);

	std::stringstream speedoFormat;
	speedoFormat << std::setfill('_') << std::setw(3) << std::to_string(static_cast<int>(std::round(speed)));
	std::string speedoTxt = speedoFormat.str();

	int charNum = 0;
	for (char c : speedoTxt) {
		SpriteInfo si;
		switch (c) {
			case '0': si = spriteN0; break;
			case '1': si = spriteN1; break;
			case '2': si = spriteN2; break;
			case '3': si = spriteN3; break;
			case '4': si = spriteN4; break;
			case '5': si = spriteN5; break;
			case '6': si = spriteN6; break;
			case '7': si = spriteN7; break;
			case '8': si = spriteN8; break;
			case '9': si = spriteN9; break;
			default: si = spriteNE; break;
		}

		drawTexture(si.Id, charNum, -9998, static_cast<int>(GAMEPLAY::GET_FRAME_TIME() * 1500.0f),
			settings.SpeedoSettings.SpeedSize, static_cast<float>(si.Height) * (settings.SpeedoSettings.SpeedSize / static_cast<float>(si.Width)),
			0.5f, 0.5f,
			settings.SpeedoSettings.SpeedXpos + settings.SpeedoSettings.SpeedSize * charNum, settings.SpeedoSettings.SpeedYpos,
			0.0f, screencorrection, 0.0f, 0.5f, 0.74f, 1.0f);
		//showText(settings.SpeedoSettings.SpeedXpos + settings.SpeedoSettings.SpeedSize * charNum, settings.SpeedoSettings.SpeedYpos, 1.0f, std::string(1, c));
		charNum++;
	}

	SpriteInfo spriteGear;
	WTFABColor c = { 0.0f, 0.5f, 0.74f, 1.0f };

	bool neutral = DECORATOR::DECOR_GET_INT(vehicle, "mt_neutral");
	bool shift_indicator = DECORATOR::DECOR_GET_INT(vehicle, "mt_shift_indicator") > 0;

	if (neutral) spriteGear = spriteNN;
	else if (gear == 0) spriteGear = spriteNR;
	else if (gear == 1) spriteGear = spriteN1;
	else if (gear == 2) spriteGear = spriteN2;
	else if (gear == 3) spriteGear = spriteN3;
	else if (gear == 4) spriteGear = spriteN4;
	else if (gear == 5) spriteGear = spriteN5;
	else if (gear == 6) spriteGear = spriteN6;
	else if (gear == 7) spriteGear = spriteN7;
	else spriteGear = spriteN9;

	if (neutral || shift_indicator || ext.GetHandbrake(vehicle)) {
		c.r = 0.99f;
		c.g = 0.5f;
		c.b = 0.25f;
	}

	drawTexture(spriteGear.Id, charNum, -9998, static_cast<int>(GAMEPLAY::GET_FRAME_TIME() * 1500.0f),
		settings.SpeedoSettings.GearSize, static_cast<float>(spriteGear.Height) * (settings.SpeedoSettings.GearSize / static_cast<float>(spriteGear.Width)),
		0.5f, 0.5f,
		settings.SpeedoSettings.GearXpos, settings.SpeedoSettings.GearYpos,
		0.0f, screencorrection, c.r, c.g, c.b, c.a);
}

void update() {
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
	if (VEHICLE::IS_TOGGLE_MOD_ON(vehicle, VehicleToggleModTurbo) && turboalpha < 1.0f) {
		turboalpha += 0.01f;
	}
	if (!VEHICLE::IS_TOGGLE_MOD_ON(vehicle, VehicleToggleModTurbo) && turboalpha > 0.0f) {
		turboalpha -= 0.01f;
	}
	if (turboalpha > 1.0f) {
		turboalpha = 1.0f;
	}
	if (turboalpha < 0.0f) {
		turboalpha = 0.0f;
	}

	drawSpeedo(settings.Unit, true, VEHICLE::GET_IS_VEHICLE_ENGINE_RUNNING(vehicle));
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

	if (!DECORATOR::DECOR_IS_REGISTERED_AS_TYPE("mt_shift_indicator", DECOR_TYPE_INT)) {
		DECORATOR::DECOR_REGISTER("mt_shift_indicator", DECOR_TYPE_INT);
		logger.Write("DECOR: Registered \"mt_shift_indicator\" as DECOR_TYPE_INT");
	}
	if (!DECORATOR::DECOR_IS_REGISTERED_AS_TYPE("mt_gear", DECOR_TYPE_INT)) {
		DECORATOR::DECOR_REGISTER("mt_gear", DECOR_TYPE_INT);
		logger.Write("DECOR: Registered \"mt_gear\" as DECOR_TYPE_INT");
	}
	if (!DECORATOR::DECOR_IS_REGISTERED_AS_TYPE("mt_neutral", DECOR_TYPE_INT)) {
		DECORATOR::DECOR_REGISTER("mt_neutral", DECOR_TYPE_INT);
		logger.Write("DECOR: Registered \"mt_neutral\" as DECOR_TYPE_INT");
	}

	*g_bIsDecorRegisterLockedPtr = 1;
	return true;
}

int createTextureDefault(std::string resource, SpriteInfo *info) {
	if (FileExists(resource)) {
		//GetPNGDimensions(resource, &info->Width, &info->Height);
		std::vector<unsigned char> image;
		unsigned error = lodepng::decode(image, info->Width, info->Height, resource);
		return createTexture(resource.c_str());
	}
	logger.Write("ERROR: " + resource + " does not exist.");
	return -1;
}

void createTextures(std::string skin) {
	std::string skinPath = Paths::GetModuleFolder(Paths::GetOurModuleHandle()) + modDir + skin;

	spriteRPMBg.Id = createTextureDefault(skinPath + "\\bgRPM.png", &spriteRPMBg);
	spriteRPMNum.Id = createTextureDefault(skinPath + "\\numRPM.png", &spriteRPMNum);
	spriteRPMDial.Id = createTextureDefault(skinPath + "\\dialRPM.png", &spriteRPMDial);

	spriteTurboBg.Id = createTextureDefault(skinPath + "\\bgTurbo.png", &spriteTurboBg);
	spriteTurboNum.Id = createTextureDefault(skinPath + "\\numTurbo.png", &spriteTurboNum);
	spriteTurboDial.Id = createTextureDefault(skinPath + "\\dialTurbo.png", &spriteTurboDial);

	spriteN0.Id = createTextureDefault(skinPath + "\\N0.png", &spriteN0);
	spriteN1.Id = createTextureDefault(skinPath + "\\N1.png", &spriteN1);
	spriteN2.Id = createTextureDefault(skinPath + "\\N2.png", &spriteN2);
	spriteN3.Id = createTextureDefault(skinPath + "\\N3.png", &spriteN3);
	spriteN4.Id = createTextureDefault(skinPath + "\\N4.png", &spriteN4);
	spriteN5.Id = createTextureDefault(skinPath + "\\N5.png", &spriteN5);
	spriteN6.Id = createTextureDefault(skinPath + "\\N6.png", &spriteN6);
	spriteN7.Id = createTextureDefault(skinPath + "\\N7.png", &spriteN7);
	spriteN8.Id = createTextureDefault(skinPath + "\\N8.png", &spriteN8);
	spriteN9.Id = createTextureDefault(skinPath + "\\N9.png", &spriteN9);
	spriteNN.Id = createTextureDefault(skinPath + "\\NN.png", &spriteNN);
	spriteNR.Id = createTextureDefault(skinPath + "\\NR.png", &spriteNR);
	spriteNE.Id = createTextureDefault(skinPath + "\\NE.png", &spriteNE);

	spriteKMH.Id = createTextureDefault(skinPath + "\\kmh.png", &spriteKMH);
	spriteMPH.Id = createTextureDefault(skinPath + "\\mph.png", &spriteMPH);
}

void main() {
	logger.Write("Script started");
	mem::init();
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
	
	settings.Read();
	menu.ReadSettings();

	skinDir = "\\default";
	createTextures(skinDir);

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
