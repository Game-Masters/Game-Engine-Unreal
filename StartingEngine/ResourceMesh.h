#pragma once
#include "ModuleAssimp.h"
#include"ModuleResources.h"


struct Resource_Mesh_Base {
	uint id_vertices = 0; // id in VRAM
	uint num_indices = 0;
	uint* indices;
	uint id_indices = 0; // id in VRAM
	uint num_vertices = 0;
	float* vertices;
	uint id_normales = 0;
	float* normals = nullptr;
	uint id_colors = 0;
	float* colors = nullptr;
	uint num_textcoord = 0;
	uint id_texture = 0;
	uint id_image_devil = 0;
	float* textures_coord = nullptr;
	float3 translation;
	float3 scaling;
	Quat rotation;
	std::string texture_str;
	AABB BoundBox;
	uint id_aabb = 0;
	float* vertex_aabb = nullptr;
	uint id_index_aabb = 0;
	uint* index_aabb = nullptr;
	uint num_tris = 0;
	std::string name;
	uint Know_if_m_have[4]{ 0,0,0,0 };
	Resource_Mesh_Base() {

	}

	~Resource_Mesh_Base() {
		glDeleteBuffers(1, &id_vertices);
		glDeleteBuffers(1, &id_indices);
		glDeleteBuffers(1, &id_colors);
		glDeleteBuffers(1, &id_texture);
		glDeleteBuffers(1, &id_image_devil);
		delete[] vertex_aabb;
		delete[] index_aabb;
		delete[] indices;
		delete[] vertices;
		delete[] colors;
		delete[] textures_coord;
		delete[] normals;
	}
};

class ResourceMesh :
	public Resource
{
public:
	ResourceMesh();
	~ResourceMesh();
	ResourceMesh(int id);

	bool LoadToMemory();
	void LoadMeshBase();
	//void Save(Config& config) const;
	//void Load(const Config& config);

public:
	LCG uid_rm;
	Resource_Mesh_Base *Res_Mesh_Base;
	AABB Copy_aabb;
	

};

