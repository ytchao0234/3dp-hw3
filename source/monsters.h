//
// 3D Game Programming
// NYCU
// Instructor: Sai-Keung Wong
//
// Date: 30 Oct. 2022.
//

#ifndef __MONSTERS_H__
#define __MONSTERS_H__
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>

#include "game_obj.h"
#include "game_obj.h"
class MONSTER : public GAME_OBJ {
protected:
	void updateViewDirection();
public:
	MONSTER(SceneManager *a_SceneMgr);
	virtual bool update(const Ogre::FrameEvent& evt);
};

#endif