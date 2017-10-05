#pragma once
#include"Geometry.h"
class Cube_prim :public Geometry_Manager
{
public:
	Cube_prim();
	Cube_prim(const Cube_prim& cube_tmp);
	~Cube_prim();
	void Create_Cube_Prim(std::vector<float> vert, std::vector<uint> index, std::vector<float> text);
public:
	math::AABB* geometry_cube;
};
