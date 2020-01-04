/*
The base of this code is from InjectorTemplate by Junior_Djjr - MixMods.com.br
*/
#include "stdafx.h"
#include "IniReader/IniReader.h"
#include "ReadIniCustom.h"
#include "injector/injector.hpp"
#include "injector/assembly.hpp"
#include "GameStuff.h"
#include "PatchStuff.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace injector;
using namespace std;

string const projectName = TARGET_NAME;
int const BUILD_NUMBER = 2;

enum gameVersion
{
	VERSION_UNKNOWN,
	VERSION_A
};
gameVersion version;

gameVersion GetGameVersion()
{
	switch (injector::ReadMemory<uint32_t>(0xF3F37C, true))
	{
	case 0x005C3C10:
		//MessageBoxA(0, "VERSION_A", "Game version", 0);
		return VERSION_A;
	default:
		//MessageBoxA(0, "VERSION_UNKNOWN", "Game version", 0);
		return VERSION_UNKNOWN;
	}
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		version = GetGameVersion();
		if (version != VERSION_UNKNOWN) Init();
		else MessageBoxA(0, "Incompatible game version. For now, only for RCT3plus.exe (Platinum). Contact me if you think this is wrong.", "Error", 0);
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

fstream lg;

// Global variables from ini
bool G_ShowFPS;
bool G_ShowPeopleEtcInfos;
bool G_ShowDataPoolsInfos;
bool G_UseMinimalistFPS;

///////////////////////////////////////////////////////////////////////////////////////////////////

uintptr_t gameProcessingOriginalCall;
Game::eGameState lastGameState;

void GameProcessing()
{
	float fps = *(float*)(Game::game_pGameShellInstance + 0x24);

	int gameplayStateRelatedInfos = Game::GetGameplayStateRelatedInfos();

	Game::eGameState curGameState = *(Game::eGameState*)(gameplayStateRelatedInfos + 112);
	if (curGameState == Game::eGameState::StateInGame)
	{
		if (lastGameState != curGameState)
		{
			if (G_ShowFPS && !G_UseMinimalistFPS) Game::bShowFPS = true;
			if (G_ShowPeopleEtcInfos) Game::bShowPeopleEtcInfos = true;
			if (G_ShowDataPoolsInfos) Game::bShowDataPoolsInfos = true;
			lastGameState = curGameState;
			lg << "Gameplay started." << endl;
			lg.flush();
		}
	}
	else
	{
		lastGameState = curGameState;
	}

	if (G_UseMinimalistFPS && G_ShowFPS)
	{
		Game::bShowFPS = false;
		((int(__cdecl *)(int, int, const char *, int))0x496C60)(1, 1, "%i", (int)fps);
	}

	SimpleCall(gameProcessingOriginalCall);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void ReadIni()
{
	int i;
	float f;

	CIniReader ini(projectName + ".ini");
	if (ini.data.size() <= 0) { lg << projectName << ".ini NOT FOUND\n"; lg.flush(); return; }

	if (ReadIniInt(ini, &lg, "Graphics", "ReplaceOptionsResX1440", &i)) {
		WriteMemory<uint32_t>(0x4834DC + 4, i, true);
	}

	if (ReadIniInt(ini, &lg, "Graphics", "ReplaceOptionsResY900", &i)) {
		WriteMemory<uint32_t>(0x4834E4 + 4, i, true);
	}

	if (ReadIniInt(ini, &lg, "Graphics", "ReplaceOptionsResX1280", &i)) {
		WriteMemory<uint32_t>(0x48343C + 1, i, true);
	}

	if (ReadIniInt(ini, &lg, "Graphics", "ReplaceOptionsResY800", &i)) {
		WriteMemory<uint32_t>(0x48344F + 1, i, true);
	}

	if (ReadIniFloat(ini, &lg, "Graphics", "MaxDistValue", &f)) {
		WriteMemory<float>(0x60F77C + 1, f, true);
		WriteMemory<float>(0x60F7CC + 1, f, true);
		WriteMemory<float>(0x60F818 + 1, f, true);
		WriteMemory<float>(0x60F864 + 1, f, true);
		WriteMemory<float>(0x60F8B0 + 1, f, true);
		WriteMemory<float>(0x60F8FC + 1, f, true);
		WriteMemory<float>(0x60F948 + 1, f, true);
		WriteMemory<float>(0x60F994 + 1, f, true);
		WriteMemory<float>(0x60F9E0 + 1, f, true);
		WriteMemory<float>(0x60FA2C + 1, f, true);
		WriteMemory<float>(0x10ED8A8, f, false);
		WriteMemory<float>(0x10ED8BC, f, false);
		WriteMemory<float>(0x10ED8D0, f, false);
		WriteMemory<float>(0x10ED8E4, f, false);
		WriteMemory<float>(0x10ED8F8, f, false);
		WriteMemory<float>(0x10ED90C, f, false);
		WriteMemory<float>(0x10ED920, f, false);
		WriteMemory<float>(0x10ED934, f, false);
		WriteMemory<float>(0x10ED948, f, false);
		WriteMemory<float>(0x10ED95C, f, false);
		WriteMemory<float>(0x10ED970, f, false);
		WriteMemory<float>(0x10ED984, f, false);
		WriteMemory<float>(0x10ED998, f, false);
		WriteMemory<float>(0x10ED9AC, f, false);
		WriteMemory<float>(0x10ED9C0, f, false);
		WriteMemory<float>(0x10ED9D4, f, false);
		WriteMemory<float>(0x10ED9E8, f, false);
		WriteMemory<float>(0x10ED9FC, f, false);
		WriteMemory<float>(0x10EDA10, f, false);
		WriteMemory<float>(0x10EDA24, f, false);
	}

	if (ReadIniBool(ini, &lg, "Debug", "ShowFPS")) {
		G_ShowFPS = true;
	}
	else G_ShowFPS = false;

	if (ReadIniBool(ini, &lg, "Debug", "UseMinimalistFPS")) {
		G_UseMinimalistFPS = true;
	}
	else G_UseMinimalistFPS = false;

	if (ReadIniBool(ini, &lg, "Debug", "ShowPeopleEtcInfos")) {
		G_ShowPeopleEtcInfos = true;
	}
	else G_ShowPeopleEtcInfos = false;

	if (ReadIniBool(ini, &lg, "Debug", "ShowDataPoolsInfos")) {
		G_ShowDataPoolsInfos = true;
	}
	else G_ShowDataPoolsInfos = false;
	
	lg.flush();
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void Init()
{
	lg.open(projectName + ".log", std::fstream::out | std::fstream::trunc);
	lg << "Build " << BUILD_NUMBER << endl;
	lg.flush();

	uintptr_t address;
	switch (version)
	{
	case VERSION_A:
		address = 0x43D861;
		break;
	default:
		return;
	}
	SimpleHookCallStoreOriginal(address, GameProcessing, &gameProcessingOriginalCall);

	ReadIni();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
