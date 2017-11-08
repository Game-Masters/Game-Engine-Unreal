#pragma once
#include"Globals.h"
#include<map>
class MaterialImporter
{
public:
	MaterialImporter();
	~MaterialImporter();
	std::multimap<int, std::string> Mat_Map;
public:
	void ImportMaterial(const char* path, std::string * new_path=nullptr);
	
};

