#pragma once
#include"Application.h"
#include"Globals.h"
#include <vector>
#include "../StartingEngine/Glew/include/glew.h"
#include "SDL\include\SDL_opengl.h"
#include"MathGeoLib\MathGeoLib.h"
#include"MathGeoLib\MathBuildConfig.h"
#include<string>
#include"Component.h"

class Material;


enum PrimitiveTypes_Mesh
{
	Primitive_Undef_Mesh,
	Primitive_Point_Mesh,
	Primitive_Line_Mesh,
	Primitive_Plane_Mesh,
	Primitive_Cube_Mesh,
	Primitive_Sphere_Mesh,
	Primitive_Cylinder_Mesh,
	Primitive_Mesh_n
};

class Mesh :
	public Component
{

private:
	Material* texture_mesh=nullptr;
	std::string path_fbx;
	std::string path_fbx_mesh;
	PrimitiveTypes_Mesh    type = PrimitiveTypes_Mesh::Primitive_Undef_Mesh;
	std::string general_fb_path;

public:
	int uuid_mesh;
	Resource* mesh_r= nullptr;
	float4x4 ParentHasTransform(float3 &position, float3 &scaling, Quat &rotation);
	AABB Copy_aabb_using;
	void Update();
	void PreUpdate();
	Mesh(GameObject* parent, int uuid, const char* path=nullptr, Material* m_text=nullptr);
	~Mesh();
	PrimitiveTypes_Mesh    GetType()const;
	void CleanUp();
	const char* GetGeometryPath() const;
	const Resource_Mesh_Base& GetGeometryBaseMesh() const;
	const AABB GetAABB()const;
	void SetMaterial(Material*);
	const Material& GetMaterial()const;
	virtual void Save(JSON_Object *root_object_scene);
	virtual void Load(JSON_Object *root_object_scene);
	void Update_AABB();
};

