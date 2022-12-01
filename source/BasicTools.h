//
// 3D Game Programming
// NYCU
// Instructor: Sai-Keung Wong
//
// Date: 30 Oct. 2022.
//

#ifndef __BASIC_TOOLS_H__
#define __BASIC_TOOLS_H__
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include <SdkTrays.h>
#include <SdkCameraMan.h>

extern void basicTool_Init(
    OgreBites::SdkTrayManager* a_TrayMgr
    , Ogre::SceneManager* a_SceneMgr
    , Ogre::Camera* a_Camera);

extern void basicTool_genNameUsingIndex(
    const Ogre::String & prefix
    , int index
    , Ogre::String &out_name);

extern void basicTool_logMessage(
    const  Ogre::String &msg
);

extern void basicTool_logMessage(
    const Ogre::String& itemMsg
    , double v);

extern void basicTool_logMessage(
    const Ogre::Vector3 &v
);

extern void basicTool_logMessage(
    double v
);

extern bool basicTool_projectScenePointOntoTerrain_PosDirection(
    Ogre::Vector3 &p
);

extern bool basicTool_projectScenePointOntoTerrain_NegDirection(
    Ogre::Vector3 &p
);

extern Ogre::SceneNode* basicTool_initParticleSystemForExplosion(
    Ogre::SceneManager *sceneMgr
    , const char *particleName
    , const char* particleScriptName = "Examples/GreenyNimbus"
    );

extern void basicTool_setOffParticleSystem(
	Ogre::SceneNode *fNode
    , const Ogre::String & particleName
    , const Ogre::Vector3 &pos); 

extern void basicTool_setVisibleParticleSystem(
	Ogre::SceneNode *particleNode
    , const Ogre::String & particleName
    , bool flg_show); 

#endif