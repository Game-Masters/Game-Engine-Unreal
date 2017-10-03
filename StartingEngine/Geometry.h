
#pragma once
#include"Globals.h"
#include"Color.h"
#include <vector>
#include "../StartingEngine/Glew/include/glew.h"
#include "SDL\include\SDL_opengl.h"
#include"MathGeoLib\MathGeoLib.h"
#include"MathGeoLib\MathBuildConfig.h"



struct geometry_base {
	uint id_vertices = 0; // id in VRAM
	uint num_indices = 0;
	std::vector<unsigned int> indices;
	uint id_indices = 0; // id in VRAM
	uint num_vertices = 0;
	std::vector<float> vertices;
	~geometry_base() {
		indices.clear();
		vertices.clear();
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
	Primitive_Cylinder
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
