#include"Cube_prim.h"

Cube_prim::Cube_prim() : Geometry_Mesh(PrimitiveTypes::Primitive_Cube)
{
	geometry_cube = new math::AABB();
}

Cube_prim::Cube_prim(const Cube_prim & cube_tmp) : Geometry_Mesh(cube_tmp)
{
	geometry_cube = new math::AABB();
}


Cube_prim::~Cube_prim()
{
}

void Cube_prim::Create_Cube_Prim(std::vector<float> vert, std::vector<uint> index, std::vector<float> text)
{

	mesh.num_vertices = vert.size()/3;

	mesh.num_indices = index.size();;

	mesh.num_textcoord = text.size()/2;


	mesh.vertices = new float[mesh.num_vertices * 3];
	mesh.indices = new uint[mesh.num_indices];
	memcpy(mesh.vertices, &vert[0], sizeof(float) * mesh.num_vertices * 3);
	for (uint i = 0; i < mesh.num_indices; ++i)
	{
		memcpy(&mesh.indices[i], &index[i], sizeof(uint));
	}

	//if (vert[0]!=NULL) {
		mesh.textures_coord = new float[mesh.num_textcoord * 2];
		memcpy(mesh.textures_coord, &text[0], sizeof(float) * mesh.num_textcoord * 2);
	//}

}
