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
