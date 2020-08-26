#pragma once
#include <Main.h>
#include <Singleton.h>

#define PARSE_FLAG_BOOL(name, offset) [[nodiscard]] inline bool name() const { return (uiState() & (1 << offset)) != 0; }

namespace GW2Radial
{

struct LinkedMem;
struct MumbleContext;

class MumbleLink : public Singleton<MumbleLink> {
public:
	enum class Profession : uint8_t {
		NONE = 0,
	    GUARDIAN = 1,
		WARRIOR = 2,
		ENGINEER = 3,
		RANGER = 4,
		THIEF = 5,
		ELEMENTALIST = 6,
		MESMER = 7,
		NECROMANCER = 8,
		REVENANT = 9
	};

	enum class Race : uint8_t {
	    ASURA = 0,
		CHARR = 1,
		HUMAN = 2,
		NORN = 3,
		SYLVARI = 4
	};

	MumbleLink();
	~MumbleLink();

	void OnUpdate();

	[[nodiscard]] bool isInWvW() const;

	// uiState flags
	PARSE_FLAG_BOOL(isMapOpen, 0);
	PARSE_FLAG_BOOL(isCompassTopRight, 1);
	PARSE_FLAG_BOOL(doesCompassHaveRotationEnabled, 2);
	PARSE_FLAG_BOOL(gameHasFocus, 3);
	PARSE_FLAG_BOOL(isInCompetitiveMode, 4);
	PARSE_FLAG_BOOL(textboxHasFocus, 5);
	PARSE_FLAG_BOOL(isInCombat, 6);

	[[nodiscard]] fVector3 position() const;

	[[nodiscard]] MountType currentMount() const;
	[[nodiscard]] bool isMounted() const;
	[[nodiscard]] bool isInMap() const;
	[[nodiscard]] uint32_t mapId() const;
	[[nodiscard]] const wchar_t* characterName() const;
	[[nodiscard]] bool isSwimmingOnSurface() const;
	[[nodiscard]] bool isUnderwater() const;
	
	[[nodiscard]] Profession characterProfession() const {
	    return identity_.profession;
    }
	
	[[nodiscard]] uint8_t characterSpecialization() const {
	    return identity_.specialization;
    }

    [[nodiscard]] Race characterRace() const {
	    return identity_.race;
    }

	[[nodiscard]] bool isCommander() const {
		return identity_.commander;
	}

	[[nodiscard]] float fov() const {
		return identity_.fov;
	}

	[[nodiscard]] uint8_t uiScale() const {
		return identity_.uiScale;
	}

protected:
	[[nodiscard]] uint32_t uiState() const;

	struct Identity
	{
	    Profession profession = Profession::NONE;
		uint8_t specialization = 0;
		Race race = Race::ASURA;
		bool commander = false;
		float fov = 0.f;
		uint8_t uiScale = 0;
	};

	[[nodiscard]] const MumbleContext* context() const;
	HANDLE fileMapping_ = nullptr;
	LinkedMem* linkedMemory_ = nullptr;

	Identity identity_;
};

}