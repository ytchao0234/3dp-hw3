//
// 3D Game Programming
// National Yang Ming Chiao Tung University (NYCU), Taiwan
// Instructor: Sai-Keung Wong
// Date: 2022/10/05
//

#include "weapons.h"
#include "BasicTools.h"
#include "sound.h"
#include "sound_manager.h"
#include "map_manager.h"

extern SOUND* mSound;
WEAPON::WEAPON(SceneManager* a_SceneMgr) : GAME_OBJ(a_SceneMgr)
{
}

bool WEAPON::hitTarget_Sphere(
	const Vector3& p,
	Real r)
{
	bool flg = false;
	Vector3 pos = mSceneNode->getPosition();
	if (r >= pos.distance(p)) {
		Vector3 normal_dir = pos - p;
		normal_dir.normalise();
		Vector3 new_pos = p + (r + 0.5) * normal_dir;
		mSceneNode->setPosition(new_pos);
		Real d = mVelocity.dotProduct(normal_dir);
		if (0.0 >= d) {
			mVelocity = mVelocity - d * normal_dir;
			//mSound->init();
			//mSound->play();
			SOUND_MANAGER::getInstance()->play_Explosion();

		}
		flg = true;
	}
	return flg;
}

//
// Purpose:
// Determine if the weapon hits the target. 
// Use sphere-sphere intersection test.
// If yes, play a particle system at the hit position.
// Also, play a sound clip, e.g., explosion, etc.
// Furthermore, the weapon should bounce off from the target.
// so, need to compute a new velocity for the weapon.
// 
// Position p is the target position.
// r is the radius of the target.
// In our case, the target can the large sphere or others.
// 
// Return true: if hit
// Return false: otherwise, i.e., no hit
//
bool WEAPON::hitTarget_Sphere(
	const Vector3& p,
	Real r,
	WeaponParticleSystemManager* wpsMgr
)
{
	bool flg = false;
	// add your own stuff
	return flg;
}

//
// dt: simulation time step size
//
bool WEAPON::update(double dt)
{
	if (!mIsAlive) {
		return mIsAlive;
	}
	mLifeTime -= dt;
	if (mLifeTime < 0) {
		mLifeTime = 0;
		mSceneNode->setVisible(false);
		mIsAlive = false;
		return mIsAlive;
	}
	Vector3 pos = mSceneNode->getPosition();
	Vector3 old_pos = pos;		// Save the old position of the weapon

	//
	// Compute position of the weapon based on projectile motion.
	//
	pos += 0.2*mVelocity * dt;		// compute the temporary position
	/*
	pos += mVelocity * dt;		// compute the temporary position
	Vector3 grav(0, -29.8, 0);	// garvity
	mVelocity += grav * dt;		// update velocity for projectile motion
	*/

	//
	// Compute another temporary position due the interaction 
	// between the weapon and the terrain surface.
	// If the bullet hits the terrain, reverse its velocity direction
	// and reduce the magnitue of the velocity.
	//
	Vector3 new_pos = pos;
	Real r = 5;
	new_pos -= Vector3(0, 1, 0) * r;
	bool flg = basicTool_projectScenePointOntoTerrain_PosDirection(new_pos);
	if (flg) {
		pos = new_pos + Vector3(0, 1.0, 0) + Vector3(0, 1, 0) * r;
		//mVelocity.y = -mVelocity.y * 20;
	}
	
	//
	// Compute the final position of the weapon due to the interaction 
	// between the weapon and the wall structure.
	// If pos != modified_p, the weapon hits the wall structure.
	// The new velocity direction of the weapon is the reflection ray
	// of the current velocity direction.
	//
	Vector3 modified_p;
	modified_p = pos;
	MAP_MANAGER::movePosition(old_pos, pos, modified_p);
	if (pos != modified_p)
	{
		//
		// n is the wall normal
		//
		Vector3 n = MAP_MANAGER::getGridNormalVector(modified_p.x, modified_p.z);
		Real len = n.length();
		if (len != 0.0) {
			float d = mVelocity.dotProduct(n);

			//Vector3 new_v = reflection of mVelocity.
			//mVelocity = new_v;

			//Output the vector to the console window.
			//cout << "normal:" << n.x << "\t" << n.y << "\t" << n.z << endl;
		}
		pos = modified_p;
	}
	//
	mSceneNode->setPosition(pos);
	return mIsAlive;
}

void WEAPON::adjustDueToMap()
{
	Vector3 pos = mSceneNode->getPosition();
	Vector3 n = MAP_MANAGER::getGridNormalVector(pos.x, pos.z);
	Real len = n.length();
	if (len != 0.0) {
		float d = mVelocity.dotProduct(n);

		//mVelocity.x = -mVelocity.x; // This does not work
		//mVelocity.z = -mVelocity.z; // This does not work
		//

		// This is correct. Based on reflection ray
		Vector3 new_v = mVelocity - 2 * d * n; 
		mVelocity = new_v;

		//  cout << "normal:" << n.x << "\t" << n.y << "\t" << n.z << endl;

	}
}