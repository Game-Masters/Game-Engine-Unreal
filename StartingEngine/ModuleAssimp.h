#pragma once
#ifndef __ModuleAssimp_H__
#define __ModuleAssimp_H__

#include "Module.h"
#include "SDL/include/SDL.h"
#include"Geometry.h"
#include"Devil\include\ilut.h"

#pragma comment (lib, "../StartingEngine/Devil/libx86/DevIL.lib")
#pragma comment (lib, "../StartingEngine/Devil/libx86/ILU.lib")
#pragma comment (lib, "../StartingEngine/Devil/libx86/ILUT.lib")


class Application;
struct geometry_base_creating;
struct material_base_geometry;
class ModuleAssimp : public Module
{
public:

	ModuleAssimp(bool start_enabled = true);

	// Destructor
	virtual ~ModuleAssimp();

	bool Start();
	update_status Update(float dt);
	update_status PreUpdate(float dt);
	update_status PostUpdate(float dt);
	bool Gui_Engine_Modules(float dt);
	bool CleanUp();

	void ImportGeometry(const char* fbx, std::string *str);


	aiNode* Calc_AllGeometry_Childs(aiNode* Parent_node, uint search_mesh);
	float2 LoadImage_devil(const char* theFileName, GLuint *buff);
	bool loadTextureFromPixels32(GLuint * id_pixels, GLuint width, GLuint height, GLuint *buff);

	bool IsTexture(const char *path);
public:
	//GLuint *Lenna_texture = 0;

	//std::vector<Geometry_Mesh*> meshes_vec;

	bool loaded = false;

	bool IsTexture(char *path);
public:
	//GLuint *Lenna_texture = 0;
	geometry_base_creating* m;
	material_base_geometry* mat_geom;
	//std::vector<Geometry_Manager*> meshes_vec;
	GLuint * paco;


};

#endif // __ModuleAssimp_H__