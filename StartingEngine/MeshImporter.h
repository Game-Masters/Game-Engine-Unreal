#pragma once
#include"Globals.h"
#include"ModuleAssimp.h"
#include<vector>
class GameObject;

class MeshImporter
{
public:
	void CalculateMeshAssimp_Values(const aiScene* scene, const char* path);
	void ImportMesh(geometry_base_creating* temp_m, const char* path);
	bool LoadMesh(const char* path);
	void LoadRecursive(char ** cursor, GameObject* Parent, const char* path);
	GameObject* LoadMesh_variables(char ** cursor, GameObject* parent, int* num_childs, const char* path);
	uint RecursiveSizeScene(aiNode* node, const aiScene* scene);
	uint GetSceneSize(const aiScene* scene);
	void Recursive_childs_general_bin(char ** cursor, const aiScene* scene, aiNode* node, const char* path);
	void Load_Mesh_Childs_Recursive(char ** cursor, GameObject* Parent);
	void General_Bin_Mesh(char ** cursor, const aiScene* scene, aiNode* node, const char* path);
	geometry_base_creating * Create_Base_Geometry(const char* path, const char* name, const char* final_path);
	bool Load_Texture_Scenes(const aiScene* scene);
	MeshImporter();
	~MeshImporter();
	int change_nameimporter = 0;
	};

