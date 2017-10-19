#pragma once
#include"Globals.h"
#include"ModuleAssimp.h"
#include<vector>

class MeshImporter
{
public:
	void ImportMesh(const aiScene* scene, const char* path);
	bool LoadMesh(const char* path);
	void LoadMesh_variables(char* cursor, uint num_meshes, uint size_mesh);
	MeshImporter();
	~MeshImporter();
	};

