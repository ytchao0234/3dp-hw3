//
// 3D Game Programming
// NYCU
// Instructor: Sai-Keung Wong
//
// Date: 30 Oct. 2022.
//
#include "ogre_utility_3D2D.h"

void mapWorldPositionToViewportCoordinates(const Camera *camera, const Vector3 &world_pos, Vector2 &viewport_coord)
{
	Matrix4 prot_mat = camera->getProjectionMatrix();
	Matrix4 view_mat = camera->getViewMatrix(true);
	Matrix4 mat = prot_mat*view_mat;
	Vector3 obj_in_cam_pos;
	Vector3 p = mat*world_pos;
	viewport_coord.x = (p.x - (-1))/2.0;	
	viewport_coord.y = (1 - p.y)/2;
}