//
// 3D Game Programming
// National Yang Ming Chiao Tung University (NYCU), Taiwan
// Instructor: Sai-Keung Wong
// Date: 2022/10/05
//
#include <iostream>
#include "SystemParameter.h"

using namespace std;



SystemParameter* SystemParameter::_instance = new SystemParameter;

SystemParameter::SystemParameter() 
{
	radius = 130;
	maxSpeed = 1.5;
	acceleration = 0.15;
	maxNumParticleSystems = 60;
	stopGameMaxTime = 0.5;
	maxSimulationTimeStepSize = 1 / 30.0; // (sec)
	charMaxExperiencePoints = 20;
}
