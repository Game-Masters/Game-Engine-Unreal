#include"Cube_prim.h"

Cube_prim::Cube_prim() : Geometry_Manager(PrimitiveTypes::Primitive_Cube)
{
	geometry_cube = new math::AABB();
}

Cube_prim::Cube_prim(Cube_prim & cube_tmp) : Geometry_Manager(cube_tmp)
{
	geometry_cube = new math::AABB();
}


Cube_prim::~Cube_prim()
{
}
