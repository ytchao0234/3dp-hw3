//
// 3D Game Programming
// National Yang Ming Chiao Tung University (NYCU), Taiwan
// Instructor: Sai-Keung Wong
// Date: 2022/10/05
//

#ifndef __WEAPON_MGR__
#define __WEAPON_MGR__
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>

#include "game_obj.h"
#include "weapons.h"
#include "WeaponParticleSystemManager.h"

class WEAPON_MANAGER : public GAME_OBJ {
protected:

	Real mCoolDownTimeForFiring;
	Real mMaxCoolDownTime;
	bool mUsedWeaponsArr[128];
	WEAPON* mBulletsArr[128];
	int mMaxNum;
	int mCurBulletsNum;

	Vector3 mTargetPos;
	Real mTargetRadius;
	bool mFlgTarget;
	//
	WeaponParticleSystemManager* mWeaponParticleSystemManager;
	//
	int mCounter_Traversal;
public:
	WEAPON_MANAGER(SceneManager* a_SceneMgr);
	void installWeaponWSManager(WeaponParticleSystemManager* wpsMgr);
	void setTarget(const Vector3& pos, Real radius);
	virtual void setMaxBulletsNum(int a_Num);

	virtual void fire_Normal(const Vector3& pos, const Vector3& direction);
	virtual bool update(double dt);
	//
	void init_Traversal();
	WEAPON* getObj_Traversal();
};

#endif