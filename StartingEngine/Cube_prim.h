#pragma once
#include"Geometry.h"
class Cube_prim :public Geometry_Manager
{
public:
	Cube_prim();
	Cube_prim(Cube_prim& cube_tmp);
	~Cube_prim();

public:
	math::AABB* geometry_cube;
};
