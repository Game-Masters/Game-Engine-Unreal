#include "ResourceMesh.h"



ResourceMesh::ResourceMesh():Resource(uid_rm.Int(), Resources_Type::texture)
{
}


ResourceMesh::~ResourceMesh()
{
}

ResourceMesh::ResourceMesh(int id) : Resource(id, Resources_Type::texture)
{
}
