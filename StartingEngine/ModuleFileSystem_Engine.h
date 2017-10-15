#pragma once
#include "Module.h"
#include <experimental/filesystem> // C++-standard header file name  
#include <filesystem> // Microsoft-specific implementation header file name  
using namespace std::experimental::filesystem::v1;

class ModuleFileSystem_Engine :
	public Module
{
public:





	ModuleFileSystem_Engine();
	~ModuleFileSystem_Engine();
};

