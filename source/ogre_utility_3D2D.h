//
// 3D Game Programming
// NYCU
// Instructor: Sai-Keung Wong
//
// Date: 30 Oct. 2022.
//
#ifndef __OGRE_UTILITY_H__
#define __OGRE_UTILITY_H__

#include "Ogre.h"
#include "OgreStringConverter.h"
#include "OgreException.h"

using namespace Ogre;

extern void mapWorldPositionToViewportCoordinates(const Camera *camera, const Vector3 &world_pos, Vector2 &viewport_coord);
#endif