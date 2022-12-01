//
// 3D Game Programming
// NYCU
// Instructor: Sai-Keung Wong
//
// Date: 30 Oct. 2022.
//

#ifndef __MONSTER_MGR__
#define __MONSTER_MGR__
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>

#include "game_obj.h"
#include "monsters.h"

class MONSTER_MANAGER : public GAME_OBJ {
protected:
	int mNumMonsters;
	int mCurMonstersNum;
	bool mLifeStateArr[512];
	MONSTER* mMonstersArr[512];
	GAME_OBJ* mMonstersTarget;
	//
	int mCounter_Traversal;
protected:
	void resolveMonsterTargetCollision();
	void resolveMonsterCollision();
public:
	MONSTER_MANAGER(SceneManager* a_SceneMgr
		, const Vector3 &character_start_pos);
	virtual bool update(const Ogre::FrameEvent& evt);
	virtual void setTargetForMonsters(GAME_OBJ* a_Target);
	virtual void setMaxMonstersNum(int a_Num);

	void setParticleSystem(
		const Vector3& pos,
		int numParticles,
		SceneNode** particleNodes
	);
	//
	void init_Traversal( );
	MONSTER* getObj_Traversal( );
};

#endif