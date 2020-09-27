#pragma once
#include "stdafx.h"
#include "injector/injector.hpp"
#include "injector/assembly.hpp"

enum gameVersion
{
	VERSION_PLATINUM,
	VERSION_COMPLETE,
	VERSION_UNKNOWN
};
extern gameVersion version;

namespace Game {

	uintptr_t GetGameplayStateRelatedInfos()
	{
		if (version == gameVersion::VERSION_PLATINUM) {
			return ((uintptr_t(__cdecl *)())(0x00440FD0))();
		}
		else {
			return ((uintptr_t(__cdecl *)())(0x0055E450))();
		}
	}	

	// Real name from C02680
	uint32_t GetGameShellInstance()
	{
		if (version == gameVersion::VERSION_PLATINUM) {
			return *(uint32_t*)(0x13D2EBC);
		}
		else {
			return *(uint32_t*)(0x159D774);
		}
	}

	uint32_t GetShowFPS()
	{
		if (version == gameVersion::VERSION_PLATINUM) {
			return 0x1103C64;
		}
		else {
			return 0x12CD1BC;
		}
	}

	uint32_t GetShowPeopleEtcInfos()
	{
		if (version == gameVersion::VERSION_PLATINUM) {
			return 0x1103C60;
		}
		else {
			return 0x12CD1B9;
		}
	}

	uint32_t GetShowDataPoolsInfos()
	{
		if (version == gameVersion::VERSION_PLATINUM) {
			return 0x1103C61;
		}
		else {
			return 0x12CD1BA;
		}
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

}