#pragma once
#include"Application.h"
#include"Globals.h"
#include <vector>
#include "Component.h"

class Material :
	public Component
{
protected:
	std::string path_texture_exported;
	std::string path_texture;
public:
	geometry_base_creating* texture_v = nullptr;
	int UUID_mat;
	Material(int UUID, GameObject* parent);
	void Update();
	~Material();
	//material_base_geometry* GetMaterialVec();
	const char* GetPathMaterial() const;
	virtual void Save(JSON_Object *root_object_scene);
	virtual void Load(JSON_Object *root_object_scene);
	void CleanUp();
};

