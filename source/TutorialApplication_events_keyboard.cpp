//
// 3D Game Programming
// National Yang Ming Chiao Tung University (NYCU), Taiwan
// Instructor: Sai-Keung Wong
// Date: 2022/10/05
//
//
// The functions will be invoked at the runtime stage.
//
// Example:
// Handle key events to control the camera.
// Handle key events to set viewports.
// Handle key events to obtain the camera information.
// Handle key events to activate the objects/items, e.g., spheres, robots, etc
// And others
//
// A key handler handles simple tasks,
// such as setting the states of game objects.
//
//

#include "TutorialApplication.h"
#include "BasicTools.h"
#include "map_manager.h"
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <math.h>

//
// using namespace Ogre;
// Enable to use the functions/structures defined in the namespace Ogre.
//
using namespace Ogre;

bool BasicTutorial_00::keyPressed_CharacterPosition(
	const OIS::KeyEvent& arg
)
{
	bool flg_handled = false;
	if (arg.key == OIS::KC_F1) {
		flg_handled = true;
		mMainChar->setPosition(Vector3(860, 51, 751));
	}
	if (arg.key == OIS::KC_F2) {
		flg_handled = true;
		mMainChar->setPosition(Vector3(4612, 41, 4529));
	}
	return flg_handled;

}

bool BasicTutorial_00::keyPressed_UpdateCharacterState(
	const OIS::KeyEvent& arg
)
{
	bool flg_handled = false;
	if (arg.key == OIS::KC_W) {
		flg_handled = true;
		mMainChar->setWalkForward();
	}
	if (arg.key == OIS::KC_S) {
		flg_handled = true;
		mMainChar->setWalkBackward();
	}

	if (arg.key == OIS::KC_SPACE)
	{
		flg_handled = true;
		mMainChar->setFireAction_Normal();
	}

	return flg_handled;
}

bool BasicTutorial_00::keyPressed_UpdateCameraState(
	const OIS::KeyEvent& arg
)
{
	bool flg_handled = false;
	if (arg.key == OIS::KC_Z) {
		flg_handled = true;
		mMiniMap_KeyPressedZoomMode = 1;
		mMiniMap_CameraDistanceAdjustSpeed = 300;
		mMiniMap_CameraDistanceSlowDownSpeed = 0;
	}
	if (arg.key == OIS::KC_X) {
		flg_handled = true;
		mMiniMap_KeyPressedZoomMode = -1;
		mMiniMap_CameraDistanceAdjustSpeed = 300;
		mMiniMap_CameraDistanceSlowDownSpeed = 0;

	}
	return flg_handled;

}
bool BasicTutorial_00::keyPressed_UpdateSystemState(
	const OIS::KeyEvent& arg
)
{
	bool flg_handled = false;
	if (arg.key == OIS::KC_P) {
		flg_handled = true;
		mTurnOnParticleSystems = !mTurnOnParticleSystems;

		for (int i = 0; i < mNumParticleNodes; ++i) {
			basicTool_setVisibleParticleSystem(
				mParticleNode[i],
				"explosion",
				mTurnOnParticleSystems);
		}
	}
	return flg_handled;

}
bool BasicTutorial_00::keyPressed(const OIS::KeyEvent& arg)
{
	//bool flg = BaseApplication::keyPressed(arg);
	bool flg = true;

	flg |= keyPressed_CharacterPosition(arg);
	flg |= keyPressed_UpdateCharacterState(arg);
	flg |= keyPressed_UpdateCameraState(arg);
	flg |= keyPressed_UpdateSystemState(arg);

	if (arg.key == OIS::KC_0) {
		mKeyPressed_StopKey = true;
	}


	return flg;
}

bool BasicTutorial_00::keyReleased(const OIS::KeyEvent& arg)
{
	bool flg = true;
	if (arg.key == OIS::KC_Z) {
		mMiniMap_KeyPressedZoomMode = 0;
		mMiniMap_CameraDistanceAdjustSpeed = -mMiniMap_CameraDistanceAdjustSpeed;
		mMiniMap_CameraDistanceSlowDownSpeed = -200;
	}
	if (arg.key == OIS::KC_X) {
		mMiniMap_KeyPressedZoomMode = 0;
		mMiniMap_CameraDistanceAdjustSpeed = mMiniMap_CameraDistanceAdjustSpeed;
		mMiniMap_CameraDistanceSlowDownSpeed = 200;
	}

	if (arg.key == OIS::KC_W) {
		mMainChar->unsetWalkForward();
	}
	if (arg.key == OIS::KC_S) {
		mMainChar->unsetWalkBackward();
	}

	if (arg.key == OIS::KC_ESCAPE)
	{
		mShutDown = true;
	}
	if (arg.key == OIS::KC_0) {
		mKeyPressed_StopKey = false;
	}

	return flg;
}