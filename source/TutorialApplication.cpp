//
// 3D Game Programming
// National Yang Ming Chiao Tung University (NYCU), Taiwan
// Instructor: Sai-Keung Wong
// Date: 2022/10/05
//
#include "TutorialApplication.h"
#include "BasicTools.h"
#include "reader_data.h"
#include "map_manager.h"
#include "envTools.h"
#include "sound_manager.h"
#include "SystemParameter.h"

using namespace Ogre;
SOUND* mSound;

BasicTutorial_00::BasicTutorial_00(void) {
	mMax_dt = SystemParameter::getInstance()->maxSimulationTimeStepSize;
	//
	mFlgGoOnGame = true;
	mToggle_CumulativeTime = 2.5;
	mKeyPressed_StopKey = false;
	//
	mMainChar = 0;
	mMiniMap_CameraDistance = 0;
	mMiniMap_KeyPressedZoomMode = 0;
	mMiniMap_CameraDistanceAdjustSpeed = 0;
	mMiniMap_CameraDistanceSlowDownSpeed = 0;
	mSound = new SOUND;
	mSound->init();
	//
	//mScoreCoord_MaxX = 0.5;
	mScoreCoord_MaxX = 0.10;
	mScoreCoord_MinX = 0.05;
	mScoreCoord_X = mScoreCoord_MinX;

	mScoreBoard_Direction = true;
	mfScore = 0.0;

	mStamina_Min = 0.0;
	mStamina_Max = 100.0;
	mStamina = mStamina_Max;

	mTurnOnParticleSystems = true;
	//
	mAttackDefenseSystem = nullptr;
	//
	mLevel = 1;

	//
	mFlg_Victory = false;
}




void BasicTutorial_00::chooseSceneManager()
{
	//ST_EXTERIOR_FAR
	//mSceneMgrArr[0] = mRoot
	//	->createSceneManager(ST_EXTERIOR_CLOSE, "primary");
	mSceneMgrArr[0] = mRoot
		->createSceneManager(
			ST_EXTERIOR_CLOSE, "primary");
	mSceneMgrArr[1] = mSceneMgrArr[0];
	/*
	mSceneMgrArr[1] = mRoot
	->createSceneManager(ST_EXTERIOR_CLOSE, "secondary");
*/
}

void BasicTutorial_00::createCamera_00(void)
{
	mSceneMgr = mSceneMgrArr[0];
	mCamera = mCameraArr[0] = mSceneMgr->createCamera("PlayerCam");
	mCamera->setPosition(Ogre::Vector3(770, 800, 2100));
	mCamera->lookAt(Ogre::Vector3(750, 50, 750));
	mCamera->setNearClipDistance(5);
	mCameraManArr[0] = new OgreBites::SdkCameraMan(mCamera);   // create a default camera controller
}

void BasicTutorial_00::createCamera_01(void)
{
	mSceneMgr = mSceneMgrArr[1];
	mCamera = mCameraArr[1] = mSceneMgr->createCamera("PlayerCam2");
	mCamera->setPosition(Ogre::Vector3(750, 1000, 750));
	mCamera->lookAt(Ogre::Vector3(750, 0, 751));
	mCamera->setNearClipDistance(5);
	mCameraManArr[1] = new OgreBites::SdkCameraMan(mCamera);   // create a default camera controller

}



void BasicTutorial_00::createViewport_Main(void)
{
	mCamera = mCameraArr[0];
	Ogre::Viewport* vp = mWindow->addViewport(
		mCamera
		, 0          // z-order
		, 0.0f
		, 0.0f
		, 1.0f
		, 1.0f
	);
	vp->setBackgroundColour(Ogre::ColourValue(0, 0, 1));
	mCamera->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
	vp->setVisibilityMask(0x01);
}

void BasicTutorial_00::createViewport_MiniMap(void)
{
	mCamera = mCameraArr[1];

	Ogre::Viewport* vp = mWindow->addViewport(
		mCamera,
		1,
		0.75,
		0.0,
		0.25,
		0.5
	);
	vp->setBackgroundColour(Ogre::ColourValue(0, 1, 0));
	mCamera->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
	vp->setOverlaysEnabled(false);
	vp->setVisibilityMask(0x10);
}






void BasicTutorial_00::createViewports(void)
{
	createViewport_Main();
	createViewport_MiniMap();
	mCamera = mCameraArr[0];
}

void BasicTutorial_00::createCamera(void) {
	createCamera_00();
	createCamera_01();
	mCameraMan = mCameraManArr[0];
	//mCameraMan = mCameraManArr[1];
	mCamera = mCameraArr[0];
}





int main(int argc, char* argv[]) {
	BasicTutorial_00 app;
	app.go();
	return 0;
}
