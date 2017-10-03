#pragma once
#ifndef __ModuleAssimp_H__
#define __ModuleAssimp_H__

#include "Module.h"
#include "SDL/include/SDL.h"
#include"Geometry.h"

class Application;

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
	void ImportGeometry(char* fbx);


public:

	Geometry_Manager* m;
	std::vector<Geometry_Manager*> meshes_vec;
	GLuint * paco;
};

#endif // __ModuleAssimp_H__