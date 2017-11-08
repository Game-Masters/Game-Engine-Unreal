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
