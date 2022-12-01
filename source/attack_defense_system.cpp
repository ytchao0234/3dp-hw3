
//
// 3D Game Programming
// National Yang Ming Chiao Tung University (NYCU), Taiwan
// Instructor: Sai-Keung Wong
// Date: 2022/10/05
//

#include "attack_defense_system.h"
#include "weapon_manager.h"
#include "monster_manager.h"
#include "map_manager.h"
#include "reader_data.h"
#include "BasicTools.h"
#include "sound_manager.h"


ATTACK_DEFENSE_SYSTEM::ATTACK_DEFENSE_SYSTEM(
	MONSTER_MANAGER* monsterMgr
	, WEAPON_MANAGER* weaponMgr)
{

	mMonsterMgr = monsterMgr;
	mWeaponMgr = weaponMgr;
}

//
// w: weapon
// m: monster
//
bool ATTACK_DEFENSE_SYSTEM::performAttack(
	WEAPON* w
	, MONSTER* m
	, double dt)
{
	// check if w hits m.
	// if yes, play an explosion sound 
	// and set the life of the monster to zero.
	// 
	bool flgHit = false;
	//
	//
	//
	return flgHit;
}

//
// For each monster
// check if the monster is hit by a bullet.
//
// If a bullet w hits a monster, set the life of the bullet w to zero
// Also, use hitMonsterSPMgr to play a particle system at the monster position.
//
int ATTACK_DEFENSE_SYSTEM::update(
	WeaponParticleSystemManager* hitMonsterSPMgr
	, double dt
)
{
	int numHits = 0;

	mMonsterMgr->init_Traversal( );
	mWeaponMgr->init_Traversal( );
	bool flgHit;
	while (true) {
		MONSTER* m = mMonsterMgr->getObj_Traversal();
		if (m == nullptr) break;
		if (!m->isAlive()) continue;
		while (true) {
			WEAPON* w = mWeaponMgr->getObj_Traversal();
			if (w == nullptr) {
				break;
			}
			flgHit = false;
			flgHit = performAttack(w, m, dt);
			if (flgHit) {
				++numHits;
				w->setLife(0);
				//p = m->getPosition( )
				//Use hitMonsterSPMgr to invoke play(p)
				break;
			}
			else {
				
			}
		}
		mWeaponMgr->init_Traversal();
	}
	return numHits;
}
