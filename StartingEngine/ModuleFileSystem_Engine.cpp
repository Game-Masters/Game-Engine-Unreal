#include "ModuleFileSystem_Engine.h"
#include<filesystem>



bool ModuleFileSystem_Engine::Start()
{

	std::experimental::filesystem::create_directory("Assets");


	return true;
}

bool ModuleFileSystem_Engine::CleanUp()
{
	return false;
}

bool ModuleFileSystem_Engine::LoadFile(const char * path, const char ** buffer)
{
	return false;
}

ModuleFileSystem_Engine::ModuleFileSystem_Engine()
{
}


ModuleFileSystem_Engine::~ModuleFileSystem_Engine()
{
}
