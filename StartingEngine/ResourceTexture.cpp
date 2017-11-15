#include "ResourceTexture.h"



ResourceTexture::ResourceTexture() :Resource(uid_rt.Int(), Resources_Type::texture)
{

}

ResourceTexture::~ResourceTexture()
{
}

ResourceTexture::ResourceTexture(int id): Resource(id,Resources_Type::texture)
{

	
}

void ResourceTexture::DeleteRes() {
	glDeleteBuffers(1, &id_image_devil);
}

bool ResourceTexture::LoadToMemory()
{
	if (loaded == 0) {
		App->assimp->LoadImage_devil(this->file.c_str(), &id_image_devil);
		loaded++;
		return true;
	}
		loaded++;
	return false;
}

void ResourceTexture::Update_Resource()
{
	if (loaded > 0) {
		glDeleteBuffers(1, &id_image_devil);
		std::string n_file;
		App->imp_mat->ImportMaterial(exported_file.c_str(), &n_file);
		exported_file = n_file;
		App->assimp->LoadImage_devil(n_file.c_str(), &id_image_devil);
	}
}
