#pragma once
#include"Application.h"
#include"Globals.h"
#include <vector>
#include "Component.h"

struct material_base_geometry {
	uint num_textcoord = 0;
	uint id_texture = 0;
	uint id_image_devil = 0;
	uint num_vertices = 0;
	uint* texture_w_h=nullptr;
	float* textures_coord = nullptr;

	~material_base_geometry() {
		glDeleteBuffers(1, &id_texture);
		glDeleteBuffers(1, &id_image_devil);
	}
};


class Material :
	public Component
{
protected:
	std::string path_texture;

public:
	geometry_base_creating* texture_v = nullptr;
	int UUID_mat;
	Material(int UUID, GameObject* parent);
	void Update();
	~Material();
	//material_base_geometry* GetMaterialVec();
	const char* GetPathMaterial();
	virtual void Save(JSON_Object *root_object_scene);
	virtual void Load(JSON_Object *root_object_scene);
	void CleanUp();
};

