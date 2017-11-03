#include "MeshImporter.h"
#include"Application.h"
#include"ModuleFileSystem_Engine.h"
#include"GameObject.h"

#define MAXRANGCHAR 70


void MeshImporter::CalculateMeshAssimp_Values(const aiScene* scene, const char* path)
{

	uint size_buffer_gen = GetSceneSize(scene);
	char* buffer_total_gen = new char[size_buffer_gen];
	char* cursor = buffer_total_gen;

	Recursive_childs_general_bin(&cursor, scene, scene->mRootNode, path);

	std::string path_n = path;
	std::string path_new_format;
	App->fs_e->ChangeFormat_File(path_n.c_str(), "ric", &path_new_format, App->fs_e->Mesh_Engine);
	App->fs_e->SaveFile(path_new_format.data(), buffer_total_gen, size_buffer_gen);
	RELEASE_ARRAY(buffer_total_gen);


	geometry_base_creating* m = nullptr;
	//std::vector<geometry_base_creating*> mesh_v;
	for (int i = 0; i < scene->mNumMeshes; i++) {

		LOG("Mesh imported %i----------------", i);
		m = new geometry_base_creating();
		std::string str_parent = path;
		size_t temp_uint = str_parent.rfind("\\")+1;
		size_t temp_uint_2 = str_parent.rfind(".");
		uint diff = temp_uint_2 - temp_uint;
		std::string str_parent_substracted = str_parent.substr(temp_uint, diff);
		std::string str_n_i = std::to_string(i);
		m->name = str_parent_substracted+ " " + str_n_i;
		m->num_vertices = scene->mMeshes[i]->mNumVertices;
		m->vertices = new float[m->num_vertices * 3];
		LOG("New mesh with %d vertices", m->num_vertices);
		memcpy(m->vertices, scene->mMeshes[i]->mVertices, sizeof(float) * m->num_vertices * 3);
		if (m->vertices == nullptr) {
			LOG("The new mesh has failed trying to import the vertices");
		}
		else {
			m->Know_if_m_have[0] = 1;
			LOG("The new mesh has succed trying to import the vertices");
		}
		//Generate bounding bax
		
		LOG("A BoundBox has been added to the mesh", m->num_vertices);
		// copy faces
		if (scene->mMeshes[i]->HasFaces())
		{
			m->num_tris = scene->mMeshes[i]->mNumFaces;
			m->num_indices = scene->mMeshes[i]->mNumFaces *3;
			LOG("The mesh has %d triangles", m->num_tris);
			m->indices = new uint[scene->mMeshes[i]->mNumFaces * 3]; // assume each face is a triangle
			LOG("The mesh has %d indices", m->num_indices);

			for (uint k = 0; k < scene->mMeshes[i]->mNumFaces; ++k)
			{
				if (scene->mMeshes[i]->mFaces[k].mNumIndices != 3) {
					LOG("WARNING, geometry face with != 3 indices!");
				}
				else {
					memcpy(&m->indices[k * 3], scene->mMeshes[i]->mFaces[k].mIndices, 3 * sizeof(uint));
				}
			}
		}
		if (m->indices == nullptr) {
			LOG("The new mesh has failed trying to import the indices");
		}
		else {
			m->Know_if_m_have[1] = 1;
			LOG("The new mesh has succed trying to import the indices");
		}

		if (scene->mMeshes[i]->HasNormals()) {

			LOG("The new mesh has normals");
			m->normals = new float[scene->mMeshes[i]->mNumVertices * 3];
			memcpy(m->normals, scene->mMeshes[i]->mNormals, sizeof(float) * m->num_vertices * 3);
			if (m->normals == nullptr) {
				LOG("The new mesh has failed trying to import the normals");
			}
			else {
				m->Know_if_m_have[2] = 1;
				LOG("The new mesh has succed trying to import the normals");
			}
		}
		else {
			LOG("The new mesh has not normals so the engine cannot import them");
		}

		if (scene->mMeshes[i]->HasTextureCoords(0))
		{
			m->Know_if_m_have[3] = 1;
			m->textures_coord = new float[scene->mMeshes[i]->mNumVertices * 2];

			for (int z = 0; z < scene->mMeshes[i]->mNumVertices; ++z) {

				m->textures_coord[z * 2] = scene->mMeshes[i]->mTextureCoords[0][z].x;
				m->textures_coord[z * 2 + 1] = scene->mMeshes[i]->mTextureCoords[0][z].y;


			}

		}

		ImportMesh(m, path);
		
	//	mesh_v.push_back(m);

	}


	delete m;
}

void MeshImporter::ImportMesh(geometry_base_creating* temp_m, const char* path)
{

	float total_size = 0;
	
		uint ranges[2] = { temp_m->num_indices, temp_m->num_vertices };
		total_size += sizeof(ranges) + sizeof(uint) * 4;
		if (temp_m->Know_if_m_have[0] == 1 && temp_m->Know_if_m_have[1] == 1)
			total_size += sizeof(uint)*temp_m->num_indices + sizeof(float)*temp_m->num_vertices * 3;
		if (temp_m->Know_if_m_have[3] == 1)
			total_size += sizeof(float)*temp_m->num_vertices * 2;
		if (temp_m->Know_if_m_have[2] == 1)
			total_size += sizeof(float)*temp_m->num_vertices * 3;


	char* buffer_total = new char[total_size];
	char* cursor = buffer_total;

		
		uint size = sizeof(ranges);
		memcpy(cursor, ranges, size);
		cursor += size;

		size = sizeof(uint)*4;
		memcpy(cursor, temp_m->Know_if_m_have, size);
		cursor += size;

		if (temp_m->Know_if_m_have[1] == 1) {
			size = sizeof(uint)*temp_m->num_indices;
			memcpy(cursor, temp_m->indices, temp_m->num_indices * sizeof(uint));
			cursor += size;
		}

		//store vertex
		if (temp_m->Know_if_m_have[0] == 1) {
			size = sizeof(float)*temp_m->num_vertices * 3;
			memcpy(cursor, temp_m->vertices, size);
			cursor += size;
		}

		if (temp_m->Know_if_m_have[3] == 1) {
			
			size = sizeof(float)*temp_m->num_vertices * 2;
			memcpy(cursor, temp_m->textures_coord, size);
			cursor += size;
		}

		if (temp_m->Know_if_m_have[2] == 1) {
			
			size = sizeof(float)*temp_m->num_vertices * 3;
			memcpy(cursor, temp_m->normals, size);
			cursor += size;
		}


	std::string path_n = path;
	std::string path_new_format;
	App->fs_e->ChangeFormat_File(temp_m->name.c_str(), "ric", &path_new_format, App->fs_e->Mesh_Engine);
	App->fs_e->SaveFile(path_new_format.data(), buffer_total, total_size);

	path_new_format = "";

	

}

//char** cursor, Object* parent, int* num_childs

bool MeshImporter::LoadMesh(const char * path)
{

	char* buffer;
	App->fs_e->LoadFile(path, &buffer);
	char* cursor = buffer;

	//parent nullptr_ root go
	LoadRecursive(&cursor, nullptr, path);

	RELEASE_ARRAY(buffer);
	return false;
}


void MeshImporter::LoadRecursive(char ** cursor, GameObject* Parent, const char* path) {

	int child_num = 0;
	
	Parent = LoadMesh_variables(&cursor[0], Parent, &child_num, path);

	for (int i = 0; i < child_num; i++) {
		LoadRecursive(&cursor[0], Parent, path);
	}

}

GameObject* MeshImporter::LoadMesh_variables(char ** cursor, GameObject* parent, int* num_childs, const char* path)
{
	uint* ind = nullptr;
	uint name_lenght;
	uint num_mesh_iterator_count = 0;
	uint num_meshes = 0;
	uint size = 0;
	uint size_mesh = 0;

	std::string name_mesh;
	aiVector3D translation = { 0,0,0 };
	aiVector3D scaling = { 1,1,1 };
	aiQuaternion rotation = { 0, 0, 0, 1 };
	float3 translation_f;
	float3 scale_f;
	Quat Final_quat;
	geometry_base_creating* n_temp_mesh = nullptr;
	
	//need to fix
	std::string final_path_mesh;
	GameObject* child_gameobj = nullptr;
	size = sizeof(uint);
	memcpy(&num_meshes, cursor[0], size);
	cursor[0] += size;

	do {

		
		size = sizeof(char)*(MAXRANGCHAR);
		char* name = new char[MAXRANGCHAR];
		memcpy(name, cursor[0], size);
		name_mesh = name;
		cursor[0] += size;
		
		size = sizeof(int);
		memcpy(num_childs, cursor[0], size);
		cursor[0] += size;
		
		size = sizeof(aiVector3D);
		memcpy(&scaling, cursor[0], size);
		cursor[0] += size;
		scale_f.Set(scaling.x, scaling.y, scaling.z);
		
		size = sizeof(aiVector3D);
		memcpy(&translation, cursor[0], size);
		cursor[0] += size;
		translation_f.Set(translation.x, translation.y, translation.z);

		size = sizeof(aiQuaternion);
		memcpy(&rotation, cursor[0], size);
		cursor[0] += size;

		Final_quat = { rotation.w ,rotation.x,rotation.y,rotation.z};


		if (num_meshes > 0) {
			final_path_mesh = App->fs_e->Mesh_Engine->path + "\\" + name + ".ric";
			n_temp_mesh = Create_Base_Geometry(path, name_mesh.c_str(), final_path_mesh.c_str());
		}

		if (parent == nullptr) {
			child_gameobj = App->scene_intro->CreateNewGameObjects(name_mesh.c_str(), true, App->scene_intro->root_gameobject, Tag_Object_Enum::no_obj_tag, false);
		}
		else {
			child_gameobj = App->scene_intro->CreateNewGameObjects(name_mesh.c_str(), true, parent, Tag_Object_Enum::no_obj_tag, false);
		}
		if (n_temp_mesh!=nullptr) {
			child_gameobj->AddNewMesh(n_temp_mesh, final_path_mesh.c_str());
		}
			child_gameobj->AddNewTransform(translation_f, scale_f, Final_quat);
		
		num_mesh_iterator_count++;
	} while (num_mesh_iterator_count < num_meshes);


	delete[] ind;
	return child_gameobj;
}


geometry_base_creating * MeshImporter::Create_Base_Geometry(const char* path, const char* name, const char* final_path) {
	//need fix
	uint* ind = nullptr;
	uint name_lenght;
	uint num_mesh_iterator_count = 0;
	uint num_meshes = 0;
	uint size = 0;
	uint size_mesh = 0;

	std::string name_mesh;

	geometry_base_creating* n_temp_mesh = nullptr;
	std::string final_path_mesh;

	char* buffer_Mesh;
	App->fs_e->LoadFile(final_path, &buffer_Mesh);
	char* cursor_Mesh = buffer_Mesh;

	uint ranges[4]{ 0,0,0,0 };
	n_temp_mesh = new geometry_base_creating();
	uint ranges_num[2];

	size_mesh = sizeof(ranges_num);
	memcpy(ranges_num, cursor_Mesh, size_mesh);
	n_temp_mesh->num_indices = ranges_num[0];
	n_temp_mesh->num_vertices = ranges_num[1];
	cursor_Mesh += size_mesh;

	size_mesh = sizeof(uint) * 4;
	memcpy(ranges, cursor_Mesh, size_mesh);
	cursor_Mesh += size_mesh;

	if (ranges[1] == 1) {

		size_mesh = sizeof(uint)*n_temp_mesh->num_indices;
		ind = new uint[n_temp_mesh->num_indices];
		memcpy(ind, cursor_Mesh, size_mesh);
		n_temp_mesh->indices = ind;
		cursor_Mesh += size_mesh;
	}

	if (ranges[0] == 1) {

		size_mesh = sizeof(float)*n_temp_mesh->num_vertices * 3;
		n_temp_mesh->vertices = new float[n_temp_mesh->num_vertices * 3];
		memcpy(n_temp_mesh->vertices, cursor_Mesh, size_mesh);
		cursor_Mesh += size_mesh;
	}

	if (ranges[3] == 1) {

		size_mesh = sizeof(float)*n_temp_mesh->num_vertices * 2;
		n_temp_mesh->textures_coord = new float[n_temp_mesh->num_vertices * 2];
		memcpy(n_temp_mesh->textures_coord, cursor_Mesh, size_mesh);
		cursor_Mesh += size_mesh;
	}

	if (ranges[2] == 1) {

		size_mesh = sizeof(float)*n_temp_mesh->num_vertices * 3;
		n_temp_mesh->normals = new float[n_temp_mesh->num_vertices * 3];
		memcpy(n_temp_mesh->normals, cursor_Mesh, size_mesh);
		cursor_Mesh += size_mesh;
	}

	n_temp_mesh->BoundBox.SetNegativeInfinity();
	n_temp_mesh->BoundBox.Enclose((float3*)n_temp_mesh->vertices, n_temp_mesh->num_vertices);
	App->camera->CameraCenter(&n_temp_mesh->BoundBox);
	RELEASE_ARRAY(buffer_Mesh);
	return n_temp_mesh;
}

uint MeshImporter::RecursiveSizeScene(aiNode * node, const aiScene * scene)
{
	uint size = 0;
	aiMesh* temp_mesh=nullptr;
	uint n_meshes = 0;
	do {

		size += sizeof(aiVector3D) * 2 + sizeof(aiQuaternion) + sizeof(char)*MAXRANGCHAR + sizeof(uint);

		for (int i = 0; i < node->mNumChildren; i++) {
			size += RecursiveSizeScene(node->mChildren[i], scene);
		}
		n_meshes++;
	} while (n_meshes < node->mNumMeshes);
	size += sizeof(uint);
	return size;
}

uint MeshImporter::GetSceneSize(const aiScene * scene)
{

	aiNode* root_node = scene->mRootNode;

	uint size = RecursiveSizeScene(root_node, scene);


	return size;

}

void MeshImporter::Recursive_childs_general_bin(char **cursor, const aiScene * scene, aiNode * node, const char* path)
{

	if (scene != nullptr && cursor[0] != nullptr && node != nullptr) {

		General_Bin_Mesh(&cursor[0], scene, node, path);
		change_nameimporter++;
		for (int i = 0; i < node->mNumChildren; i++) {
			Recursive_childs_general_bin(&cursor[0], scene, node->mChildren[i], path);
		}

	}

}

void MeshImporter::General_Bin_Mesh(char ** cursor, const aiScene * scene, aiNode* node, const char* path)
{

	if (scene != nullptr && cursor[0] != nullptr && node!=nullptr) {
		
		aiMesh* mesh_temp = nullptr;
		uint num_child_iterator = 0;
		std::string name_mesh;
		uint size = 0;
		aiVector3D translation = { 0,0,0 };
		aiVector3D scaling = { 1,1,1 };
		aiQuaternion rotation = { 0, 0, 0, 1 };
		
		size = sizeof(uint);
		uint num_mesh = node->mNumMeshes;
		memcpy(cursor[0], &num_mesh,size);
		cursor[0] += size;

		do{ 
			
			std::string str_parent = path;
			size_t temp_uint = str_parent.rfind("\\") + 1;
			size_t temp_uint_2 = str_parent.rfind(".");
			uint diff = temp_uint_2 - temp_uint;
			std::string num_added_change_name_Str = std::to_string(change_nameimporter);
			std::string str_parent_substracted = str_parent.substr(temp_uint, diff);
			name_mesh = str_parent_substracted + "n"+ num_added_change_name_Str;
			node->mTransformation.Decompose(scaling, rotation, translation);
			if (node->mNumMeshes > 0 && scene->mRootNode!= node) {
				mesh_temp = scene->mMeshes[node->mMeshes[num_child_iterator]];
				std::string str_n_i = std::to_string(node->mMeshes[num_child_iterator]);
				name_mesh = str_parent_substracted + " " + str_n_i;
			}
				

				
			size = sizeof(char)* MAXRANGCHAR;
			memcpy(cursor[0], name_mesh.data(), size);
			cursor[0] += size;

			size = sizeof(uint);
			memcpy(cursor[0], &node->mNumChildren, size);
			cursor[0] += size;

			size = sizeof(aiVector3D);
			memcpy(cursor[0], &scaling, size);
			cursor[0] += size;

			size = sizeof(aiVector3D);
			memcpy(cursor[0], &translation, size);
			cursor[0] += size;

			Quat Final_quat = { rotation.x,rotation.y,rotation.z, rotation.w };

			size = sizeof(aiQuaternion);
			memcpy(cursor[0], &Final_quat, size);
			cursor[0] += size;
			num_child_iterator++;
		} while (num_child_iterator < node->mNumMeshes);
	}	

}


MeshImporter::MeshImporter()
{
}


MeshImporter::~MeshImporter()
{
}
