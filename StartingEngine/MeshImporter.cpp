#include "MeshImporter.h"
#include"Application.h"
#include"ModuleFileSystem_Engine.h"
#include"GameObject.h"


void MeshImporter::ImportMesh(const aiScene* scene, const char* path)
{
	float total_size = 0;
	
	geometry_base_creating* m = nullptr;
	std::vector<geometry_base_creating*> mesh_v;
	for (int i = 0; i < scene->mNumMeshes; i++) {

		LOG("Mesh imported %i----------------", i);
		m = new geometry_base_creating();
		
		m->name = scene->mRootNode->mChildren[i]->mName.C_Str();
		m->num_vertices = scene->mMeshes[i]->mNumVertices;
		m->vertices = new float[m->num_vertices * 3];
		LOG("New mesh with %d vertices", m->num_vertices);
		memcpy(m->vertices, scene->mMeshes[i]->mVertices, sizeof(float) * m->num_vertices * 3);
		if (m->vertices == nullptr) {
			LOG("The new mesh has failed trying to import the vertices");
		}
		else {
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
			m->num_indices = scene->mMeshes[i]->mNumFaces * 3;
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
				LOG("The new mesh has succed trying to import the normals");
			}
		}
		else {
			LOG("The new mesh has not normals so the engine cannot import them");
		}

		if (scene->mMeshes[i]->HasTextureCoords(0))
		{
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

		mesh_v.push_back(m);

	}

	

	for (int i = 0; i < mesh_v.size(); i++) {
		geometry_base_creating* temp_m = mesh_v[i];
		uint ranges[2] = { temp_m->num_indices, temp_m->num_vertices };
		total_size += sizeof(ranges) + sizeof(uint)*temp_m->num_indices + sizeof(float)*temp_m->num_vertices*3 
			+ sizeof(float)*temp_m->num_vertices* 2 +sizeof(float)*temp_m->num_vertices *3 
			+ sizeof(uint)+ sizeof(char)*temp_m->name.size()+ sizeof(float3) + sizeof(float3)+ sizeof(Quat);
	}

	char* buffer_total = new char[total_size];
	char* cursor = buffer_total;

	
	uint size = sizeof(mesh_v.size());
	uint data[1] = { mesh_v.size() };
	memcpy(cursor, data, size);
	
	for (int i = 0; i < mesh_v.size(); i++) {

		geometry_base_creating* temp_m = mesh_v[i];
		cursor += size;
		uint ranges[2] = { temp_m->num_indices, temp_m->num_vertices};
		size = sizeof(ranges);
		memcpy(cursor, ranges, size);

		cursor += size;
		size = sizeof(uint)*temp_m->num_indices;
		memcpy(cursor, temp_m->indices, temp_m->num_indices*sizeof(uint));

		//store vertex
		cursor += size;
		size = sizeof(float)*temp_m->num_vertices*3;
		memcpy(cursor, temp_m->vertices, size);

		cursor += size;
		size = sizeof(float)*temp_m->num_vertices * 2;
		memcpy(cursor, temp_m->textures_coord, size);

		cursor += size;
		size = sizeof(float)*temp_m->num_vertices * 3;
		memcpy(cursor, temp_m->normals, size);

		cursor += size;
		uint size_name = temp_m->name.size();
		size = sizeof(uint);
		memcpy(cursor, &size_name, size);

		cursor += size;
		size = sizeof(char)*temp_m->name.size();
		memcpy(cursor, temp_m->name.c_str(), size);

		cursor += size;
		size = sizeof(float3);
		memcpy(cursor, &m->translation, size);

		cursor += size;
		size = sizeof(float3);
		memcpy(cursor, &m->scaling, size);

		cursor += size;
		size = sizeof(Quat);
		memcpy(cursor, &m->rotation, size);
		
	}
	std::string path_n = path;
	std::string path_new_format;
	App->fs_e->ChangeFormat_File(path_n.c_str(), "ric", &path_new_format, App->fs_e->Mesh_Engine);
	App->fs_e->SaveFile(path_new_format.data(), buffer_total, total_size);
	path_new_format = "";

}

bool MeshImporter::LoadMesh(const char * path)
{

	char* buffer;
	App->fs_e->LoadFile(path, &buffer);
	char* cursor = buffer;

	uint num_meshes[] = {0};
	uint size_mesh = sizeof(uint);
	memcpy(num_meshes, cursor, size_mesh);

	LoadMesh_variables(cursor, num_meshes[0], size_mesh);

	RELEASE_ARRAY(buffer);
	return false;
}

void MeshImporter::LoadMesh_variables(char * cursor, uint num_meshes, uint size_mesh)
{
	GameObject* parent_go = nullptr;
	uint* ind = nullptr;
	uint name_lenght;
	if (num_meshes>1) {
		parent_go = App->scene_intro->CreateNewGameObjects("Mesh_Import", true, App->scene_intro->root_gameobject, Tag_Object_Enum::no_obj_tag, false);
	}
	else {
		parent_go = App->scene_intro->root_gameobject;
	}
	for (int i = 0; i <num_meshes; i++) {
		geometry_base_creating* n_temp_mesh = new geometry_base_creating();

		cursor += size_mesh;
		uint ranges[2];
		size_mesh = sizeof(ranges);
		memcpy(ranges, cursor, size_mesh);
		n_temp_mesh->num_indices = ranges[0];
		n_temp_mesh->num_vertices = ranges[1];

		cursor += size_mesh;
		size_mesh = sizeof(uint)*n_temp_mesh->num_indices;
		ind = new uint[n_temp_mesh->num_indices];
		memcpy(ind, cursor, size_mesh);
		n_temp_mesh->indices = ind;

		cursor += size_mesh;
		size_mesh = sizeof(float)*n_temp_mesh->num_vertices * 3;
		n_temp_mesh->vertices = new float[n_temp_mesh->num_vertices * 3];
		memcpy(n_temp_mesh->vertices, cursor, size_mesh);

		cursor += size_mesh;
		size_mesh = sizeof(float)*n_temp_mesh->num_vertices * 2;
		n_temp_mesh->textures_coord = new float[n_temp_mesh->num_vertices * 2];
		memcpy(n_temp_mesh->textures_coord, cursor, size_mesh);


		cursor += size_mesh;
		size_mesh = sizeof(float)*n_temp_mesh->num_vertices * 3;
		n_temp_mesh->normals = new float[n_temp_mesh->num_vertices * 3];
		memcpy(n_temp_mesh->normals, cursor, size_mesh);

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

	
		GameObject* child_gameobj = App->scene_intro->CreateNewGameObjects(n_temp_mesh->name.c_str(), true, parent_go, Tag_Object_Enum::no_obj_tag, false);
		child_gameobj->AddNewMesh(n_temp_mesh);
		child_gameobj->AddNewTransform(n_temp_mesh->translation, n_temp_mesh->scaling, n_temp_mesh->rotation);
	}

	delete[] ind;
}

MeshImporter::MeshImporter()
{
}


MeshImporter::~MeshImporter()
{
}
