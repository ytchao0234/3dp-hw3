//
// 3D Game Programming
// National Yang Ming Chiao Tung University (NYCU), Taiwan
// Instructor: Sai-Keung Wong
// Date: 2022/10/05
//
//
// Purpose: Set up the scenes.
//
//
//
#include "TutorialApplication.h"
#include "BasicTools.h"
#include "SystemParameter.h"
#include "reader_data.h"
#include "reader_config.h"
#include "map_manager.h"
#include "sound_manager.h"
#include "envTools.h"

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <math.h>

using namespace Ogre;

void BasicTutorial_00::createWaterSurface()
{
	Vector3 org = Vector3(0, 51, 0);

	Plane plane(Vector3::UNIT_Y, 0);
	MeshManager::getSingleton().createPlane(
		"ground", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		plane,
		15000, 15000, 	// width, height
		20, 20, 		// x- and y-segments
		true, 		// normal
		1, 			// num texture sets
		5, 5, 		// x- and y-tiles
		Vector3::UNIT_Z	// upward vector
	);

	Entity* ent = mSceneMgr->createEntity(
		"GroundEntity", "ground");
	//ent->setMaterialName("Examples/BeachStones");
	//ent->setMaterialName("Examples/WaterStream");

	ent->setMaterialName(READER_DATA::getWaterMaterialName());
	Vector3 waterCoordY;
	waterCoordY.y = READER_DATA::getWaterCoord_Y();
	SceneNode* snode = mSceneMgr
		->getRootSceneNode()
		->createChildSceneNode(waterCoordY);

	snode->attachObject(ent);
	//snode->translate(org);

}

void BasicTutorial_00::createLights()
{
	Light* light;
	light = mSceneMgr->createLight("Light1");
	light->setType(Light::LT_POINT);
	//light->setType(Light::LT_DIRECTIONAL);
	light->setPosition(Vector3(0, 450, 250));
	light->setDiffuseColour(0.7, 0.7, 0.7);
	light->setSpecularColour(1.0, 1.0, 1.0);
	light->setDirection(Vector3(1, 1, 1));
	mLight0 = light;

}

void BasicTutorial_00::createParticleSystems()
{
	mParticleMainNode = basicTool_initParticleSystemForExplosion(
		mSceneMgr,
		"explosion");
	Vector3 pos;
	basicTool_setOffParticleSystem(mParticleMainNode, "explosion", pos);

	mNumParticleNodes = 16;
	for (int i = 0; i < mNumParticleNodes; ++i) {
		String pname;
		basicTool_genNameUsingIndex("p", i, pname);
		mParticleNode[i] = basicTool_initParticleSystemForExplosion(
			mSceneMgr,
			pname.data());
		mParticleNode[i]->setVisible(false);
	}

}

void BasicTutorial_00::createLargeSphere()
{
	Vector3 org = Vector3(750, 51, 750);

	Entity* ent2
		= mSceneMgr
		->createEntity("Robot2", "sphere.mesh");
	//ent2->setCastShadows(true);



	ent2->setMaterialName("Examples/SphereMappedRustySteel");
	SceneNode* node2 = mSceneNode_Sphere
		= mSceneMgr
		->getRootSceneNode()
		->createChildSceneNode(
			"RobotNode2", org + Vector3(0, 50, 0));
	Real scalingFactor = 2.0;
	mSceneNode_Sphere->scale(scalingFactor, scalingFactor, scalingFactor);
	mSphereRadius = ent2->getBoundingRadius();
	mSphereRadius *= scalingFactor * 0.7;
	node2->attachObject(ent2);

}

void BasicTutorial_00::createMapMesh()
{
	mMapMesh = new SIMPLE_TERRAIN(mSceneMgr);
	mMapMesh->setMaterial("Examples/Rockwall_Wingo");
	mMapMesh->create();
	//mMapMesh->translateSceneNode(10000, -300, 10000);
	mMapMesh->translateSceneNode(0, -300, 0);
	mMapMesh->dilateMapObstacles(2);
	mMapMesh->computeNormalVectors();
	mMapMesh->scanMapForLocatingObjects();

	MAP_MANAGER::installMeshMapManager(mMapMesh);
}

void BasicTutorial_00::createAvatar()
{
	mMainChar = new MAIN_CHAR(mSceneMgrArr[0]);
	//
	mMainChar->createGameObj("avatar", READER_DATA::getAvatarMeshName());
	mMainChar->setEyePosition_Y(READER_DATA::getAvatarEyePosition_Y());
	//mMainChar->setVisibilityFlags(0x10);
	mMainChar->attachCamera(mCameraArr[0]);

	mMainChar->setMaxBulletsNum(READER_DATA::getMaxBulletsNum());
	mMainChar->setWalkingMaxSpeed_Modifier(
		READER_DATA::getAvatarWalkingMaxSpeed()
	);


	Vector3 character_start_pos;
	mMapMesh->getStartingPosition(character_start_pos);
	mMainChar->setPosition_to_Environment(character_start_pos);
	mMainChar->installWeaponWSManager(mWeaponPSMgr);
}

void BasicTutorial_00::createMonsterManager()
{
	Vector3 character_start_pos;
	mMapMesh->getStartingPosition(character_start_pos);
	mMonsterMgr = new MONSTER_MANAGER(
		mSceneMgrArr[0]
		, character_start_pos
	);

	mMonsterMgr->setTargetForMonsters(mMainChar);
	mMonsterMgr->setMaxMonstersNum(READER_DATA::getMaxMonstersNum());
}

void BasicTutorial_00::createStatusBars() {
	mBar2D_Stamina = new BAR_2D(mSceneMgr, "wago_game/StaminaBar", NULL);
	mBar2D_Stamina->setDefaultPos(0.05, 0.55);

	mBar2D_2_Speed = new BAR_2D(mSceneMgr, "wago_game/LifeBar", NULL);
	mBar2D_2_Speed->setDefaultPos(0.05, 0.65);
	//
	//
	mBar2D_Experience = new BAR_2D(mSceneMgr, "Examples/ExpBar", NULL);
	mBar2D_Experience->setDefaultPos(0.3, 0.9);
	mBar2D_Experience->setBarDimension(0.6, 0.01);
	//
	mScore = 0;
	mDigitDialogue = new DIGIT_STRING_DIALOGUE(mSceneMgr, "Examples/Digits");
	mDigitDialogue->setScore(mScore, 0.05, 0.05);

	//mLevel = 123;
	mDigitDialogue_Level = new DIGIT_STRING_DIALOGUE(mSceneMgr, "Examples/Digits");
	mDigitDialogue_Level->setScore(mLevel, 0.05, 0.1);
}

void BasicTutorial_00::setupAttackDefenseSystem()
{
	mAttackDefenseSystem = new ATTACK_DEFENSE_SYSTEM(
		mMonsterMgr
		, mMainChar->getWeaponManager()
	);
}
void BasicTutorial_00::createScene_MainScene(void)
{
	Ogre::LogManager::getSingletonPtr()->logMessage(
		"*** createScene_MainScene ***"
	);

	Ogre::LogManager::getSingletonPtr()->logMessage(
		"*** DATA_CONFIG::readData() ***"
	);

	READER_CONFIG::readData();

	Ogre::LogManager::getSingletonPtr()->logMessage(
		"*** DATA_READER::readData() ***"
	);

	READER_DATA::readData(READER_CONFIG::getDataFileName());

	basicTool_Init(mTrayMgr, mSceneMgrArr[0], mCameraArr[0]);
	//
	initEnvTools(mSceneMgrArr[0]);
	//
	SystemParameter::getInstance()->charMaxExperiencePoints
		= READER_DATA::getVictoryPoints( );
	//
	mSceneMgr = mSceneMgrArr[0];
	//
	mWeaponPSMgr = new WeaponParticleSystemManager(mSceneMgr);
	mWeaponPSMgr->init("weaponFX");
	//

	mHitMonsterPSMgr = new WeaponParticleSystemManager(mSceneMgr);
	mHitMonsterPSMgr->init("hitMonsterFX");

	//
	ColourValue fadeColour(0.9, 0.9, 0.9);

	//This line should put before SetWorldGeometry

	if (READER_DATA::isEnabledExpFog()) {
		Real density = READER_DATA::getExpFogDensity();
		mSceneMgr->setFog(FOG_EXP, fadeColour, density);
	}
	mSceneMgr->setWorldGeometry("terrain.cfg");


	mSceneMgr->setSkyBox(
		true,
		"Examples/TrippySkyBox");




	if (READER_DATA::isEnabledShadow()) {
		mSceneMgr->setShadowTechnique(
			SHADOWTYPE_TEXTURE_MODULATIVE);
		//SHADOWTYPE_TEXTURE_ADDITIVE);
	//SHADOWTYPE_STENCIL_MODULATIVE);
	}

	//

	mSceneMgr->setAmbientLight(ColourValue(0.7, 0.7, 0.7));
	//mSceneMgr->setAmbientLight( ColourValue( 1, 1, 1 ) );

	Ogre::LogManager::getSingletonPtr()->logMessage(
		"***createLights() ***"
	);

	createMapMesh();

	createLights();
	createParticleSystems();
	createLargeSphere();
	//
	createWaterSurface();
	//
	createAvatar();
	//
	createMonsterManager();
	createStatusBars();
	//
	setupAttackDefenseSystem();
	//
	SOUND_MANAGER::getInstance();
	//
	//Ogre::LogManager::getSingletonPtr()->logMessage(
	//	"*** DATA_READER::createStatusBars() ***"
	//);
}

//
// Do not need to create anything.
//
void BasicTutorial_00::createScene_01(void)
{
	return;
}

void BasicTutorial_00::createScene(void) {
	createScene_MainScene();
	createScene_01();
	//mSceneMgr = mSceneMgrArr[0]; // active SceneManager
	mSceneMgr = mSceneMgrArr[1]; // active SceneManager
}