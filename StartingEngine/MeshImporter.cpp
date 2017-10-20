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

	//Need to do recursive general function


	geometry_base_creating* m = nullptr;
	std::vector<geometry_base_creating*> mesh_v;
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
		m->BoundBox.SetNegativeInfinity();
		m->BoundBox.Enclose((float3*)m->vertices, m->num_vertices);
		App->camera->CameraCenter(&m->BoundBox);
		LOG("A BoundBox has been added to the mesh", m->num_vertices);
		// copy faces
		if (scene->mMeshes[i]->HasFaces())
		{
			m->num_tris = scene->mMeshes[i]->mNumFaces;
			m->num_indices = scene->mMeshes[i]->mNumFaces *3;
			LOG("The mesh has %d triangles", m->num_tris);
			m->indices = new uint[m->num_indices]; // assume each face is a triangle
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
			m->normals = new float[m->num_vertices * 3];
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
			m->textures_coord = new float[m->num_vertices * 2];

			for (int z = 0; z < scene->mMeshes[i]->mNumVertices; ++z) {

				m->textures_coord[z * 2] = scene->mMeshes[i]->mTextureCoords[0][z].x;
				m->textures_coord[z * 2 + 1] = scene->mMeshes[i]->mTextureCoords[0][z].y;


			}

		}

		aiVector3D translation;
		aiVector3D scaling;
		aiQuaternion rotation;

		aiNode* nod = App->assimp->Calc_AllGeometry_Childs(scene->mRootNode, i);
		aiMatrix4x4 temp_trans;
		if (nod != nullptr) {
			while (nod->mParent != nullptr) {
				temp_trans *= nod->mTransformation;
				nod = nod->mParent;
			}
			LOG("The new mesh is imported in the same position as in the original file");
		}
		else {
			LOG("The new mesh has failed trying to import the transformation of the geometry");
		}
		temp_trans.Decompose(scaling, rotation, translation);
		m->translation.Set(translation.x, translation.y, translation.z);
		m->scaling.Set(scaling.x, scaling.y, scaling.z);
		m->rotation.Set(rotation.x, rotation.y, rotation.z, rotation.w);

		ImportMesh(m, path);

		mesh_v.push_back(m);

	}



}

void MeshImporter::ImportMesh(geometry_base_creating* temp_m, const char* path)
{

	float total_size = 0;
	
		uint ranges[2] = { temp_m->num_indices, temp_m->num_vertices };
		total_size += sizeof(ranges) + sizeof(uint)*temp_m->num_indices + sizeof(float)*temp_m->num_vertices*3 
			+ sizeof(float)*temp_m->num_vertices* 2 +sizeof(float)*temp_m->num_vertices *3 
			+ sizeof(uint)+ sizeof(char)*temp_m->name.size()+ sizeof(float3) + sizeof(float3)+ sizeof(Quat)
			+ sizeof(uint)*4;

	char* buffer_total = new char[total_size];
	char* cursor = buffer_total;

		
		//cursor += size;
		uint size = sizeof(ranges);
		memcpy(cursor, ranges, size);

		cursor += size;
		size = sizeof(uint)*4;
		memcpy(cursor, temp_m->Know_if_m_have, size);

		if (temp_m->Know_if_m_have[1] == 1) {
			cursor += size;
			size = sizeof(uint)*temp_m->num_indices;
			memcpy(cursor, temp_m->indices, temp_m->num_indices * sizeof(uint));
		}

		//store vertex
		if (temp_m->Know_if_m_have[0] == 1) {
			cursor += size;
			size = sizeof(float)*temp_m->num_vertices * 3;
			memcpy(cursor, temp_m->vertices, size);
		}

		if (temp_m->Know_if_m_have[3] == 1) {
			cursor += size;
			size = sizeof(float)*temp_m->num_vertices * 2;
			memcpy(cursor, temp_m->textures_coord, size);
		}

		if (temp_m->Know_if_m_have[2] == 1) {
			cursor += size;
			size = sizeof(float)*temp_m->num_vertices * 3;
			memcpy(cursor, temp_m->normals, size);
		}

		cursor += size;
		uint size_name = temp_m->name.size();
		size = sizeof(uint);
		memcpy(cursor, &size_name, size);

		cursor += size;
		size = sizeof(char)*temp_m->name.size();
		memcpy(cursor, temp_m->name.c_str(), size);

		cursor += size;
		size = sizeof(float3);
		memcpy(cursor, &temp_m->translation, size);

		cursor += size;
		size = sizeof(float3);
		memcpy(cursor, &temp_m->scaling, size);

		cursor += size;
		size = sizeof(Quat);
		memcpy(cursor, &temp_m->rotation, size);

	std::string path_n = path;
	std::string path_new_format;
	App->fs_e->ChangeFormat_File(temp_m->name.c_str(), "ric", &path_new_format, App->fs_e->Mesh_Engine);
	App->fs_e->SaveFile(path_new_format.data(), buffer_total, total_size);

	//TO TEST IF WORKS-----------------------------------------------
	LoadMesh(path_new_format.c_str());


	//---------------------------------------------------------------
	path_new_format = "";

	

}

bool MeshImporter::LoadMesh(const char * path)
{

	char* buffer;
	App->fs_e->LoadFile(path, &buffer);
	char* cursor = buffer;
	geometry_base_creating* n_temp_mesh = new geometry_base_creating();
	
	uint ranges[2];
	uint size_mesh = sizeof(ranges);
	memcpy(ranges, cursor, size_mesh);
	n_temp_mesh->num_indices = ranges[0];
	n_temp_mesh->num_vertices = ranges[1];

	LoadMesh_variables(cursor, n_temp_mesh, size_mesh);

	RELEASE_ARRAY(buffer);
	return false;
}

void MeshImporter::LoadMesh_variables(char * cursor, geometry_base_creating* n_temp_mesh, uint size_mesh)
{
	uint* ind = nullptr;
	uint name_lenght;
	
	uint ranges[4]{ 0,0,0,0 };


		cursor += size_mesh;
		size_mesh = sizeof(uint)*4;
		memcpy(ranges, cursor, size_mesh);

		if (ranges[1] == 1) {
			cursor += size_mesh;
			size_mesh = sizeof(uint)*n_temp_mesh->num_indices;
			ind = new uint[n_temp_mesh->num_indices];
			memcpy(ind, cursor, size_mesh);
			n_temp_mesh->indices = ind;
		}

		if (ranges[0] == 1) {
			cursor += size_mesh;
			size_mesh = sizeof(float)*n_temp_mesh->num_vertices * 3;
			n_temp_mesh->vertices = new float[n_temp_mesh->num_vertices * 3];
			memcpy(n_temp_mesh->vertices, cursor, size_mesh);
		}

		if (ranges[3] == 1) {
			cursor += size_mesh;
			size_mesh = sizeof(float)*n_temp_mesh->num_vertices * 2;
			n_temp_mesh->textures_coord = new float[n_temp_mesh->num_vertices * 2];
			memcpy(n_temp_mesh->textures_coord, cursor, size_mesh);
		}

		if (ranges[2] == 1) {
			cursor += size_mesh;
			size_mesh = sizeof(float)*n_temp_mesh->num_vertices * 3;
			n_temp_mesh->normals = new float[n_temp_mesh->num_vertices * 3];
			memcpy(n_temp_mesh->normals, cursor, size_mesh);
		}

		cursor += size_mesh;
		size_mesh = sizeof(uint);
		//name_lenght = new uint();
		memcpy(&name_lenght, cursor, size_mesh);

		cursor += size_mesh;
		size_mesh = sizeof(char)*(name_lenght);
		char* name = new char[name_lenght];
		memcpy(name, cursor, size_mesh);
		n_temp_mesh->name = name;

		cursor += size_mesh;
		size_mesh = sizeof(float3);
		memcpy(&n_temp_mesh->translation, cursor, size_mesh);

		cursor += size_mesh;
		size_mesh = sizeof(float3);
		memcpy(&n_temp_mesh->scaling, cursor, size_mesh);

		cursor += size_mesh;
		size_mesh = sizeof(Quat);
		memcpy(&n_temp_mesh->rotation, cursor, size_mesh);

	
		GameObject* child_gameobj = App->scene_intro->CreateNewGameObjects(n_temp_mesh->name.c_str(), true, App->scene_intro->root_gameobject, Tag_Object_Enum::no_obj_tag, false);
		child_gameobj->AddNewMesh(n_temp_mesh);
		child_gameobj->AddNewTransform(n_temp_mesh->translation, n_temp_mesh->scaling, n_temp_mesh->rotation);


	delete[] ind;
}

uint MeshImporter::RecursiveSizeScene(aiNode * node, const aiScene * scene)
{
	uint size = 0;
	aiMesh* temp_mesh=nullptr;
	
	size += sizeof(aiVector3D) * 2 + sizeof(aiQuaternion) + sizeof(char)*MAXRANGCHAR + sizeof(uint);

	for (int i = 0; i < node->mNumChildren; i++) {
		size += RecursiveSizeScene(node->mChildren[i], scene);
	}

	return size;
}

uint MeshImporter::GetSceneSize(const aiScene * scene)
{

	aiNode* root_node = scene->mRootNode;

	uint size = RecursiveSizeScene(root_node, scene);
	size += scene->mNumMeshes * sizeof(uint);

	return size;

}


MeshImporter::MeshImporter()
{
}


MeshImporter::~MeshImporter()
{
}
