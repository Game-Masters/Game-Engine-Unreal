
#pragma once
#include"Globals.h"

#include"Color.h"
#include <vector>
#include "../StartingEngine/Glew/include/glew.h"
#include "SDL\include\SDL_opengl.h"
#include"MathGeoLib\MathGeoLib.h"
#include"MathGeoLib\MathBuildConfig.h"
#include "../StartingEngine/Assimp/include/assimp/cimport.h"
#include "../StartingEngine/Assimp/include/assimp/scene.h"
#include "../StartingEngine/Assimp/include/assimp/postprocess.h"
#include "../StartingEngine/Assimp/include/assimp/cfileio.h"



struct geometry_base {
	uint id_vertices = 0; // id in VRAM
	uint num_indices = 0;
	uint* indices;
	uint id_indices = 0; // id in VRAM
	uint num_vertices = 0;
	float* vertices;
	uint id_normales = 0;
	float* normals=nullptr;
	uint id_colors = 0;
	float* colors = nullptr;
	uint num_textcoord = 0;
	uint id_texture = 0;
	uint id_image_devil = 0;
	float* textures_coord = nullptr;
	char* texture_str;
	

	aiVector3D translation;
	aiVector3D scaling;
	aiQuaternion rotation;

	~geometry_base() {
		delete[] indices;
		delete[] vertices;
	}
};

enum PrimitiveTypes
{
	Primitive_Undef,
	Primitive_Point,
	Primitive_Line,
	Primitive_Plane,
	Primitive_Cube,
	Primitive_Sphere,
	Primitive_Cylinder,
	Primitive_Mesh
};

class Geometry_Manager
{

public:

	Geometry_Manager(PrimitiveTypes _type);
	Geometry_Manager(const Geometry_Manager& _cpy);
	virtual ~Geometry_Manager();

public:

	virtual void    Initialize();
	void            Draw();

	//protected:
	GLuint ImageName = 0;
	Color            color = { 255,255,255,255 };
	PrimitiveTypes    type = Primitive_Undef;
	uint            geometry_div = 0;
	geometry_base        mesh;

public:

	//Set Methods -----------
	void SetColor(const Color& oth_color);

	//void SetType(PrimitiveTypes oth_type);
	//    void SetDivisions(uint divis);

	//Get Methods -----------
	Color            GetColor()const;
	PrimitiveTypes    GetType()const;
};
