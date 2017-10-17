#pragma once
#include "Module.h"


class ModuleFileSystem_Engine :
	public Module
{
public:
	
	bool Start();
	bool CleanUp();
	void CreateDir(const char* dir);
	bool LoadFile(const char* path, char** buffer);
	bool SaveFile(const char* path, char** buffer, uint size);
	ModuleFileSystem_Engine();
	~ModuleFileSystem_Engine();
};

