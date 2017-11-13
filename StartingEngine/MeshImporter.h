#pragma once
#include"Globals.h"
#include"ResourceMesh.h"
#include"ModuleAssimp.h"
#include<vector>


class Material;
class GameObject;
class MeshImporter
{
public:
	Material* AddTextureResourceToGO(Resource_Mesh_Base* n_temp_mesh, GameObject* child_gameobj, const char* final_path_mesh, const char * path_fbx_gen);
	void AddMeshResourceToGO(Resource_Mesh_Base* n_temp_mesh, GameObject* child_gameobj, int uuid_mesh, Material* mat, const char * path, const char * path_fbx_gen);
	void CalculateMeshAssimp_Values(const aiScene* scene, const char* path, std::string *new_name=nullptr);
	void ImportMesh(Resource_Mesh_Base* temp_m, const char* path);
	bool LoadMesh(const char* path, const char * path_fbx_gen , GameObject* parent=nullptr);
	void LoadRecursive(char ** cursor, GameObject* Parent, const char* path, const char * path_fbx_gen, GameObject* Parent_Gen_World=nullptr);
	GameObject* LoadMesh_variables(char ** cursor, GameObject* parent, int* num_childs, const char* path,const char * path_fbx_gen, GameObject* Parent_Gen_World = nullptr);
	uint RecursiveSizeScene(aiNode* node, const aiScene* scene);
	uint GetSceneSize(const aiScene* scene);
	void Recursive_childs_general_bin(char ** cursor, const aiScene* scene, aiNode* node, const char* path);
	void Resource_Assimp_Creation(const aiScene* scene, const char* path, const char* name, int i);
	void General_Bin_Mesh(char ** cursor, const aiScene* scene, aiNode* node, const char* path);
	Resource_Mesh_Base * Create_Base_Geometry(const char* path, const char* name, const char* final_path, GameObject* Parent_Gen_World = nullptr);
	bool Load_Texture_Scenes(const aiScene* scene);
	
	MeshImporter();
	~MeshImporter();
	int change_nameimporter = 0;
	};

