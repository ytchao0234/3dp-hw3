//
// 3D Game Programming
// NYCU
// Instructor: Sai-Keung Wong
//
// Date: 30 Oct. 2022.
//
#include "monsters.h"
#include "BasicTools.h"

MONSTER::MONSTER(SceneManager *a_SceneMgr) : GAME_OBJ(a_SceneMgr)
{
}

//
// Set the monster to look at the target object, mTarget
//
void MONSTER::updateViewDirection()
{
    if (mTarget == 0) return;
    Vector3 pos = mTarget->getPosition();
    Vector3 target_pos = mSceneNode->getPosition();
    target_pos.x = pos.x;
    target_pos.z = pos.z;

    mSceneNode->lookAt(target_pos, Node::TS_WORLD);
    //yaw(Degree( mDegreeCorrection ) );
    mSceneNode->yaw(Degree(-3.14/5));
}

//
// mTarget is the main character.
// mTarget->getPosition() is the main character position
// 
// update the position of the monsters.
// make them look at the main character via updateViewDirection().
//
bool MONSTER::update(const Ogre::FrameEvent& evt)
{
    if (!mIsAlive) return mIsAlive;
    //
    Vector3 mv = mInitPosition - mTarget->getPosition();
    mv.y = 0.0;
    Real d = mv.length();
    mv.normalise();
    
    mVelocity -= evt.timeSinceLastFrame * mv * 10;

 

    //mTime += evt.timeSinceLastFrame + evt.timeSinceLastFrame * (5 * mRandSpeed);
    Vector3 offset(0, 0, 0);
    //offset.y = mAmplitude * sin(mTime);
    //if (mTime > 3.14159 * 2) {
    //   mTime -= 3.14159 * 2;
    //}

    Vector3 curPos = mSceneNode->getPosition();
    curPos += mVelocity * evt.timeSinceLastFrame;

    curPos.y = mInitPosition.y;
    mInitPosition = curPos;
    mVelocity *= (1-0.1*evt.timeSinceLastFrame);
    if (mVelocity.length() < 0.0001) {
        mVelocity = Vector3::ZERO;
    }
    Vector3 ip = mInitPosition;
    mSceneNode->setPosition(offset+ip);
    //
    updateViewDirection();

    return true; // Alive
}