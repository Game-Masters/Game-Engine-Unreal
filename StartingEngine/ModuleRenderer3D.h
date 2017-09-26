#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "Light.h"
#include "../StartingEngine/Glew/include/glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include <shellapi.h>
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
	bool CleanUp();
	bool Gui_Engine_Modules(float dt);
	void OnResize(int width, int height);

public:
	
	Light lights[MAX_LIGHTS];
	SDL_GLContext context;
	mat3x3 NormalMatrix;
	mat4x4 ModelMatrix, ViewMatrix, ProjectionMatrix;
	bool wireframe = false;
	bool points = false;
	bool cullface = false;
};