//
// 3D Game Programming
// NYCU
// Instructor: Sai-Keung Wong
//
// Date: 30 Oct. 2022.
//
#include "main_char.h"
#include "BasicTools.h"
#include "envTools.h"
#include "map_manager.h"
#include "sound_manager.h"
#include "SystemParameter.h"
#include <OgreInstancedGeometry.h>

MAIN_CHAR::MAIN_CHAR()
{
    init();
}

MAIN_CHAR::MAIN_CHAR(SceneManager *a_SceneMgr) : GAME_OBJ(a_SceneMgr)
{
    /*
    mDistanceOffsetToTerrain = 0;
    mCamera = 0;
    mVelocity = Vector3(1, 0, 0);
    mSpeedFactor = 100.0;
    mActionMode = ACTION_NONE;
    mEyePosition = Vector3(0,120, 0);

    mFireActionMode = FIRE_ACTION_NONE;
    mTarget = 0; //null
    mCurBulletsNum = 0;
    */
    init();
    mWeaponMgr = new WEAPON_MANAGER(mSceneMgr);


}

void MAIN_CHAR::init()
{
    mDistanceOffsetToTerrain = 0;
    mCamera = nullptr;
    mVelocity = Vector3(1, 0, 0);
    mSpeedFactor = 100.0;
    mActionMode = ACTION_NONE;
    mEyePosition = Vector3(0, 120, 0);

    mFireActionMode = FIRE_ACTION_NONE;
    mWeaponMgr = nullptr;
    mTarget = nullptr; //null
    mCurBulletsNum = 0;
    //
    mExperiencePoints = 0.0;
    mMaxExperiencePoints =
        SystemParameter::getInstance()->charMaxExperiencePoints;

    //basicTool_logMessage("mExperiencePoints:", mExperiencePoints);
    //basicTool_logMessage("mMaxExperiencePoints:", mMaxExperiencePoints);
}
void MAIN_CHAR::installWeaponWSManager(WeaponParticleSystemManager *wpsMgr)
{
    if (mWeaponMgr) mWeaponMgr->installWeaponWSManager(wpsMgr);
}

void MAIN_CHAR::setEyePosition_Y(double y)
{
    mEyePosition.y = y;
}

void MAIN_CHAR::setWalkingMaxSpeed_Modifier(double walkingMaxSpeed)
{
    mSpeedFactor_Modifer = walkingMaxSpeed;
}


WEAPON_MANAGER *MAIN_CHAR::getWeaponManager( )
{
    return mWeaponMgr;
}

void MAIN_CHAR::setMaxBulletsNum(int a_Num)
{
    mCurBulletsNum = a_Num;
    mWeaponMgr->setMaxBulletsNum(mCurBulletsNum);
}

void MAIN_CHAR::attachCamera(Camera *a_Camera)
{
    mCamera = a_Camera;
    double dt = 0.0;
    walkForward(dt);
}

void MAIN_CHAR::updateCameraToFollowMainCharacter()
{
    Vector3 p = mSceneNode->getPosition();
    Vector3 pos = p + mEyePosition;
    Vector3 actualDirection = mCamera->getDirection();
    Vector3 new_eye_pos = pos - actualDirection * 5 + Vector3(0, 0, 0);

    // Make the camera follow the main character, mSceneNode
    mCamera->setPosition(new_eye_pos);
    mCamera->lookAt(pos);
}

//
// Make the main character to look at point in front of it.
// The look at direction is the camera direction.
// Make sure that the main character faces to the look-at direction.
//
// Then invoke updateCameraToFollowMainCharacter( ).
//
void MAIN_CHAR::updateViewDirection()
{
    Vector3 actualDirection;
    actualDirection = mCamera->getRealDirection();

    Vector3 p = mSceneNode->getPosition();
    actualDirection.y = 0.0;

    Vector3 point_in_front = p + actualDirection * 10;
    mSceneNode->lookAt(point_in_front, Node::TS_WORLD);
    mSceneNode->yaw(Radian(3.14159*0.5));

    //point_in_front is a point in front of the character,
    //i.e., p + actualDirection * k, where k is a positive value.
    //
    // Now make the main character look at point_in_front in the world frame.
    // Invoke lookAt of mSceneNode
    // with arguments (point_in_front, Node::TS_WORLD);
    //
    // Correct the orientation of the main character
    // due to the model initial orientation issue,
    // i.e., invoke mSceneNode->yaw(Radian(offset));

    //
    // The following line is correct.
    //
    updateCameraToFollowMainCharacter();
}

//
// void MAIN_CHAR::walkForward(double dt)
// is correct.
//
void MAIN_CHAR::walkForward(double dt)
{
    Vector3 actualDirection = mCamera->getRealDirection();

    Vector3 p = mSceneNode->getPosition();
    actualDirection.y = 0.0;

    mSceneNode->lookAt(p+ actualDirection*10, Node::TS_WORLD);
    mSceneNode->yaw(Radian(3.14159*0.5));

    actualDirection = mCamera->getRealDirection();
    Vector3 d;
    d = actualDirection*mSpeedFactor*dt
        *mSpeedFactor_Modifer;

    ///////////////////////////////////////////////
    basicTool_logMessage("MAIN_CHAR::walkForward:Direction\n");
    basicTool_logMessage(actualDirection);
    basicTool_logMessage(d);
    ///////////////////////////////////////////////

    mSceneNode->translate(d);
    setPosition_to_Environment(mSceneNode->getPosition());
    updateViewDirection();

    /*
    Vector3 pos = mSceneNode->getPosition();
    bool flg = basicTool_projectScenePointOntoTerrain_PosDirection(pos);
    if (flg == false) {
        basicTool_projectScenePointOntoTerrain_NegDirection(pos);
    }
    mSceneNode->setPosition(pos);

    Vector3 e = actualDirection*20;
    mCamera->setPosition(pos+mEyePosition+e);
    */
}

//
// This function has a bug.
//
void MAIN_CHAR::walkBackward(double dt)
{
    Vector3 actualDirection = mCamera->getRealDirection();

    Vector3 p = mSceneNode->getPosition();
    actualDirection.y = 0.0;

    mSceneNode->lookAt(p+ actualDirection*10, Node::TS_WORLD);
    mSceneNode->yaw(Radian(3.14159*0.5));

    actualDirection = mCamera->getRealDirection();
    Vector3 d;
    d = actualDirection*mSpeedFactor*dt
        *mSpeedFactor_Modifer;

    ///////////////////////////////////////////////
    basicTool_logMessage("MAIN_CHAR::walkBackward:Direction\n");
    basicTool_logMessage(actualDirection);
    basicTool_logMessage(-d);
    ///////////////////////////////////////////////

    mSceneNode->translate(-d);
    setPosition_to_Environment(mSceneNode->getPosition());
    updateViewDirection();
    /*
    Vector3 pos = mSceneNode->getPosition();
    bool flg = basicTool_projectScenePointOntoTerrain_PosDirection(pos);
    if (flg == false) {
        basicTool_projectScenePointOntoTerrain_NegDirection(pos);
    }
    mSceneNode->setPosition(pos);

    Vector3 e = actualDirection*20;
    mCamera->setPosition(pos+mEyePosition+e);
    */
}

void MAIN_CHAR::setPosition_to_Environment(const Vector3 &cur_p)
{
    Vector3 new_p;
    clampToEnvironment(cur_p, mDistanceOffsetToTerrain, new_p);
    mSceneNode->setPosition(new_p);
}

unsigned int MAIN_CHAR::getActionMode() const {
    return mActionMode;
}

void MAIN_CHAR::setWalkForward()
{
    mActionMode |= ACTION_WALK_FORWARD;
}

//
// Turn on the state of ACTION_WALK_BACKWARD,
// i.e., mActionMode |= ACTION_WALK_BACKWARD
//
void MAIN_CHAR::setWalkBackward()
{
    mActionMode |= ACTION_WALK_BACKWARD;
}

void MAIN_CHAR::unsetWalkForward()
{
    mActionMode ^= ACTION_WALK_FORWARD;
}
void MAIN_CHAR::unsetWalkBackward()
{
    mActionMode ^= ACTION_WALK_BACKWARD;

}

Vector3 MAIN_CHAR::getWeaponPosition() const
{
    Vector3 p = mSceneNode->getPosition();
    p += mEyePosition;
    Vector3 d = mCamera->getRealDirection();
    p += d*0.01;
    return p;
}



bool MAIN_CHAR::update(double dt)
{
    Vector3 p0 = mSceneNode->getPosition();
    ///////////////////////////////////////////
    if (mActionMode & ACTION_WALK_FORWARD) {
        walkForward(dt);
    }
    if (mActionMode & ACTION_WALK_BACKWARD) {
        walkBackward(dt);
    }

    fireWeapon();
    updateWeapon(dt);
    Real sf = 3.0;
    //if (mAnimationState == 0) {
    if (
        (mActionMode & ACTION_WALK_FORWARD)
        ||
        (mActionMode & ACTION_WALK_BACKWARD)
        ) {

            mAnimationState = mEntity->getAnimationState("Walk");
            mAnimationState->setLoop(true);
            mAnimationState->setEnabled(true);
            if (mActionMode & ACTION_WALK_FORWARD) {
                //move forward, animation
                mAnimationState->addTime(dt*sf);
            }
            else {
                //move backward, animation
                //mAnimationState->addTime(-dt*sf);
            }
    } else {
        mAnimationState = mEntity->getAnimationState("Idle");
        mAnimationState->setLoop(true);
        mAnimationState->setEnabled(true);
        mAnimationState->addTime(dt*sf);
    }
    //}

    Vector3 new_p;
    Vector3 cur_p = mSceneNode->getPosition();
    Vector3 modified_p;
    MAP_MANAGER::movePosition(p0, cur_p, modified_p);
    //
    clampToEnvironment(modified_p, 0.1, new_p);
    mSceneNode->setPosition(new_p);
    //


    updateCameraToFollowMainCharacter();

    return true; // Alive
}



void MAIN_CHAR::fireWeapon()
{
    Vector3 pos;
    Vector3 direction;
    if (mFireActionMode&FIRE_ACTION_NORMAL)
    {
        pos = getWeaponPosition();
        direction = mCamera->getRealDirection();
        mWeaponMgr->fire_Normal(pos, direction);
        mFireActionMode ^= FIRE_ACTION_NORMAL;
    }
}

void MAIN_CHAR::updateWeapon(double dt)
{
    mWeaponMgr->update(dt);
}

void MAIN_CHAR::setFireAction_Normal()
{
    //SOUND_MANAGER::getInstance()->play_Fire();
    //

    //
    // DO NOT CHANGE THIS LINE
    //
    mFireActionMode |= FIRE_ACTION_NORMAL;
}

void MAIN_CHAR::addExperience(double exp)
{
    if (exp <= 0.0) return;
    mExperiencePoints += exp;
    //static int count = 0;
    //count++;
    if (mExperiencePoints
        >= SystemParameter::getInstance()->charMaxExperiencePoints
        )
    {
        mExperiencePoints = SystemParameter::getInstance()
            ->charMaxExperiencePoints;
    }
    int c = mExperiencePoints;

    //
    // Play "you level up!" when the character's level is up.
    //
}

// current experience points
double MAIN_CHAR::getExperience() const
{
    return mExperiencePoints;
}

// maximum experience points
double MAIN_CHAR::getMaxExperience() const
{
    return mMaxExperiencePoints;
}
