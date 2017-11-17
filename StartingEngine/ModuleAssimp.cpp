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


	/*for (int p = 0; p < meshes_vec.size(); p++) {
		meshes_vec[p]->Initialize();
	}*/

	return true;
}

update_status ModuleAssimp::PreUpdate(float dt)
{



	return update_status::UPDATE_CONTINUE;
}

update_status ModuleAssimp::Update(float dt)
{

	/*for (int p = 0; p < meshes_vec.size(); p++) {
		meshes_vec[p]->Draw();
	}
	
	if (App->input->flie_dropped) {
		if (IsTexture(App->input->dropped_filedir.c_str()) == false) {
			for (int p = 0; p < meshes_vec.size(); p++) {
				delete meshes_vec[p];
			}

			meshes_vec.clear();
		}
		loaded = ImportGeometry(App->input->dropped_filedir.c_str());
		for (int p = 0; p < meshes_vec.size(); p++) {
			meshes_vec[p]->Initialize();
		}

		if (loaded == true)
		{
			App->camera->CameraCenter(&meshes_vec.back()->mesh.BoundBox);
		}

		App->input->flie_dropped = false;


			App->input->flie_dropped = false;
	}
	
	if (App->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN) {
	//	App->camera->CameraRecenter();
	}*/

	return UPDATE_CONTINUE;
}


update_status ModuleAssimp::PostUpdate(float dt)
{

	


	return UPDATE_CONTINUE;
}

bool ModuleAssimp::Gui_Engine_Modules(float dt)
{

	if (ImGui::CollapsingHeader(name.c_str()))
	{
		
		

	}
	return true;

}


// Called before quitting
bool ModuleAssimp::CleanUp()
{

	



	return true;
}


void ModuleAssimp::ImportGeometry(const char* fbx, std::string *str)
{

	//----------------ASSIMP
	std::vector<geometry_base_creating*> mesh_v_temp;

	std::string full_path;
	full_path = fbx;

	
	const aiScene* scene = aiImportFile(full_path.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene != nullptr && scene->HasMeshes())
	{
		
		App->imp_mesh->CalculateMeshAssimp_Values(scene, fbx, str);
		aiReleaseImport(scene);
	}
}


float2 ModuleAssimp::LoadImage_devil(const char * theFileName, GLuint *buff)
{
	float2 texture_w_h;
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
			texture_w_h.x= (uint)ilGetInteger(IL_IMAGE_WIDTH); texture_w_h.y = (uint)ilGetInteger(IL_IMAGE_HEIGHT);
			//Create texture from file pixels
			textureLoaded = true;
		}

		//Delete file from memory
		ilDeleteImages(1, &imgID);
	}

	return texture_w_h;

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

bool ModuleAssimp::IsTexture(const char * path)
{
	bool ret = false;

	uint imgID = 0;
	ilGenImages(1, &imgID);
	ilBindImage(imgID);

	//Load image
	ILboolean success = ilLoadImage(path);
	if (success) {
		ret = true;
	}
	ilDeleteImages(1, &imgID);

	return ret;
}


aiNode* ModuleAssimp::Calc_AllGeometry_Childs(aiNode* Parent_node, uint search_mesh) {

	aiNode* temp;
	if (Parent_node != nullptr) {
		int i;
		for (i = 0; i < Parent_node->mNumChildren; i++) {
			for (int j = 0; j < Parent_node->mChildren[i]->mNumMeshes; j++) {
				if (Parent_node->mChildren[i]->mMeshes[j] == search_mesh) {
					return Parent_node->mChildren[i];
				}
			}
			if (Parent_node->mNumChildren > 0) {
				temp = Calc_AllGeometry_Childs(Parent_node->mChildren[i], search_mesh);
				if (temp != nullptr)
					return temp;
			}
		}	
		
		

	}
	return nullptr;

}

