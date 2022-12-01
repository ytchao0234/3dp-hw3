//
// 3D Game Programming
// NYCU
// Instructor: Sai-Keung Wong
//
// Date: 30 Oct. 2022.
//

#include "weapon_manager.h"
#include "monster_manager.h"
#include "WeaponParticleSystemManager.h"

class ATTACK_DEFENSE_SYSTEM {
protected:
	MONSTER_MANAGER* mMonsterMgr;
	WEAPON_MANAGER* mWeaponMgr;
public:
	ATTACK_DEFENSE_SYSTEM(
		MONSTER_MANAGER *monsterMgr
		, WEAPON_MANAGER *weaponMgr);

	int update(WeaponParticleSystemManager* hitMonsterSPMgr, double dt);
protected:
	bool performAttack(
		WEAPON* w
		, MONSTER* m
		, double dt);
};