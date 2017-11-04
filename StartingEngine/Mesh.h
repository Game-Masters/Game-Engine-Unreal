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
	AABB BoundBox;
	uint id_aabb=0;
	float* vertex_aabb;
	uint id_index_aabb=0;
	uint* index_aabb;
	uint num_tris = 0;
	std::string name;
	uint Know_if_m_have[4]{ 0,0,0,0 };
	geometry_base_creating() {

	}

	~geometry_base_creating() {
		glDeleteBuffers(1, &id_vertices);
		glDeleteBuffers(1, &id_indices);
		glDeleteBuffers(1, &id_colors);
		glDeleteBuffers(1, &id_texture);
		glDeleteBuffers(1, &id_image_devil);

		/*delete[] vertex_aabb;
		delete[] index_aabb;*/
		delete[] indices;
		delete[] vertices;
		delete[] colors;
		delete[] textures_coord;
		delete[] normals;
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
	geometry_base_creating* mesh_v;
public:
	float4x4 ParentHasTransform(float3 &position, float3 &scaling, Quat &rotation);

	void Update();
	Mesh(GameObject* parent, geometry_base_creating* vec_mesh, const char* path, Material* m_text=nullptr);
	~Mesh();
	PrimitiveTypes_Mesh    GetType()const;
	void CleanUp();
	const char* GetGeometryPath();
	geometry_base_creating* GetGeometryBaseMesh();
	virtual void Save(JSON_Object *root_object_scene);
	virtual void Load(JSON_Object *root_object_scene);

};

