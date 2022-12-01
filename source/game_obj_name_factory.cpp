//
// 3D Game Programming
// NYCU
// Instructor: Sai-Keung Wong
//
// Date: 30 Oct. 2022.
//
#include "game_obj_name_factory.h"

//initialize static member variables
Ogre::String GAME_OBJ_NAME_FACTORY::global_name_prefix = "_ton_";
int GAME_OBJ_NAME_FACTORY::global_name_counter = 0;