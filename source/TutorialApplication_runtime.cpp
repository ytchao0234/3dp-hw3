//
// 3D Game Programming
// National Yang Ming Chiao Tung University (NYCU), Taiwan
// Instructor: Sai-Keung Wong
// Date: 2022/10/05
//
//
// Purpose: Update the game state,
// including object states, game progress, physics simulation,
// collision detection, collision response, and etc.
//
//
// The functions will be invoked at the runtime stage.
//

#include "TutorialApplication.h"
#include "BasicTools.h"
#include "reader_data.h"
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <math.h>
#include "sound_manager.h"
#include "SystemParameter.h"
//
// using namespace Ogre;
// Enable to use the functions/structures defined in the namespace Ogre.
//
using namespace Ogre;

//
// dt: simulation time stp size
//
// zoom-in or zoom-out the minimap
//
bool BasicTutorial_00::update_MiniMapCamera(double dt)
{

	switch (mMiniMap_KeyPressedZoomMode) {
	case 1:
		mMiniMap_CameraDistance -= dt * mMiniMap_CameraDistanceAdjustSpeed;
		break;

	case -1:
		mMiniMap_CameraDistance += dt * mMiniMap_CameraDistanceAdjustSpeed;

		break;
	default:
		mMiniMap_CameraDistance += dt * mMiniMap_CameraDistanceAdjustSpeed;
		break;
	}

	// Add your own stuff
	if (abs(mMiniMap_CameraDistanceAdjustSpeed) > abs(dt * mMiniMap_CameraDistanceSlowDownSpeed))
	{
		mMiniMap_CameraDistanceAdjustSpeed -= dt * mMiniMap_CameraDistanceSlowDownSpeed;
	}
	else
	{
		mMiniMap_CameraDistanceAdjustSpeed = 0;
		mMiniMap_CameraDistanceSlowDownSpeed = 0;
	}

	Vector3 cpos = mMainChar->getPosition();
	mCameraArr[1]->setPosition(cpos + Vector3(0, 1000 + mMiniMap_CameraDistance, 0));

	return true;
}

bool BasicTutorial_00::update_LargeSphere(double dt)
{
	Vector3 pos;
	mMapMesh->getStartingPosition(pos);

	Vector3 offset = Vector3(0, 250, 0);
	static Real b = 0;
	b += 0.8 * dt;
	Real y = 9000 * sin(b);
	pos.y += offset.y + y;
	//setPosition(pos);
	return true;
}

bool  BasicTutorial_00::update_Light(double dt) {
	Vector3 pos = mMainChar->getPosition();
	mLight0->setPosition(Vector3(0, 100, 0) + pos);
	return true;
}

bool BasicTutorial_00::update_Character(double dt)
{
	Vector3 pos = mSceneNode_Sphere->getPosition();
	mMainChar->getWeaponManager()->setTarget(pos, mSphereRadius);
	basicTool_setOffParticleSystem(
		mParticleMainNode,
		"explosion",
		pos + Vector3(0.0, 200.0, 0.0)
	);
	mMainChar->update(dt);

	update_CharacterWalkSpeed(dt);

	return true;
}

bool BasicTutorial_00::adjust_MainCharacterPosition_InteractionWithLargeSphere(double dt)
{
	Vector3 p = mMainChar->getPosition();
	Vector3 q = mSceneNode_Sphere->getPosition();
	double rp = 100;
	double rq = mSphereRadius;

	double distance = p.distance(q);
	double rr = rp + rq;
	if (distance > rr) return true;

	Vector3 pq = p - q;
	double len = pq.length();
	pq.y = 0.0;
	Vector3 npq;
	if (len == 0.0) {
		npq = Vector3(1.0, 0.0, 0.0);
	} else npq = pq.normalisedCopy();
	double dlen = rr - len;

	//
	// adjust the main character position
	//

	return true;
}

//
// Get the character level and show the level.
//
bool BasicTutorial_00::update_CharacterLevel_UI(double dt)
{
	//
	// add your own stuff
	//
	return true;
}

bool BasicTutorial_00::update_CharacterExperience_UI(double dt)
{
	//expPoints = (float) mMainChar->getExperience();
	//maxExpPoints = (float)mMainChar->getMaxExperience();

	//basicTool_logMessage("expPoints:", expPoints);
	//basicTool_logMessage("maxExpPoints:", maxExpPoints);


	//mBar2D_Experience->setSplit2Parts(true);
	//mBar2D_Experience->setInfo(expPoints, maxExpPoints);
	//mBar2D_Experience->update(0, 0);
	return true;
}

bool BasicTutorial_00::update_CharacterInternalState_UI(double dt)
{
	//
	// reduce/increase stamina
	// update stamina bar, mBar2D_Stamina
	// if condition is satisified, play a voice about stamina
	//
	// compute walk speed factor
	// update speed bar, mBar2D_2_Speed
	//

	return true;
}

bool BasicTutorial_00::update_CharacterWalkSpeed(double dt)
{
	double speed_factor = mBar2D_2_Speed->getCurrentValue();
	mMainChar->setSpeedFactor(speed_factor);
	return true;

}

//
// new_score is the earned score in this frame.
//
bool BasicTutorial_00::update_Score_UI(
	int new_score
	, double dt)
{

	float k = 0.01;
	if (mScoreBoard_Direction) {

		mScoreCoord_X += dt * k;
		if (mScoreCoord_X > mScoreCoord_MaxX) {
			mScoreCoord_X = mScoreCoord_MaxX;
			mScoreBoard_Direction = !mScoreBoard_Direction;
		}
	}
	else {
		// Add your own stuff
	}

	mfScore += new_score;				// accumulate the score
	if (mfScore >= 1000) mfScore = 0;
	mScore = mfScore;
	//mDigitDialogue->setScore(mScore, mScoreCoord_X, 0.05);
	mDigitDialogue->setScore(mScore, 0.1, 0.05);
	return true;
}

bool BasicTutorial_00::update_ParticleSystems(double dt)
{
	if (!mTurnOnParticleSystems) return true;
	mMonsterMgr->setParticleSystem(
		mMainChar->getPosition(),
		mNumParticleNodes,
		mParticleNode
	);
	return true;
}

bool BasicTutorial_00::checkGoOnGameStatus(double dt)
{
	bool flg_stop = false;
	double& stopGameMaxTime =
		SystemParameter::getInstance()->stopGameMaxTime;

	mToggle_CumulativeTime += dt;
	if (mToggle_CumulativeTime >
		stopGameMaxTime)
		mToggle_CumulativeTime = stopGameMaxTime + 0.1;

	if (mKeyPressed_StopKey) {
		if (mToggle_CumulativeTime >= stopGameMaxTime) {
			mFlgGoOnGame = !mFlgGoOnGame;
			mToggle_CumulativeTime = 0.0;
		}
	}
	else {
		mToggle_CumulativeTime = 0.0;
	}

	return mFlgGoOnGame;
}

//
// Check whether the player wins.
// If yes, play a voice to tell the game is over.
// Also, darken the environment, i.e., ser low intensity to light.
//
void BasicTutorial_00::checkVictory(double dt)
{
	if (mFlg_Victory) return;
	//
	// Add your own stuff
	//
}

bool BasicTutorial_00::frameStarted(const Ogre::FrameEvent& evt)
{
	bool flg = Ogre::FrameListener::frameStarted(evt);
	// dt: simulation time step size
	double dt = evt.timeSinceLastFrame;

	//make sure that dt must not be larger than maxSimulationTimeStepSize.
	if (dt > mMax_dt)
		dt = mMax_dt;

	if (!checkGoOnGameStatus(dt)) return flg;

	update_LargeSphere(dt);
	update_Light(dt);
	mMonsterMgr->update(evt);
	update_MiniMapCamera(dt);
	update_ParticleSystems(dt);

	update_CharacterInternalState_UI(dt);

	update_CharacterExperience_UI(dt);

	double numHits = mAttackDefenseSystem->update(mHitMonsterPSMgr, dt);

	//basicTool_logMessage("numHits:", numHits);


	update_Score_UI(numHits, dt);


	mMainChar->addExperience( numHits );
	update_Character(dt);
	update_CharacterLevel_UI(dt);
	adjust_MainCharacterPosition_InteractionWithLargeSphere(dt);

	checkVictory(dt);

	return flg;
}