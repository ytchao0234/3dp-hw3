//
// 3D Game Programming
// National Yang Ming Chiao Tung University (NYCU), Taiwan
// Instructor: Sai-Keung Wong
// Date: 2022/10/05
//
//
// The functions will be invoked at the runtime stage.
//
// Example: 
// Handle mouse events to control the camera.
// Handle mouse events to obtain the camera information.
// Handle mouse events to activate the objects/items, e.g., spheres, robots, etc
// And others
// 
// A mouse handler handles simple tasks, 
// such as setting the states of game objects. 
//
//

#include "TutorialApplication.h"
#include "BasicTools.h"

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <math.h>

//
// using namespace Ogre;
// Enable to use the functions/structures defined in the namespace Ogre.
//
using namespace Ogre;


bool BasicTutorial_00::mouseMoved(const OIS::MouseEvent& arg)
{
	//Ogre::String ss = Ogre::StringConverter::toString(arg.state.Z.rel);
	//Ogre::LogManager::getSingletonPtr()->logMessage(ss);

	bool flg = BaseApplication::mouseMoved(arg);
	mMainChar->updateViewDirection();
	return flg;
}
/*
bool BasicTutorial_00::mouseMoved(const OIS::MouseEvent& arg)
{
	Ogre::String ss = Ogre::StringConverter::toString(arg.state.Z.rel);

	Ogre::LogManager::getSingletonPtr()->logMessage(ss);

	if (arg.state.Z.rel != 0) {

		Vector3 p = mCamera->getPosition();

		Real dy = arg.state.Z.rel / 20.0;
		p.y -= dy;
		Real dz = arg.state.Z.rel / 20.0;
		p.z -= dz;
		mCamera->setPosition(p);

	}

	return BaseApplication::mouseMoved(arg);
}
*/

bool BasicTutorial_00::mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id)
{
	return BaseApplication::mousePressed(arg, id);
}
bool BasicTutorial_00::mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id)
{
	return BaseApplication::mouseReleased(arg, id);
}