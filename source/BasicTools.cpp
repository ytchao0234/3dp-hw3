//
// 3D Game Programming
// NYCU
// Instructor: Sai-Keung Wong
//
// Date: 30 Oct. 2022.
//
#include "BasicTools.h"

namespace {
	OgreBites::SdkTrayManager* sTrayMgr;
	Ogre::RaySceneQuery* sRaySceneQuery;
	Ogre::SceneManager* sSceneMgr;
	Ogre::Camera* sCamera;
};

using namespace Ogre;

//
// Call basicTool_Init to set the objects 
// (tray manager, scene manager, and camera)
// that will be used by this set of functions.
//

void basicTool_Init(
	OgreBites::SdkTrayManager* a_TrayMgr
	, Ogre::SceneManager* a_SceneMgr
	, Ogre::Camera* a_Camera
)
{
	sTrayMgr = a_TrayMgr;
	sSceneMgr = a_SceneMgr;
	sCamera = a_Camera;
	sRaySceneQuery = sSceneMgr->createRayQuery(Ogre::Ray());
}

//
// Generate a name out_name
// based on the prefix and index
// For example,
// prefix = "myObjects_"
// index = 12
// 
// out_name = "myObjects_12"
//
void basicTool_genNameUsingIndex(
	const Ogre::String& prefix
	, int index
	, Ogre::String& out_name)
{
	out_name = prefix 
		+ Ogre::StringConverter::toString(static_cast<int>(index));
}

//
// log a message msg to the log file
//
void basicTool_logMessage(const  Ogre::String& msg)
{
	Ogre::LogManager::getSingletonPtr()->logMessage(msg);
}

//
// log a Vector3 v to the log file
//
void basicTool_logMessage(const Ogre::Vector3& v)
{
	Ogre::String msg;
	std::stringstream out0;
	std::stringstream out1;
	std::stringstream out2;
	out0 << v.x;
	out1 << v.y;
	out2 << v.z;

	msg = out0.str() + "\t\t" + out1.str() + "\t\t" + out2.str();

	Ogre::LogManager::getSingletonPtr()->logMessage(msg);
}

void basicTool_logMessage(
	double v
)
{
	Ogre::String msg;
	std::stringstream out0;
	out0 << v;

	msg = out0.str();

	Ogre::LogManager::getSingletonPtr()->logMessage(msg);
}

void basicTool_logMessage(
	const Ogre::String &itemMsg
	, double v
)
{
	Ogre::String msg;
	std::stringstream out0;
	out0 << v;

	msg = itemMsg + out0.str();

	Ogre::LogManager::getSingletonPtr()->logMessage(msg);
}

//
// Cast a ray at position p along the up-direction (i.e., y-axis)
// If there is an intersection between the ray and the terrain,
// set the intersection point to p and return true.
// Otherwise return false.
//
bool basicTool_projectScenePointOntoTerrain_PosDirection(
	Ogre::Vector3& p
)
{
	//Ray mRay =sTrayMgr->getCursorRay(sCamera);
	sRaySceneQuery->setRay(Ray(p, Vector3(0, 1, 0)));

	// Perform the scene query
	RaySceneQueryResult& result =
		sRaySceneQuery->execute();
	RaySceneQueryResult::iterator itr = result.begin();

	bool flg = false;
	// Get the results, set the camera height
	// We are interested in the first intersection. It is ok to traverse all the results.
	if (itr != result.end() && itr->worldFragment)
	{
		p = itr->worldFragment->singleIntersection;

		flg = true;
	}
	return flg;
}

//
// Cast a ray at position p along the down-direction (i.e., negative y-axis)
// If there is an intersection between the ray and the terrain,
// set the intersection point to p and return true.
// Otherwise return false.
//
bool basicTool_projectScenePointOntoTerrain_NegDirection(
	Ogre::Vector3& p
)
{
	//Ray mRay =sTrayMgr->getCursorRay(sCamera);
	sRaySceneQuery->setRay(Ray(p, Vector3(0, -1, 0)));

	// Perform the scene query
	RaySceneQueryResult& result =
		sRaySceneQuery->execute();
	RaySceneQueryResult::iterator itr = result.begin();

	bool flg = false;

	// Get the results, set the camera height
	// We are interested in the first intersection. 
	// It is ok to traverse all the results.
	if (itr != result.end() && itr->worldFragment)
	{
		p = itr->worldFragment->singleIntersection;
		flg = true;
	}
	return flg;

}

//
// Create a particle system with the particle script particleScriptName.
// Return the scene node of the particle system.
// Later on, we can use the scene node to directly access the particle system.
//
Ogre::SceneNode* 
basicTool_initParticleSystemForExplosion(
	Ogre::SceneManager* sceneMgr
	, const char* particleName
	, const char* particleScriptName
) {
	Ogre::SceneNode* particleNode = static_cast<SceneNode*>(
		sceneMgr->getRootSceneNode()->createChild());
	ParticleSystem* p = sceneMgr->createParticleSystem(
		particleName, particleScriptName);

	ParticleEmitter* e = p->getEmitter(0);
	e->setEnabled(false);
	particleNode->attachObject(p);
	particleNode->setPosition(Vector3::ZERO);
	particleNode->setVisible(false);
	return particleNode;
}

//
// Use the scene node particleNode to activate the particle system
// associated with the scene node
// at position pos.
//
// particleName is not used.
//
void basicTool_setOffParticleSystem(
	Ogre::SceneNode* particleNode,
	const Ogre::String& particleName,
	const Ogre::Vector3& pos)
{
	particleNode->setPosition(pos);
	particleNode->setVisible(true);
	//MovableObject *s = particleNode->getAttachedObject(pname);
	MovableObject* s = particleNode->getAttachedObject(0);

	ParticleSystem* p = static_cast<ParticleSystem*>(s);
	if (p == NULL) return;
	p->setVisible(true);
	ParticleEmitter* e = p->getEmitter(0);
	e->setEnabled(true);
}

//
// Use the scene node particleNode to
// set the visibility flag flg_show
// of the particle system associated with the scene node.
// particleName is not used.
//
void basicTool_setVisibleParticleSystem(
	Ogre::SceneNode* particleNode,
	const Ogre::String& particleName,
	bool flg_show)
{
	particleNode->setVisible(flg_show);
	//MovableObject *s = particleNode->getAttachedObject(pname);
	MovableObject* s = particleNode->getAttachedObject(0);

	ParticleSystem* p = static_cast<ParticleSystem*>(s);
	if (p == NULL) return;
	p->setVisible(flg_show);
	ParticleEmitter* e = p->getEmitter(0);
	e->setEnabled(flg_show);
}