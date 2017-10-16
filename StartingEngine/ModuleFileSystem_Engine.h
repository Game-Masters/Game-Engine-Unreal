#pragma once
#include "Module.h"


class ModuleFileSystem_Engine :
	public Module
{
public:
	
	bool Start();
	bool CleanUp();
	void CreateDir(const char* dir);

	ModuleFileSystem_Engine();
	~ModuleFileSystem_Engine();
};

