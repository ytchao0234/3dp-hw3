//
// 3D Game Programming
// National Yang Ming Chiao Tung University (NYCU), Taiwan
// Instructor: Sai-Keung Wong
// Date: 2022/10/05
//

#include <fstream>
#include <iostream>
#include <string>
#include "reader_data.h"
#define DATA_FILE_NAME	"game_data.txt"

using namespace std;
//
MESH_INFO::MESH_INFO() :
	mMeshName("penguin.mesh")
	, mMeshScale(1.0)
	, mDegreeCorrection(00.0)
{

}

//
std::string READER_DATA::mVersion = "0.11";
//
std::string READER_DATA::mMapBitMapName = "wago_game_map01.png";
bool READER_DATA::mEnableShadow = true;
int	READER_DATA::mMaxBulletsNum = 10;
int	READER_DATA::mMaxMonstersNum = 10;
float READER_DATA::mBulletSpeed = 10.0;
double	READER_DATA::mWaterCoord_Y = 0.0;
std::string READER_DATA::mWaterMaterialName = "";

MESH_INFO READER_DATA::mMeshInfo;

bool READER_DATA::mEnableExpFog = true;
float READER_DATA::mExpFogDensity = 0.0003;

//
std::string READER_DATA::mAvatarMesh = "robot.mesh";
double READER_DATA::mAvatarEyePosition_Y = 120;
double READER_DATA::mAvatar_WalkingMaxSpeed = 5;


int READER_DATA::mVictoryPoints = 20;


//
std::string READER_DATA::mSoundFile_Explosion = "missle.wav";
std::string READER_DATA::mSoundFile_Fire = "missle.wav";
std::string READER_DATA::mSoundFile_Stamina = "missle.wav";
std::string READER_DATA::mSoundFile_LevelUp = "missle.wav";
std::string READER_DATA::mSoundFile_Victory = "missle.wav";

//
READER_DATA::READER_DATA()
{

}
void READER_DATA::readData()
{
	readData(DATA_FILE_NAME);
}

void READER_DATA::readData(const std::string& fileName)
{
	cout << "Begin READER_DATA::readData()" << endl;
	using namespace std;
	std::ifstream* fp;
	fp = new std::ifstream(fileName, ios::in | ios::binary);
	if (fp == 0 || fp->fail()) {
		cout << "Cannot open data file:" << DATA_FILE_NAME << endl;
		return;
	}

	std::string key;
	double num;
	while (!fp->eof()) {
		*fp >> key;

		cout << "Reading:" << key << endl;


		if (key.compare("VERSION") == 0) {
			*fp >> mVersion;

		}
		
		if (key.compare("MAP_BITMAP_NAME") == 0) {
			*fp >> mMapBitMapName;
		}

		if (key.compare("NUM_BULLETS") == 0) {
			*fp >> num;
			mMaxBulletsNum = num;
		}

		if (key.compare("NUM_MONSTERS") == 0) {
			*fp >> num;
			mMaxMonstersNum = num;
		}

		if (key.compare("BULLET_SPEED") == 0) {
			*fp >> mBulletSpeed;
		}


		if (key.compare("WATER_Y_COORD") == 0) {
			*fp >> num;
			mWaterCoord_Y = num;
		}

		if (key.compare("MESH_SCALE") == 0) {
			double meshScale;
			*fp >> meshScale;
			mMeshInfo.mMeshScale = meshScale;

		}

		if (key.compare("WATER_MATERIAL") == 0) {
			*fp >> mWaterMaterialName;

		}
		if (key.compare("MESH_NAME") == 0) {
			string meshName;
			*fp >> meshName;
			mMeshInfo.mMeshName = meshName;

			double degreeCorrection;
			*fp >> degreeCorrection;
			mMeshInfo.mDegreeCorrection = degreeCorrection;

		}
		if (key.compare("EXP_FOG_ENABLED") == 0) {
			*fp >> mEnableExpFog;
			*fp >> mExpFogDensity;
		}

		if (key.compare("SHADOW_ENABLED") == 0) {
			*fp >> mEnableShadow;

		}

		if (key.compare("AVATAR_EYE_POSITION_Y") == 0) {
			*fp >> mAvatarEyePosition_Y;

		}

		if (key.compare("AVATAR_MESH") == 0) {
			*fp >> mAvatarMesh;

		}

		if (key.compare("AVATAR_WALKING_MAX_SPEED") == 0) {
			*fp >> mAvatar_WalkingMaxSpeed;

		}

		if (key.compare("VICTORY_POINTS") == 0) {
			*fp >> mVictoryPoints;

		}

		if (key.compare("SOUND_WAVE_FILE_EXPLOSION") == 0) {
			//
		}
		if (key.compare("SOUND_WAVE_FILE_FIRE") == 0) {
			//
		}
		if (key.compare("SOUND_WAVE_FILE_STAMINA") == 0) {
			//
		}
		if (key.compare("SOUND_WAVE_FILE_LEVEL_UP") == 0) {
			//
		}
		if (key.compare("SOUND_WAVE_FILE_VICTORY") == 0) {
			//
		}




		key.clear(); // a must here
	}

	report();

	cout << "End READER_DATA::readData()" << endl;

}

std::string READER_DATA::getVersion()
{
	return mVersion;
}

bool READER_DATA::isEnabledShadow()
{
	return mEnableShadow;
}

int READER_DATA::getMaxBulletsNum()
{
	return mMaxBulletsNum;
}

float READER_DATA::getBulletSpeed()
{
	return mBulletSpeed;
}
bool READER_DATA::isEnabledExpFog()
{
	return mEnableExpFog;
}

float READER_DATA::getExpFogDensity()
{
	return mExpFogDensity;
}


int READER_DATA::getMaxMonstersNum()
{
	return mMaxMonstersNum;
}

double READER_DATA::getMeshScale()
{
	return mMeshInfo.mMeshScale;
}

double READER_DATA::getMeshDegreeCorrection()
{
	return mMeshInfo.mDegreeCorrection;
}

double READER_DATA::getWaterCoord_Y()
{
	return mWaterCoord_Y;
}

std::string READER_DATA::getWaterMaterialName()
{
	return mWaterMaterialName;
}

std::string READER_DATA::getMeshName()
{
	return mMeshInfo.mMeshName;
}

double READER_DATA::getAvatarEyePosition_Y() {
	return mAvatarEyePosition_Y;
}

std::string READER_DATA::getAvatarMeshName() {
	return mAvatarMesh;
}

double READER_DATA::getAvatarWalkingMaxSpeed() {
	return mAvatar_WalkingMaxSpeed;
}

//mSoundFile_Fire
std::string READER_DATA::getSoundFileName_Fire() {
	return mSoundFile_Fire;
}

//mSoundFile_Explosion
std::string READER_DATA::getSoundFileName_Explosion() {
	return std::string("");
}

//mSoundFile_Stamina
std::string READER_DATA::getSoundFileName_Stamina() {
	return std::string("");
}

//mSoundFile_LevelUp
std::string READER_DATA::getSoundFileName_LevelUp() {
	return std::string("");
}

//mSoundFile_Victory
std::string READER_DATA::getSoundFileName_Victory()
{
	return std::string("");
}

int READER_DATA::getVictoryPoints()
{
	return mVictoryPoints;
}

std::string READER_DATA::getMap_BitMap_Name()
{
	return mMapBitMapName;

}

void READER_DATA::report()
{
	cout << "READER_DATA::report" << endl;

	cout << "mVersion:" << "\t" << mVersion << endl;
	cout << "mMapBitMapName:" << "\t" << mMapBitMapName << endl;
	
	cout << "mEnableExpFog:" << "\t" << mEnableExpFog << endl;
	cout << "mEnableShadow:" << "\t" << mEnableShadow << endl;
	cout << "mExpFogDensity:" << "\t" << mExpFogDensity << endl;
	cout << "mMaxBulletsNum:" << "\t" << mMaxBulletsNum << endl;
	cout << "mMaxMonstersNum:" << "\t" << mMaxMonstersNum << endl;
	cout << "mBulletSpeed:" << "\t" << mBulletSpeed << endl;
	cout << "mWaterCoord_Y:" << "\t" << mWaterCoord_Y << endl;
	cout << "mExpFogDensity:" << "\t" << mExpFogDensity << endl;
	cout << "mWaterMaterialName:" << "\t" << mWaterMaterialName << endl;
	cout << "mMeshName:" << "\t" << mMeshInfo.mMeshName << endl;
	cout << "mMeshScale:" << "\t" << mMeshInfo.mMeshScale << endl;
	cout << "mDegreeCorrection:" << "\t" << mMeshInfo.mDegreeCorrection << endl;
	cout << "mAvatarMesh:" << "\t" << mAvatarMesh << endl;
	cout << "mAvatarEyePosition_Y:" << "\t" << mAvatarEyePosition_Y << endl;
	cout << "mAvatar_WalkingMaxSpeed:" << "\t" << mAvatar_WalkingMaxSpeed << endl;
}