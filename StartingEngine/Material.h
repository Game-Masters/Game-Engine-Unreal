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
};


class Material :
	public Component
{
protected:
	std::string path_texture;

	material_base_geometry* texture_v=nullptr;


public:
	Material(const char* path_text, const char* fbx, GameObject* parent);
	void Update();
	~Material();
	material_base_geometry* GetMaterialVec();
	const char* GetPathMaterial();
};

