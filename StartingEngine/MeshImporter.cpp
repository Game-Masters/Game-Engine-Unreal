#include "MeshImporter.h"
#include"Application.h"
#include"ModuleFileSystem_Engine.h"



void MeshImporter::ImportMesh(const char* name_mesh, std::vector<float> vertex, std::vector<uint> index, std::vector<float> texture_coord, std::vector<float> normals)
{

	uint num_vertex = vertex.size();
	uint num_index = index.size();
	uint num_texture_coord = texture_coord.size();
	uint num_normals = normals.size();

	//Calculate total buffer

	float total_size = sizeof(uint)*num_index + sizeof(float)*num_vertex + sizeof(float)*num_texture_coord + sizeof(float)*num_normals;

	char* buffer_total = new char(total_size);

	//store vertex
	uint size = sizeof(float)*num_vertex;
	memcpy(buffer_total, vertex.data(),size);

	size = sizeof(uint)*num_index;
	memcpy(buffer_total, index.data(), size);

	size = sizeof(float)*num_texture_coord;
	memcpy(buffer_total, texture_coord.data(), size);

	size = sizeof(float)*num_normals;
	memcpy(buffer_total, normals.data(), size);

	std::string path = name_mesh;
	//Need to improve
	path += ".ric";

	App->fs_e->SaveFile(path.c_str(), buffer_total, total_size);
	path = "";
}

MeshImporter::MeshImporter()
{
}


MeshImporter::~MeshImporter()
{
}
