//
// 3D Game Programming
// National Yang Ming Chiao Tung University (NYCU), Taiwan
// Instructor: Sai-Keung Wong
// Date: 2022/10/05
//

#ifndef __DATA_READER_H__
#define __DATA_READER_H__

#include <string>

class MESH_INFO {
public:
	MESH_INFO();
	std::string mMeshName;
	double mMeshScale;
	double mDegreeCorrection;
};

class READER_DATA {
protected:
	static std::string mVersion;

	static bool mEnableExpFog;
	static bool mEnableShadow;
	static float mExpFogDensity;
	static int mMaxBulletsNum;
	static int mMaxMonstersNum;
	static float mBulletSpeed;
	static double mWaterCoord_Y;
	static std::string mWaterMaterialName;
	static MESH_INFO mMeshInfo;
	//
	static std::string mAvatarMesh;
	static double mAvatarEyePosition_Y;
	static double mAvatar_WalkingMaxSpeed;
	//
	static int mVictoryPoints;
	//
	static std::string mMapBitMapName;

	//
	static std::string mSoundFile_Explosion;
	static std::string mSoundFile_Fire;
	static std::string mSoundFile_Stamina;
	static std::string mSoundFile_LevelUp;
	static std::string mSoundFile_Victory;
public:
	READER_DATA();
	static void readData();
	static void readData(const std::string& fileName);
	//
	static std::string getVersion();

	static bool isEnabledShadow();
	static bool isEnabledExpFog();
	static float getExpFogDensity();
	static int getMaxBulletsNum();
	static int getMaxMonstersNum();
	static float getBulletSpeed();
	static double getWaterCoord_Y();
	static std::string getWaterMaterialName();
	static std::string getMeshName();
	static double getMeshScale();
	static double getMeshDegreeCorrection();
	//
	static double getAvatarEyePosition_Y();
	static std::string getAvatarMeshName();
	static double getAvatarWalkingMaxSpeed();
	//
	static int getVictoryPoints();
	// 
	static std::string READER_DATA::getMap_BitMap_Name();
	//
	static std::string getSoundFileName_Explosion();
	static std::string getSoundFileName_Fire();
	static std::string getSoundFileName_Stamina();
	static std::string getSoundFileName_LevelUp();
	static std::string getSoundFileName_Victory();

	//
	static void report();
};

#endif