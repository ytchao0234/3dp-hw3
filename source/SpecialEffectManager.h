//
// Student Name:
// Student ID:
// Student Email Address:
//
//
// 3D Game Programming
// National Yang Ming Chiao Tung University (NYCU), Taiwan
// Instructor: Sai-Keung Wong
// Date: 2022/10/05
//
// Select and move characters

#ifndef __ParticleSystemManager_h_
#define __ParticleSystemManager_h_
 
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreParticleSystem.h>
#include <OgreParticleEmitter.h>
#include <string>

using namespace Ogre;

class SpecialEffectManager {
protected:
    SceneManager *mSceneMgr;
    int mNumParticleSystems;
    SceneNode **mParticleNodes;
    ParticleEmitter **mParticleEmitters;
    int mCurrentIndex;
    //
    const std::string *mParticleSystemNames;
    //
    void createParticleSystem(const Ogre::String& prefix, int index);
public:
    SpecialEffectManager();
    SpecialEffectManager(SceneManager *sceneMgr);
    SpecialEffectManager(
    SceneManager *sceneMgr,
    const std::string *particleSystemNames,
    int numParticleSystems
    );
    SpecialEffectManager(
        SceneManager *sceneMgr,
        int numParticleSystems);

    void init(const Ogre::String& prefix);
    int getNumParticleSystems() const { return mNumParticleSystems; }
    int setOffParticleSystem(const Ogre::Vector3 &pos);
    void setOffParticleSystem(int pIndex, const Ogre::Vector3 &pos);
    void disableAllParticleSystems();
    void enableAllParticleSystems();
    virtual int getFreeParticleSystemIndex() const { return -1;}
    virtual void play(const Vector3 &pos) { }
    virtual void play(int pIndex, const Vector3 &p) { }

};

#endif
