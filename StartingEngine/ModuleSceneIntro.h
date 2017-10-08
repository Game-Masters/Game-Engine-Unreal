#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Geometry.h"
#include"j1PerfTimer.h"
#include"Imgui/imgui.h"
#include "Light.h"
#include<vector>
#include"MathGeoLib\MathGeoLib.h"
#include"MathGeoLib\MathBuildConfig.h"
#include "../StartingEngine/Glew/include/glew.h"
#include "SDL\include\SDL_opengl.h"
#include"Texture_Engine.h"

//#include"Geometry.h"
#include"Cube_prim.h"
#define MAX_SNAKE 2
#define MAX_CUBE 50
#define MAX_LIGHTS 8

struct PhysBody3D;
struct PhysMotor3D;
struct btHingeConstraint;
enum guy {
	bad_guy,
	good_guy,
	unknown
};
class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);
	update_status PostUpdate(float dt);
	bool Gui_Engine_Modules(float dt);
	bool CleanUp();
	Sphere *n_sphere_one=nullptr;
	Sphere *n_sphere_two=nullptr;
	//
	Light lights[MAX_LIGHTS];
	Sphere* sphere;
	std::vector<vec> vect_v;
	std::vector<vec> norm_v;


	std::vector<unsigned int> index;
	std::vector<unsigned int> planeindex;
	GLuint my_indices = 0;
	GLuint plane_indices = 0;
	std::vector<GLfloat> cube_vert;
	std::vector<GLfloat> plane_vert;
	GLuint my_vertex;
	GLuint plane_vertex;
	GLuint vertexbuffer;
	GLuint normalbuffer;
	GLuint texturebuffer;
	Sphere *n_sphere_o = nullptr;
	std::vector<vec> vec1;
	std::vector<vec> vec2;
	GLuint vertexbuffer1;

	std::vector<GLfloat> g_vertex_buffer_data;
	//

	
	vec* temp;

	std::vector<unsigned int> texture_index;
	std::vector<GLfloat> texture_coord;


public:
	//GLuint ImageName;
	//GLubyte checkImage[256][256][4];
	PhysBody3D*PlainGame_Body;
	Cube_prim * cube_test=nullptr;
	Cube_prim * plane_test = nullptr;
	Geometry_Manager *m;
	Texture_Engine *world_texture;

};
