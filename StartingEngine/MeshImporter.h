#pragma once
#include"Globals.h"
#include"ModuleAssimp.h"
#include<vector>

class MeshImporter
{
public:
	void CalculateMeshAssimp_Values(const aiScene* scene, const char* path);
	void ImportMesh(geometry_base_creating* temp_m, const char* path);
	bool LoadMesh(const char* path);
	void LoadMesh_variables(char* cursor, geometry_base_creating* n_temp_mesh, uint size_mesh);
	uint RecursiveSizeScene(aiNode* node, const aiScene* scene);
	uint GetSceneSize(const aiScene* scene);
	MeshImporter();
	~MeshImporter();
	};

