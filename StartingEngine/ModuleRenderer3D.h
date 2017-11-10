#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "Light.h"
#include "../StartingEngine/Glew/include/glew.h"
#include "SDL\include\SDL_opengl.h"

#define MAX_LIGHTS 8

class Material;

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
	void Render_3D(Mesh* m , int uuid, Material* texture_mesh= nullptr);



public:
	
	Light lights[MAX_LIGHTS];
	SDL_GLContext context;
	//mat3x3 NormalMatrix;
	float4x4 ProjectionMatrix;
	bool wireframe = false;
	bool points = false;
	bool cullface = false;
	bool mat = false;
	bool color = false;
	bool debugnormals = false;
	float* Window_Color = nullptr;
};