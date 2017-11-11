#include "ResourceMesh.h"
#include"ResourceMesh.h"


ResourceMesh::ResourceMesh():Resource(uid_rm.Int(), Resources_Type::mesh)
{
}


ResourceMesh::~ResourceMesh()
{
}

ResourceMesh::ResourceMesh(int id) : Resource(id, Resources_Type::mesh)
{
}

bool ResourceMesh::LoadToMemory()
{
	this->uid;
	if (loaded == 0) {
		loaded++;
		LoadMeshBase();
		return true;
	}
	loaded++;
	return false;
}

void ResourceMesh::LoadMeshBase()
{

	if (Res_Mesh_Base->vertices != nullptr && Res_Mesh_Base->indices != nullptr) {
		glGenBuffers(1, (GLuint*)&(Res_Mesh_Base->id_vertices));
		glBindBuffer(GL_ARRAY_BUFFER, Res_Mesh_Base->id_vertices);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) *Res_Mesh_Base->num_vertices * 3, &Res_Mesh_Base->vertices[0], GL_STATIC_DRAW);

		glGenBuffers(1, (GLuint*)&(Res_Mesh_Base->id_texture));
		glBindBuffer(GL_ARRAY_BUFFER, Res_Mesh_Base->id_texture);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) *Res_Mesh_Base->num_vertices * 2, &Res_Mesh_Base->textures_coord[0], GL_STATIC_DRAW);

		// Buffer for indices
		glGenBuffers(1, (GLuint*)&(Res_Mesh_Base->id_indices));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Res_Mesh_Base->id_indices);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * Res_Mesh_Base->num_indices, &Res_Mesh_Base->indices[0], GL_STATIC_DRAW);

	}
	Copy_aabb = Res_Mesh_Base->BoundBox;

	this->Res_Mesh_Base->vertex_aabb = new float[8 * 3];
	this->Res_Mesh_Base->index_aabb = new uint[8 * 3];

	float vertex_Aabb[] = {
		Copy_aabb.CornerPoint(0).x,Copy_aabb.CornerPoint(0).y,Copy_aabb.CornerPoint(0).z,
		Copy_aabb.CornerPoint(1).x,Copy_aabb.CornerPoint(1).y,Copy_aabb.CornerPoint(1).z,
		Copy_aabb.CornerPoint(2).x,Copy_aabb.CornerPoint(2).y,Copy_aabb.CornerPoint(2).z,
		Copy_aabb.CornerPoint(3).x,Copy_aabb.CornerPoint(3).y,Copy_aabb.CornerPoint(3).z,
		Copy_aabb.CornerPoint(4).x,Copy_aabb.CornerPoint(4).y,Copy_aabb.CornerPoint(4).z,
		Copy_aabb.CornerPoint(5).x,Copy_aabb.CornerPoint(5).y,Copy_aabb.CornerPoint(5).z,
		Copy_aabb.CornerPoint(6).x,Copy_aabb.CornerPoint(6).y,Copy_aabb.CornerPoint(6).z,
		Copy_aabb.CornerPoint(7).x,Copy_aabb.CornerPoint(7).y,Copy_aabb.CornerPoint(7).z
	};
	memcpy(Res_Mesh_Base->vertex_aabb, vertex_Aabb, sizeof(float) * 24);

	uint indices[] =
	{
		0,2,
		0,4,
		0,1,
		7,6,
		7,3,
		7,5,
		5,1,
		5,4,
		2,3,
		2,6,
		6,4,
		3,1
	};
	memcpy(this->Res_Mesh_Base->index_aabb, indices, sizeof(uint) * 24);

	glGenBuffers(1, (GLuint*)&(Res_Mesh_Base->id_aabb));
	glBindBuffer(GL_ARRAY_BUFFER, Res_Mesh_Base->id_aabb);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8 * 3, &Res_Mesh_Base->vertex_aabb[0], GL_STATIC_DRAW);

	glGenBuffers(1, (GLuint*)&(Res_Mesh_Base->id_index_aabb));
	glBindBuffer(GL_ARRAY_BUFFER, Res_Mesh_Base->id_index_aabb);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uint) * 8 * 3, &Res_Mesh_Base->index_aabb[0], GL_STATIC_DRAW);


}
