#pragma once
#include "Macros.h"
#include "AttackableUnit.h"

namespace Scholzf
{
	class
		 AIHeroClient : public AttackableUnit
	{
	public:
		MAKE_GET(ChampionName, std::string*, Offsets::Obj_AIHero::ChampionName);
	};
}