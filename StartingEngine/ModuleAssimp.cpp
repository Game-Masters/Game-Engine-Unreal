#include "ModuleAssimp.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleGui.h"
#include "Module.h"
#include"Imgui/imgui_impl_sdl.h"
#include"Imgui\imgui_impl_sdl_gl3.h"
#include"Imgui/imgui.h"
#include"ModuleSceneIntro.h"
#include"Mesh.h"
#include"Material.h"

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
	ilutRenderer(ILUT_OPENGL);
	ilInit();
	iluInit();
	ilutInit();
	ilutRenderer(ILUT_OPENGL);

	ilClearColour(255, 255, 255, 000);

	//Check for error
	ILenum ilError = ilGetError();
	if (ilError != IL_NO_ERROR)
	{
		LOG("IlInit error!!");
	}



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

std::vector<geometry_base_creating*> ModuleAssimp::ImportGeometry(const char* fbx)
{

	//----------------ASSIMP
	std::vector<geometry_base_creating*> mesh_v_temp;

	std::string full_path;
	full_path = fbx;
	const aiScene* scene = aiImportFile(full_path.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene != nullptr && scene->HasMeshes())
	{
		// Use scene->mNumMeshes to iterate on scene->mMeshes array
		for (int i = 0; i < scene->mNumMeshes; i++) {
			m = new geometry_base_creating();
			m->num_vertices = scene->mMeshes[i]->mNumVertices;
			m->vertices = new float[m->num_vertices * 3];
			memcpy(m->vertices, scene->mMeshes[i]->mVertices, sizeof(float) * m->num_vertices * 3);
			LOG("New mesh with %d vertices", m->num_vertices);
			// copy faces
			if (scene->mMeshes[i]->HasFaces())
			{
				m->num_indices = scene->mMeshes[i]->mNumFaces * 3;
				m->indices = new uint[m->num_indices]; // assume each face is a triangle

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

			if (scene->mMeshes[i]->HasNormals()) {
				m->normals = new float[m->num_vertices * 3];
				memcpy(m->normals, scene->mMeshes[i]->mNormals, sizeof(float) * m->num_vertices * 3);
			}

			aiVector3D translation;
			aiVector3D scaling;
			aiQuaternion rotation;

			for (int i = 0; i < scene->mRootNode->mNumChildren; i++) {
				scene->mRootNode->mChildren[i]->mTransformation.Decompose(scaling, rotation, translation);
				m->translation.Set(translation.x, translation.y, translation.z);
				m->scaling.Set(scaling.x, scaling.y, scaling.z);
				m->rotation.Set(rotation.x, rotation.y, rotation.z, rotation.w);
			}


			if (scene->mMeshes[i]->HasTextureCoords(0))
			{
				m->textures_coord = new float[m->num_vertices * 2];

				for (int z = 0; z < scene->mMeshes[i]->mNumVertices; ++z) {

					m->textures_coord[z * 2] = scene->mMeshes[i]->mTextureCoords[0][z].x;
					m->textures_coord[z * 2 + 1] = scene->mMeshes[i]->mTextureCoords[0][z].y;


				}
				
			}

			mesh_v_temp.push_back(m);


		}
		aiReleaseImport(scene);
	}
	else {
		LOG("Error loading scene %s", full_path);
	}
	//aiMesh

	return mesh_v_temp;

}



std::vector<material_base_geometry*> ModuleAssimp::ImportGeometry_Texture(const char* fbx)
{

	//----------------ASSIMP
	std::vector<material_base_geometry*> mesh_v_temp;

	std::string full_path;
	full_path = fbx;
	const aiScene* scene = aiImportFile(full_path.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene != nullptr && scene->HasMeshes())
	{
		// Use scene->mNumMeshes to iterate on scene->mMeshes array
		for (int i = 0; i < scene->mNumMeshes; i++) {
			mat_geom = new material_base_geometry();
			mat_geom->num_vertices = scene->mMeshes[i]->mNumVertices;
			
			if (scene->mMeshes[i]->HasTextureCoords(0))
			{
				mat_geom->textures_coord = new float[mat_geom->num_vertices * 2];

				for (int z = 0; z < scene->mMeshes[i]->mNumVertices; ++z) {

					mat_geom->textures_coord[z * 2] = scene->mMeshes[i]->mTextureCoords[0][z].x;
					mat_geom->textures_coord[z * 2 + 1] = scene->mMeshes[i]->mTextureCoords[0][z].y;


				}

			}

			mesh_v_temp.push_back(mat_geom);

		}
		aiReleaseImport(scene);
	}
	else {
		LOG("Error loading scene %s", full_path);
	}
	//aiMesh

	return mesh_v_temp;

}








GLuint ModuleAssimp::LoadImage_devil(const char * theFileName, GLuint *buff)
{

	//Texture loading success
	bool textureLoaded = false;

	//Generate and set current image ID
	uint imgID = 0;
	ilGenImages(1, &imgID);
	ilBindImage(imgID);

	//Load image
	ILboolean success = ilLoadImage(theFileName);

	//Image loaded successfully
	if (success == IL_TRUE)
	{
		ILinfo ImageInfo;
		iluGetImageInfo(&ImageInfo);
		if (ImageInfo.Origin == IL_ORIGIN_UPPER_LEFT)
		{
			iluFlipImage();
		}

		//Convert image to RGBA
		success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

		if (success == IL_TRUE)
		{
			textureLoaded = loadTextureFromPixels32((GLuint*)ilGetData(), (GLuint)ilGetInteger(IL_IMAGE_WIDTH), (GLuint)ilGetInteger(IL_IMAGE_HEIGHT), buff);
			//Create texture from file pixels
			textureLoaded = true;
		}

		//Delete file from memory
		ilDeleteImages(1, &imgID);
	}

	//Report error
	if (!textureLoaded)
	{

	}
	return textureLoaded;

}

bool ModuleAssimp::loadTextureFromPixels32(GLuint * id_pixels, GLuint width_img, GLuint height_img, GLuint *buff)
{


	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, buff);
	glBindTexture(GL_TEXTURE_2D, *buff);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_img, height_img,
		0, GL_RGBA, GL_UNSIGNED_BYTE, id_pixels);
	glBindTexture(GL_TEXTURE_2D, NULL);
	//Check for error
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		printf("Error loading texture from %p pixels! %s\n", id_pixels, gluErrorString(error));
		return false;
	}

	return true;
}
