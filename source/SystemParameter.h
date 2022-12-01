//
// 3D Game Programming
// National Yang Ming Chiao Tung University (NYCU), Taiwan
// Instructor: Sai-Keung Wong
// Date: 2022/10/05
//
//
//#pragma once
//header guard
#ifndef __SYSTEM_PARAMETER_H_
#define __SYSTEM_PARAMETER_H_
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
//
// Use SystemParameter as a global variable container.
//
class SystemParameter {
private:
    static SystemParameter* _instance;
public:
    SystemParameter( );
    static SystemParameter* getInstance() {
        if (!_instance) _instance = new SystemParameter;
        return _instance;
    }
public:
     double radius;
     double maxSpeed;
     double acceleration;
     int maxNumParticleSystems;
     double stopGameMaxTime;
     double maxSimulationTimeStepSize;
     double charMaxExperiencePoints;
};

#endif