//
// 3D Game Programming
// NYCU
// Instructor: Sai-Keung Wong
//
// Date: 30 Oct. 2022.
//
#ifndef __GAME_OBJ_NAME_FRACTORY_H__
#define __GAME_OBJ_NAME_FRACTORY_H__
#include "ogre.h"

class GAME_OBJ_NAME_FACTORY {
protected:
	static Ogre::String global_name_prefix;
	static int global_name_counter;
	static void generateGlobalObjName(Ogre::String &name) {
		global_name_counter++;
		name = global_name_prefix + Ogre::StringConverter::toString(static_cast<int>(global_name_counter));
	}
public:
	GAME_OBJ_NAME_FACTORY(){}
};

#endif