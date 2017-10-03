#include "ModuleAssimp.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleGui.h"
#include "Module.h"
#include"Imgui/imgui_impl_sdl.h"
#include"Imgui\imgui_impl_sdl_gl3.h"
#include"Imgui/imgui.h"
#include"ModuleSceneIntro.h"



ModuleAssimp::ModuleAssimp(bool start_enabled) : Module(start_enabled)
{

}

// Destructor
ModuleAssimp::~ModuleAssimp()
{
}

// Called before render is available
bool ModuleAssimp::Start()
{
	// Stream log messages to Debug window
	struct aiLogStream stream;
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, NULL);
	aiAttachLogStream(&stream);

	//ImportGeometry();

	for (int p = 0; p < meshes_vec.size(); p++) {
		meshes_vec[p]->Initialize();
	}

	return true;
}

update_status ModuleAssimp::PreUpdate(float dt)
{



	return update_status::UPDATE_CONTINUE;
}

update_status ModuleAssimp::Update(float dt)
{

	for (int p = 0; p < meshes_vec.size(); p++) {
		meshes_vec[p]->Draw();
	}


	return UPDATE_CONTINUE;
}


update_status ModuleAssimp::PostUpdate(float dt)
{

	if (App->input->flie_dropped) {
		ImportGeometry(App->input->dropped_filedir);
		for (int p = 0; p < meshes_vec.size(); p++) {
			meshes_vec[p]->Initialize();
		}
		App->input->flie_dropped = false;
	}

	return UPDATE_CONTINUE;
}

bool ModuleAssimp::Gui_Engine_Modules(float dt)
{
	
	return false;
}


// Called before quitting
bool ModuleAssimp::CleanUp()
{
	


	return true;
}

void ModuleAssimp::ImportGeometry(char* fbx)
{

	//----------------ASSIMP
	m = new Geometry_Manager(PrimitiveTypes::Primitive_Mesh);

	std::string full_path;
	full_path = fbx;
	const aiScene* scene = aiImportFile(full_path.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene != nullptr && scene->HasMeshes())
	{
		// Use scene->mNumMeshes to iterate on scene->mMeshes array
		for (int i = 0; i < scene->mNumMeshes; i++) {
			m->mesh.num_vertices = scene->mMeshes[i]->mNumVertices;
			m->mesh.vertices = new float[m->mesh.num_vertices * 3];
			memcpy(m->mesh.vertices, scene->mMeshes[i]->mVertices, sizeof(float) * m->mesh.num_vertices * 3);
			LOG("New mesh with %d vertices", m->mesh.num_vertices);
			// copy faces
			if (scene->mMeshes[i]->HasFaces())
			{
				m->mesh.num_indices = scene->mMeshes[i]->mNumFaces * 3;
				m->mesh.indices = new uint[m->mesh.num_indices]; // assume each face is a triangle
				for (uint k = 0; k < scene->mMeshes[i]->mNumFaces; ++k)
				{
					if (scene->mMeshes[i]->mFaces[k].mNumIndices != 3) {
						LOG("WARNING, geometry face with != 3 indices!");
					}
					else {
						memcpy(&m->mesh.indices[k * 3], scene->mMeshes[i]->mFaces[k].mIndices, 3 * sizeof(uint));
					}
				}
			}
			meshes_vec.push_back(m);


		}
		aiReleaseImport(scene);
	}
	else {
		LOG("Error loading scene %s", full_path);
	}
	//aiMesh



}
