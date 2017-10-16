#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "Light.h"
#include "../StartingEngine/Glew/include/glew.h"
#include "SDL\include\SDL_opengl.h"

#define MAX_LIGHTS 8

class ModuleRenderer3D : public Module
{
public:
	ModuleRenderer3D(bool start_enabled = true);
	~ModuleRenderer3D();

	bool Init();
	update_status PreUpdate(float dt);
	update_status PostUpdate(float dt);
	bool Start();
	bool CleanUp();
	bool Gui_Engine_Modules(float dt);
	void OnResize(int width, int height);
	bool LoadConfig(JSON_Object* node);
	bool SaveConfig(JSON_Object* node);

	//-----------
	/*
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
	Sphere *n_sphere_o = nullptr;
	std::vector<vec> vec1;
	std::vector<vec> vec2;
	GLuint vertexbuffer1;

	std::vector<GLfloat> g_vertex_buffer_data;
	*/

public:
	
	Light lights[MAX_LIGHTS];
	SDL_GLContext context;
	mat3x3 NormalMatrix;
	mat4x4 ModelMatrix, ViewMatrix, ProjectionMatrix;
	bool wireframe = false;
	bool points = false;
	bool cullface = false;
	bool mat = false;
	bool color = false;
	bool debugnormals = false;
	float* Window_Color = nullptr;
};