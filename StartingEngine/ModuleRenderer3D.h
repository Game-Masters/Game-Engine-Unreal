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
	bool SaveConfig(JSON_Object* node)const;
	void Render_3D(Mesh* m , int uuid, Material* texture_mesh= nullptr);


public:
	uint id_checkImage = 0;
	unsigned char checkImage[64][32][4];
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

	GLint shader_next_id = 0;
	GLint shader_next_id2 = 0;
	GLint shader_next_id3 = 0;
	GLint shader_next_id4 = 0;
	GLint modelLoc = 0;
	GLint testLoc = 0;
	GLuint alphatexture=0;
	GLuint alphatexture2 = 0;
	GLuint watertexture = 0;
	GLuint foam = 0;
};