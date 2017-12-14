#include "MeshImporter.h"
#include"Application.h"
#include"ModuleFileSystem_Engine.h"
#include"GameObject.h"
#include"MaterialImporter.h"
#include"ResourceMesh.h"
#include"ResourceTexture.h"
#define MAXRANGCHAR 70


void MeshImporter::CalculateMeshAssimp_Values(const aiScene* scene, const char* path, std::string *new_name)
{

	uint size_buffer_gen = GetSceneSize(scene);
	char* buffer_total_gen = new char[size_buffer_gen];
	char* cursor = buffer_total_gen;

	Recursive_childs_general_bin(&cursor, scene, scene->mRootNode, path);

	std::string path_n = path;
	std::string path_new_format;
	App->fs_e->ChangeFormat_File(path_n.c_str(), "ric", &path_new_format, App->fs_e->Mesh_Engine);
	ResourceMesh* bin_gen_res = (ResourceMesh*)App->resources_mod->CreateNewResource(Resources_Type::mesh);
	bin_gen_res->Set_New_Resource_Files(path_new_format, path);
	bin_gen_res->CreateMeta();
	App->fs_e->SaveFile(path_new_format.data(), buffer_total_gen, size_buffer_gen);
	*new_name = path_new_format;
	RELEASE_ARRAY(buffer_total_gen);

	//Load_Texture_Scenes(scene);


	//std::vector<geometry_base_creating*> mesh_v;
	for (int i = 0; i < scene->mNumMeshes; i++) {
		LOG("Mesh imported %i----------------", i);
		std::string str_parent = path;
		size_t temp_uint = str_parent.rfind("\\") + 1;
		size_t temp_uint_2 = str_parent.rfind(".");
		uint diff = temp_uint_2 - temp_uint;
		std::string str_parent_substracted = str_parent.substr(temp_uint, diff);
		std::string str_n_i = std::to_string(i);
		std::string name_mesh = str_parent_substracted + " " + str_n_i;
		Resource_Assimp_Creation(scene, path, name_mesh.c_str(),i);
	}


	//delete m;
}

void MeshImporter::Resource_Assimp_Creation(const aiScene * scene, const char* path, const char* name, int i)
{
	Resource* temp = nullptr;
	Resource_Mesh_Base* m = nullptr;

	m = new Resource_Mesh_Base();

	m->name = name;
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
		m->num_indices = scene->mMeshes[i]->mNumFaces * 3;
		LOG("The mesh has %d triangles", m->num_tris);
		m->indices = new uint[scene->mMeshes[i]->mNumFaces * 3]; // assume each face is a triangle
		LOG("The mesh has %d indices", m->num_indices);

		for (uint k = 0; k < scene->mMeshes[i]->mNumFaces; ++k)
		{
			if (scene->mMeshes[i]->mFaces[k].mNumIndices != 3) {
				LOG("WARNING, geometry face with != 3 indices!");
				m->num_indices -= 3;
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


	if (scene->mMeshes[i]->HasVertexColors(0))
	{
		m->Know_if_m_have[4] = 1;
		m->colors = new float[m->num_vertices * 3];
		memcpy(m->colors, scene->mMeshes[i]->mColors, sizeof(float) * m->num_vertices * 3);
	}

	m->BoundBox.SetNegativeInfinity();
	m->BoundBox.Enclose((float3*)m->vertices, m->num_vertices);
	m->id_image_devil = scene->mMeshes[i]->mMaterialIndex;

	//CreateResource
	std::string str_fin = App->fs_e->Mesh_Engine->path + "\\" + m->name + ".ric";
	int uuid_tm = App->resources_mod->Find_EngineRes(str_fin.c_str());
	if (uuid_tm == -1) {

		temp = App->resources_mod->CreateNewResource(Resources_Type::mesh);
		((ResourceMesh*)temp)->Res_Mesh_Base = m;
		((ResourceMesh*)temp)->Set_New_Resource_Files(str_fin, path);
		((ResourceMesh*)temp)->LoadToMemory();
		App->resources_mod->AddResources(temp);
	}
	else {
		temp = App->resources_mod->Get(uuid_tm);
	}

	ImportMesh(((ResourceMesh*)temp)->Res_Mesh_Base, path);
}




void MeshImporter::ImportMesh(Resource_Mesh_Base* temp_m, const char* path)
{

	float total_size = 0;
	
		uint ranges[2] = { temp_m->num_indices, temp_m->num_vertices };
		total_size += sizeof(ranges) + sizeof(uint) * 5;
		if (temp_m->Know_if_m_have[0] == 1 && temp_m->Know_if_m_have[1] == 1)
			total_size += sizeof(uint)*temp_m->num_indices + sizeof(float)*temp_m->num_vertices * 3;
		if (temp_m->Know_if_m_have[3] == 1)
			total_size += sizeof(float)*temp_m->num_vertices * 2;
		if (temp_m->Know_if_m_have[2] == 1)
			total_size += sizeof(float)*temp_m->num_vertices * 3;
		if (temp_m->Know_if_m_have[4] == 1)
			total_size += sizeof(float)*temp_m->num_vertices * 3;

		total_size += sizeof(uint)*1;

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

		if (temp_m->Know_if_m_have[4] == 1) {

			size = sizeof(float)*temp_m->num_vertices * 3;
			memcpy(cursor, temp_m->colors, size);
			cursor += size;

		}
		
		size = sizeof(uint);
		memcpy(cursor, &temp_m->id_image_devil, size);
		cursor += size;



	std::string path_n = path;
	std::string path_new_format;
	App->fs_e->ChangeFormat_File(temp_m->name.c_str(), "ric", &path_new_format, App->fs_e->Mesh_Engine);
	App->fs_e->SaveFile(path_new_format.data(), buffer_total, total_size);

	path_new_format = "";

	RELEASE_ARRAY(buffer_total);

}

//char** cursor, Object* parent, int* num_childs

bool MeshImporter::LoadMesh(const char * path, const char * path_fbx_gen, GameObject* parent, bool fbx_with_text)
{



	char* buffer=nullptr;
	App->fs_e->LoadFile(path, &buffer);
	char* cursor = buffer;

	//parent nullptr_ root go
	if (buffer != nullptr) {
		LoadRecursive(&cursor, nullptr, path, path_fbx_gen, parent, fbx_with_text);
	}
	App->imp_mat->Mat_Map.clear();
	RELEASE_ARRAY(buffer);
	return false;
}


void MeshImporter::LoadRecursive(char ** cursor, GameObject* Parent, const char* path, const char * path_fbx_gen, GameObject* Parent_Gen_World,bool fbx_with_text) {

	int child_num = 0;
	
	Parent = LoadMesh_variables(&cursor[0], Parent, &child_num, path, path_fbx_gen, Parent_Gen_World, fbx_with_text);

	for (int i = 0; i < child_num; i++) {
		LoadRecursive(&cursor[0], Parent, path,path_fbx_gen, Parent_Gen_World, fbx_with_text);
	}


}

GameObject* MeshImporter::LoadMesh_variables(char ** cursor, GameObject* parent, int* num_childs, const char* path, const char * path_fbx_gen, GameObject* Parent_Gen_World, bool fbx_with_text)
{
	uint* ind = nullptr;
	uint name_lenght;
	uint num_mesh_iterator_count = 0;
	uint num_meshes = 0;
	uint size = 0;
	uint size_mesh = 0;

	std::string name_mesh;
	std::string name_mesh_true;
	aiVector3D translation = { 0,0,0 };
	aiVector3D scaling = { 1,1,1 };
	aiQuaternion rotation = { 0, 0, 0, 1 };
	float3 translation_f;
	float3 scale_f;
	Quat Final_quat;
	Resource_Mesh_Base* n_temp_mesh = nullptr;
	Resource *temp = nullptr;
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
	

		size = sizeof(char)*(MAXRANGCHAR);
		char* name_mesh_temp = new char[MAXRANGCHAR];
		memcpy(name_mesh_temp, cursor[0], size);
		name_mesh_true = name_mesh_temp;
		cursor[0] += size;

		delete[] name_mesh_temp;

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

		Material* mat = nullptr;
	
		if (num_meshes > 0) {
			final_path_mesh = App->fs_e->Mesh_Engine->path + "\\" + name + ".ric";
			n_temp_mesh = Create_Base_Geometry(path, name_mesh.c_str(), final_path_mesh.c_str());
		}
		
		//delete name;
		if (parent == nullptr && Parent_Gen_World == nullptr) {
			child_gameobj = App->scene_intro->CreateNewGameObjects(name_mesh.c_str(), true, App->scene_intro->root_gameobject, Tag_Object_Enum::no_obj_tag, false);
		}
		else if (parent == nullptr && Parent_Gen_World != nullptr) {
			child_gameobj = App->scene_intro->CreateNewGameObjects(name_mesh_true.c_str(), true, Parent_Gen_World, Tag_Object_Enum::no_obj_tag, false);
		}
		else {
			child_gameobj = App->scene_intro->CreateNewGameObjects(name_mesh_true.c_str(), true, parent, Tag_Object_Enum::no_obj_tag, false);
		}

		//Add texture resource

		if (n_temp_mesh!=nullptr) {
			n_temp_mesh->name = name_mesh_true;
			if (fbx_with_text) {
				mat = AddTextureResourceToGO(n_temp_mesh, child_gameobj, final_path_mesh.c_str(), path_fbx_gen);
			}
				int uuid_mesh = App->resources_mod->Find_EngineRes(final_path_mesh.c_str());
				AddMeshResourceToGO(n_temp_mesh, child_gameobj, uuid_mesh, mat, final_path_mesh.c_str(), path_fbx_gen);
			}
			child_gameobj->AddNewTransform(translation_f, scale_f, Final_quat);
		
		num_mesh_iterator_count++;
		delete[] name;
	} while (num_mesh_iterator_count < num_meshes);


	delete[] ind;
	return child_gameobj;
}

Material* MeshImporter::AddTextureResourceToGO(Resource_Mesh_Base* n_temp_mesh, GameObject* child_gameobj, const char* final_path_mesh, const char * path_fbx_gen) {

	
	Resource *temp = nullptr;
	//need to fix
	Material* mat = nullptr;
	Resource* res_mat = nullptr;
	if (n_temp_mesh->id_image_devil != -1 && App->imp_mat->Mat_Map.size() > 0) {
		uint p_temp = 0;
		std::map<int, std::string>::iterator it = App->imp_mat->Mat_Map.find(n_temp_mesh->id_image_devil);
		if (it != App->imp_mat->Mat_Map.end()) {
			size_t size_temp = it->second.rfind(".") + 1;
			std::string f_path = it->second.substr(size_temp, it->second.size());
			if (f_path == "psd" || f_path == "PSD") {}
			else {
				//App->resources_mod->Find(it->second.c_str());
				int uuid_mat = App->resources_mod->Find_UserRes(it->second.c_str());
				if (uuid_mat != -1) {
					res_mat = App->resources_mod->Get(uuid_mat);
					res_mat->LoadToMemory();
					n_temp_mesh->id_image_devil = ((ResourceTexture*)res_mat)->id_image_devil;
					mat = child_gameobj->AddNewMaterial(uuid_mat);
					mat->UUID_mat = uuid_mat;
				}
				else {
					ResourceTexture* text = (ResourceTexture*)App->resources_mod->CreateNewResource(Resources_Type::texture);
					std::string fbx_path_temp = path_fbx_gen;
					text->Set_New_Resource_Files(it->second, fbx_path_temp);
					text->LoadToMemory();
					mat = child_gameobj->AddNewMaterial(text->GetUID());
				}
			}
		}
	}

	return mat;

}

void MeshImporter::AddMeshResourceToGO(Resource_Mesh_Base * n_temp_mesh, GameObject * child_gameobj, int uuid_mesh, Material* mat, const char * path, const char * path_fbx_gen)
{

	Resource *temp = nullptr;
	if (uuid_mesh == -1) {
		temp = App->resources_mod->CreateNewResource(Resources_Type::mesh);
		((ResourceMesh*)temp)->Res_Mesh_Base = n_temp_mesh;
		((ResourceMesh*)temp)->Set_New_Resource_Files(path, path_fbx_gen);
		((ResourceMesh*)temp)->LoadToMemory();
		App->resources_mod->AddResources(temp);
		if (mat != nullptr) {
			child_gameobj->AddNewMesh(((ResourceMesh*)temp)->GetUID(), path_fbx_gen,mat);
		}
		else {
			child_gameobj->AddNewMesh(((ResourceMesh*)temp)->GetUID(), path_fbx_gen);
		}
	}
	else {
		if (mat != nullptr) {
			child_gameobj->AddNewMesh(uuid_mesh, path_fbx_gen, mat);
		}
		else {
			child_gameobj->AddNewMesh(uuid_mesh, path_fbx_gen);
		}
	}
}

Resource_Mesh_Base * MeshImporter::Create_Base_Geometry(const char* path, const char* name, const char* final_path, GameObject* Parent_Gen_World) {
	//need fix
	uint* ind = nullptr;
	uint name_lenght;
	uint num_mesh_iterator_count = 0;
	uint num_meshes = 0;
	uint size = 0;
	uint size_mesh = 0;

	std::string name_mesh;

	Resource_Mesh_Base* n_temp_mesh = nullptr;
	std::string final_path_mesh;

	char* buffer_Mesh;
	App->fs_e->LoadFile(final_path, &buffer_Mesh);
	char* cursor_Mesh = buffer_Mesh;

	uint ranges[4]{ 0,0,0,0 };
	n_temp_mesh = new Resource_Mesh_Base();
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

	if (ranges[4] == 1) {

		size_mesh = sizeof(float)*n_temp_mesh->num_vertices * 3;
		n_temp_mesh->normals = new float[n_temp_mesh->num_vertices * 3];
		memcpy(n_temp_mesh->colors, cursor_Mesh, size_mesh);
		cursor_Mesh += size_mesh;

	}

	size_mesh = sizeof(uint);
	memcpy(&n_temp_mesh->id_image_devil, cursor_Mesh, size_mesh);
	cursor_Mesh += size_mesh;


	n_temp_mesh->BoundBox.SetNegativeInfinity();
	n_temp_mesh->BoundBox.Enclose((float3*)n_temp_mesh->vertices, n_temp_mesh->num_vertices);

	App->camera->CameraCenter(&n_temp_mesh->BoundBox);
	RELEASE_ARRAY(buffer_Mesh);
	return n_temp_mesh;
}

bool MeshImporter::Load_Texture_Scenes(const aiScene* scene)
{

	ILboolean success;

	/* initialization of DevIL */
	ilInit();
	if (scene != nullptr) {
		/* scan scene's materials for textures */
		for (unsigned int m = 0; m < scene->mNumMaterials; ++m)
		{
			int texIndex = 0;
			aiString aipath;  // filename


			if (scene->mMaterials[m]->GetTexture(aiTextureType_DIFFUSE, 0, &aipath) == AI_SUCCESS) {

				std::string file_name = aipath.C_Str();
				std::string file_name_end;
				App->imp_mat->ImportMaterial(file_name.c_str(), &file_name_end);
			}
		}

		for (int i = 0; i < scene->mNumMeshes; i++) {
			uint id_text = scene->mMeshes[i]->mMaterialIndex;

			aiMaterial* material = scene->mMaterials[scene->mMeshes[i]->mMaterialIndex];
			uint numTextures = material->GetTextureCount(aiTextureType_DIFFUSE);

			aiString path;
			uint p;


			if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS) {
				std::string temp = path.C_Str();
				size_t numt = temp.rfind("\\") + 1;
				temp = temp.substr(numt, temp.size());
				std::string final_path = App->fs_e->Material_User->path + "\\" + temp;
				//App->resources_mod->ImportFile(final_path.c_str());
				//App->fs_e->ChangeFormat_File(temp.c_str(), "dds", &final_path, App->fs_e->Material_Engine);

				std::pair<uint, std::string> pair_t;
				pair_t.first = id_text;
				pair_t.second = final_path;
				App->imp_mat->Mat_Map.insert(pair_t);
			}

		}
	}

	

	
	return true;

}

uint MeshImporter::RecursiveSizeScene(aiNode * node, const aiScene * scene)
{
	uint size = 0;
	aiMesh* temp_mesh=nullptr;
	uint n_meshes = 0;
	do {

		size += sizeof(aiVector3D) * 2 + sizeof(aiQuaternion) + sizeof(char)*MAXRANGCHAR+ sizeof(char)*MAXRANGCHAR + sizeof(uint);

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
		std::string name_mesh_true = "-1";
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
			name_mesh_true = "parent" + num_added_change_name_Str;
			name_mesh_true = node->mName.C_Str();
		
			node->mTransformation.Decompose(scaling, rotation, translation);
			
			
			if (node->mNumMeshes > 0 && scene->mRootNode!= node) {
				mesh_temp = scene->mMeshes[node->mMeshes[num_child_iterator]];
				std::string str_n_i = std::to_string(node->mMeshes[num_child_iterator]);
				name_mesh = str_parent_substracted + " " + str_n_i;
				name_mesh_true = node->mName.C_Str();
			}

			size = sizeof(char)* MAXRANGCHAR;
			memcpy(cursor[0], name_mesh.data(), size);
			cursor[0] += size;

			size = sizeof(char)* MAXRANGCHAR;
			memcpy(cursor[0], name_mesh_true.data(), size);
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
