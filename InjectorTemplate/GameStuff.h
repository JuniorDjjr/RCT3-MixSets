#pragma once
#include "stdafx.h"
#include "injector/injector.hpp"
#include "injector/assembly.hpp"

namespace Game {

	uintptr_t GetGameplayStateRelatedInfos()
	{
		return ((uintptr_t(__cdecl *)())(0x00440FD0))();
	}

	// Real names from 440010
	enum eGameState {
		StateBannerSequence = 0,
		StateFrontScreen = 1,
		StateAttractSequence = 2,
		StateCareerMapScreen = 3,
		StateTutorial = 4,
		StateScenarioStartAttractSequence = 5,
		StateInGame = 6,
		StateScenarioEditor = 7,
		StateConvertSavedGameToScenario = 8,
		StateRCDesigner = 9,
		StateTrackDesignManager = 0xB,
		StateFireworkDesignManager = 0xC,
		StatePeopleDesignManager = 0xD,
		StateDemoEndBannerSequence = 0xE,
		StateExit = 0xF,
		StateCacheWarming = 0x13,
		StateNumStates = 0x14
	};

	// Real name from C02680
	auto &game_pGameShellInstance = *(uint32_t*)(0x13D2EBC);

	auto &bShowFPS = *(uint32_t *)0x1103C64;
	auto &bShowPeopleEtcInfos = *(bool *)0x1103C60;
	auto &bShowDataPoolsInfos = *(bool *)0x1103C61;

}