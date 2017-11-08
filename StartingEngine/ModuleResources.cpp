#include "ModuleResources.h"
#include"Application.h"
#include"ResourceTexture.h"


ModuleResources::ModuleResources()
{
}


ModuleResources::~ModuleResources()
{
}

int ModuleResources::GenerateNewUID()
{
	LCG p;
	return p.Int();
}

Resource * ModuleResources::CreateNewResource(Resources_Type type, int force_uid)
{
	int uid = GenerateNewUID();
	Resource* ret = nullptr;
	switch (type) {
	case Resources_Type::texture:
		ret = (Resource*)new ResourceTexture(uid);
		break;

	default:
		break;
	}





	std::pair<int, Resource*> res_p;
	res_p.first = uid;
	res_p.second = ret;
	resources.insert(res_p);

	return ret;
}

Resource::Resource(int uid, Resources_Type type): uid(uid), type(type)
{
}

Resource::~Resource()
{
}

Resources_Type Resource::GetType() const
{
	return type;
}

int Resource::GetUID() const
{
	return uid;
}

const char * Resource::GetFile() const
{
	return file.c_str();
}

const char * Resource::GetExportedFile() const
{
	return exported_file.c_str();
}

uint Resource::CountReferences() const
{
	return loaded;
}
