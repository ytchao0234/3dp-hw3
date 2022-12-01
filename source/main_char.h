//
// 3D Game Programming
// NYCU
// Instructor: Sai-Keung Wong
//
// Date: 30 Oct. 2022.
//

#ifndef __MAIN_CHAR_H__
#define __MAIN_CHAR_H__
#include <vector>
#include "game_obj.h"
#include "weapon_manager.h"
#include "WeaponParticleSystemManager.h"

class MAIN_CHAR : public GAME_OBJ
{
protected:
	Camera* mCamera;
	Vector3 mEyePosition;
	WEAPON_MANAGER* mWeaponMgr;
	unsigned int mFireActionMode;
	int mCurBulletsNum;
	virtual void fireWeapon();

	double mDistanceOffsetToTerrain;
	double mSpeedFactor_Modifer;

	double mExperiencePoints;
	double mMaxExperiencePoints;
protected:
	void init();
	void updateCameraToFollowMainCharacter();
public:
	MAIN_CHAR();
	MAIN_CHAR(SceneManager* a_SceneMgr);
	virtual void attachCamera(Camera* a_Camera);
	virtual void walkForward(double dt);
	virtual void walkBackward(double dt);
	virtual void setWalkForward();
	virtual void setWalkBackward();
	void unsetWalkForward();
	virtual void unsetWalkBackward();
	unsigned int getActionMode() const;
	virtual bool update(double dt);
	virtual void updateWeapon(double dt);
	virtual void setFireAction_Normal();
	virtual Vector3 getWeaponPosition() const;
	virtual void updateViewDirection();
	virtual void setMaxBulletsNum(int a_Num);

	virtual void setPosition_to_Environment(const Vector3& p);
	virtual void setEyePosition_Y(double y);
	virtual void setWalkingMaxSpeed_Modifier(double walkingMaxSpeed);
	WEAPON_MANAGER* getWeaponManager();

	void installWeaponWSManager(WeaponParticleSystemManager* wpsMgr);
	//
	virtual void addExperience(double exp);
	virtual double getExperience( ) const;
	virtual double getMaxExperience( ) const;
};

#endif