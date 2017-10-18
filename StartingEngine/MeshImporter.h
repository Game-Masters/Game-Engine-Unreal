#pragma once
#include"Globals.h"
#include<vector>
class MeshImporter
{
public:
	void ImportMesh(const char* name_mesh,std::vector<float>vertex, std::vector<uint> index, std::vector<float>texture_coord, std::vector<float> normals);
	MeshImporter();
	~MeshImporter();
	};

