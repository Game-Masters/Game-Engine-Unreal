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
struct geometry_base_creating {
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

	geometry_base_creating() {

	}

	~geometry_base_creating() {
		delete[] indices;
		delete[] vertices;
	}
};

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
	Material* texture_mesh;
	std::string path_fbx;
	PrimitiveTypes_Mesh    type = PrimitiveTypes_Mesh::Primitive_Undef_Mesh;
	std::vector<geometry_base_creating*> mesh_v;
public:
	void Update();
	Mesh(GameObject* parent, const char* str, Material* m_text=nullptr);
	~Mesh();
	PrimitiveTypes_Mesh    GetType()const;
	const char* GetGeometryPath();
};

