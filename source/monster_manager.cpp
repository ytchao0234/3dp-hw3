//
// 3D Game Programming
// NYCU
// Instructor: Sai-Keung Wong
//
// Date: 30 Oct. 2022.
//

#include "monster_manager.h"
#include "reader_data.h"
#include "BasicTools.h"
#include "map_manager.h"
//
// mNumMonsters is the total number of monsters.
// mCurMonstersNum is the current number of monsters that are activated.
//
MONSTER_MANAGER::MONSTER_MANAGER(
	SceneManager *a_SceneMgr
	, const Vector3& character_start_pos)
	: GAME_OBJ(a_SceneMgr)
{

	mMonstersTarget = 0;
	mCurMonstersNum = mNumMonsters = 512;
	//
	Vector3 org = character_start_pos;

	for (int i = 0; i < mNumMonsters; ++i) 
	{
		mLifeStateArr[i] = true;
		mMonstersArr[i] = new MONSTER(a_SceneMgr);
		String meshName = "ogrehead.mesh";
		//READER_DATA::getMeshName()
		mMonstersArr[i]->createGameObj("m", meshName);
		
		Vector3 pos;
		Real x = -1+2*(rand()%100)/100.0;
		Real z = -1+2*(rand()%100)/100.0;
		pos.x = 7700*x;
		pos.z = 7700*z;
		pos.y = 20;

		mMonstersArr[i]->setPosition(pos+org);
		mMonstersArr[i]->setInitPosition(pos+org);
		Real sx, sy, sz;
		sx = sy = sz = READER_DATA::getMeshScale();
		mMonstersArr[i]->scale(sx, sy, sz);
        double degreeCorrection = READER_DATA::getMeshDegreeCorrection( );
        mMonstersArr[i]->setDegreeCorrection( degreeCorrection );
	}

}
void MONSTER_MANAGER::setMaxMonstersNum(int a_Num)
{
	if (a_Num >= mNumMonsters) 
	{
		a_Num = mNumMonsters;
	}


	mCurMonstersNum = a_Num;
	for (int i = 0; i < mNumMonsters; ++i) 
	{
		//if (i<mCurMonstersNum) {
			mMonstersArr[i]->setVisible(true);
			mMonstersArr[i]->makeAlive(true);
		//} else {
	}
}

void MONSTER_MANAGER::setTargetForMonsters(GAME_OBJ *a_Target)
{

	mMonstersTarget = a_Target;
	for (int i = 0; i < mNumMonsters; ++i) 
	{
		Vector3 p = mMonstersArr[i]->getInitPosition();
		mMonstersArr[i]->setTarget(a_Target, 0);
	}
}

//
// mMonstersTarget is the main character.
//
void MONSTER_MANAGER::resolveMonsterTargetCollision()
{
	if (mMonstersTarget == 0) return;	
	Vector3 p1 = mMonstersTarget->getPosition();
	for (int i = 0; i < mCurMonstersNum; ++i) 
	{
		if (!mMonstersArr[i]->isAlive()) continue;

		Vector3 p0 = mMonstersArr[i]->getPosition();
		Vector3 mm = p0 - p1;
		mm.y = 0;
		Real d = mm.length();
		mm.normalise();
        //
		// Adjust the monster position 
		// if the monster collides with the main character.
		//
	}
}

void MONSTER_MANAGER::resolveMonsterCollision()
{
	for (int i = 0; i < mCurMonstersNum; ++i) 
	{
		if (!mMonstersArr[i]->isAlive()) continue;
		for (int j = i+1; j < mCurMonstersNum; ++j) 
		{
			if (!mMonstersArr[j]->isAlive()) continue;
			//
			Vector3 p0 = mMonstersArr[i]->getPosition();
			Vector3 p1 = mMonstersArr[j]->getPosition();

			//
			// Move the monsters i and j away from each other
			//
		}
	}
}


bool MONSTER_MANAGER::update(const Ogre::FrameEvent& evt)
{
	for (int i = 0; i < mCurMonstersNum; ++i) 
	{
		if (!mMonstersArr[i]->isAlive()) continue;

		Vector3 p = mMonstersArr[i]->getInitPosition();
		mMonstersArr[i]->update(evt);
	}
	resolveMonsterTargetCollision();
	resolveMonsterCollision();
	/*
	resolveMonsterTargetCollision();
	resolveMonsterCollision();
	resolveMonsterTargetCollision();
	resolveMonsterCollision();
	resolveMonsterTargetCollision();
	resolveMonsterCollision();
	resolveMonsterTargetCollision();
	*/

    return true;
}

//
// pos is the main character position.
// numParticles is the total number of particle systems that can be used.
// particleNodes store the scene nodes of all the particle systems.
//

void MONSTER_MANAGER::setParticleSystem(
    const Vector3 &pos,
    int numParticles,
    SceneNode **particleNodes
    )
{
    int particleCount = 0;
    for (int i = 0; i < mCurMonstersNum; ++i) 
    {
        Vector3 q = mMonstersArr[i]->getInitPosition();
        float d = pos.distance(q);
        if (particleCount >= numParticles) break;
		double threshold = 600;
        if (d < threshold) {
			// set the particle scene node to be visible.
			// set the particle system to be visible
			// Add your own stuff

            ++particleCount;
        }
    }

	//
	// turn of all the other particle systems
    for (int i = particleCount; i < numParticles; ++i )
    {
        particleNodes[particleCount]->setVisible(false);

    }
}

void MONSTER_MANAGER::init_Traversal() {
	mCounter_Traversal = 0;
}

MONSTER* MONSTER_MANAGER::getObj_Traversal()
{
	MONSTER* m = nullptr;
	if (mCounter_Traversal >= mCurMonstersNum) return m;
	while (mCounter_Traversal < mCurMonstersNum) {
		++mCounter_Traversal;
		if (mMonstersArr[mCounter_Traversal - 1]->isAlive()) {
			m = mMonstersArr[mCounter_Traversal - 1];
			break;
		}
	}
	return m;
}
