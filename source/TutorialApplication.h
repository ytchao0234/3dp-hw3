//
// 3D Game Programming
// National Yang Ming Chiao Tung University (NYCU), Taiwan
// Instructor: Sai-Keung Wong
// Date: 2022/10/05
//
/*!
\brief 3D Game Programming
\n
My Name: Yu-Ting Chao
\n
My ID: 311551031
\n
My Email: ytchao.cs11@cs.nctu.edu.tw

This is an assignment of 3D Game Programming

*/

#ifndef __BasicTutorial_00_h_
#define __BasicTutorial_00_h_

#include "BaseApplication.h"
#include "main_char.h"
#include "monster_manager.h"
#include "sound.h"
#include "bar2D.h"
#include "digit_string_dialogue.h"
#include "wago_ogre_mesh.h"
#include "WeaponParticleSystemManager.h"
#include "attack_defense_system.h"

class BasicTutorial_00 : public BaseApplication
{
public:
	BasicTutorial_00(void);
protected:

	virtual bool frameStarted(const Ogre::FrameEvent& evt);
	virtual void createViewports(void);
	virtual void createScene(void);
	virtual void createCamera(void);
	virtual void chooseSceneManager(void);

	//
	virtual bool update_MiniMapCamera(double dt);
	virtual bool update_LargeSphere(double dt);
	virtual bool update_Light(double dt);
	virtual bool update_Character(double dt);
	virtual bool update_CharacterLevel_UI(double dt);
	virtual bool update_CharacterInternalState_UI(double dt);
	virtual bool update_CharacterExperience_UI(double dt);
	virtual bool update_CharacterWalkSpeed(double dt);
	virtual bool update_Score_UI(int new_score, double dt);
	virtual bool update_ParticleSystems(double dt);
	virtual bool checkGoOnGameStatus(double dt);
	virtual bool adjust_MainCharacterPosition_InteractionWithLargeSphere(double dt);
	virtual void checkVictory(double dt);
	//
	virtual bool keyPressed_CharacterPosition(
		const OIS::KeyEvent& arg
	);
	virtual bool keyPressed_UpdateCharacterState(
		const OIS::KeyEvent& arg
	);
	virtual bool keyPressed_UpdateCameraState(
		const OIS::KeyEvent& arg
	);
	virtual bool keyPressed_UpdateSystemState(
		const OIS::KeyEvent& arg
	);
	virtual bool keyPressed(const OIS::KeyEvent& arg);
	virtual bool keyReleased(const OIS::KeyEvent& arg);
	//
	virtual bool mouseMoved(const OIS::MouseEvent& arg);
	virtual bool mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id);
	virtual bool mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id);
	//


	//
	virtual void createWaterSurface();
	virtual void createLights();
	virtual void createParticleSystems();
	virtual void createLargeSphere();
	virtual void createMapMesh();
	virtual void createAvatar();
	virtual void createMonsterManager();
	virtual void createStatusBars();
	virtual void setupAttackDefenseSystem();


private:
	/*!
	\brief Create a viewport

	Create a viewport for the entire screen.

	\return The sum of two integers.
	*/
	void createViewport_Main(void);
	void createViewport_MiniMap(void);
	//
	void createCamera_00();
	void createCamera_01();

	void createScene_MainScene();
	void createScene_01();

	SIMPLE_TERRAIN* mMapMesh;

	//
	// true: update all the game items
	// false: do not update game items
	//
	bool mFlgGoOnGame;
	//
	bool mKeyPressed_StopKey;
	Ogre::Real mToggle_CumulativeTime;
	Ogre::Light* mLight0;

	Ogre::SceneNode* mParticleMainNode;

	int mNumParticleNodes;
	Ogre::SceneNode* mParticleNode[16];

	Ogre::SceneNode* mSceneNode_Sphere;
	Ogre::Camera* mCameraArr[8];
	Ogre::SceneManager* mSceneMgrArr[8];
	OgreBites::SdkCameraMan* mCameraManArr[8];
	//
	Real mSphereRadius;
	int mMiniMap_KeyPressedZoomMode;

	Real mMiniMap_CameraDistanceSlowDownSpeed;
	Real mMiniMap_CameraDistance;
	Real mMiniMap_CameraDistanceAdjustSpeed;

	MAIN_CHAR* mMainChar;
	MONSTER_MANAGER* mMonsterMgr;
	//
	float mStamina;
	float mStamina_Min;
	float mStamina_Max;

	BAR_2D* mBar2D_Stamina;
	BAR_2D* mBar2D_2_Speed;
	BAR_2D* mBar2D_Experience;

	float mScoreCoord_X;
	float mScoreCoord_MaxX;
	float mScoreCoord_MinX;
	bool mScoreBoard_Direction;
	float mfScore;
	int mScore;
	DIGIT_STRING_DIALOGUE* mDigitDialogue;
	//
	int mLevel;
	DIGIT_STRING_DIALOGUE* mDigitDialogue_Level;
	//
	WeaponParticleSystemManager* mWeaponPSMgr;
	//
	bool mTurnOnParticleSystems;

	ATTACK_DEFENSE_SYSTEM* mAttackDefenseSystem;
	WeaponParticleSystemManager* mHitMonsterPSMgr;

	double mMax_dt; // maximum simulation time step size

	bool mFlg_Victory;
};

#endif // #ifndef __BasicTutorial_00_h_