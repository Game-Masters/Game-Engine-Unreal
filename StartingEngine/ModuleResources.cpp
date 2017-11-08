#include "ModuleResources.h"
#include"Application.h"
#include"ResourceTexture.h"


ModuleResources::ModuleResources()
{
}


ModuleResources::~ModuleResources()
{
}

int ModuleResources::ImportFile(const char * new_file_in_assets, bool force)
{
	int ret = -1;
	std::string file_imported = new_file_in_assets;
	size_t find_ext = file_imported.rfind("."); find_ext += 1;
	std::string ext_file = file_imported.substr(find_ext, file_imported.size());
	std::string file_in_engine="-1";
	Resources_Type type = Resources_Type::unknown_r;

	if (ext_file == "png" || ext_file == "PNG") {
		App->imp_mat->ImportMaterial(new_file_in_assets, &file_in_engine);
		type = Resources_Type::texture;
	}
	else if (ext_file == "fbx" || ext_file == "FBX") {

		App->assimp->ImportGeometry(new_file_in_assets, &file_in_engine);
		App->imp_mesh->LoadMesh(file_in_engine.c_str());
		type = Resources_Type::mesh;
	}

	if (file_in_engine != "-1" && type!= Resources_Type::unknown_r) {
		Resource* res = CreateNewResource(type);
		res->Set_New_Resource_Files(file_in_engine, new_file_in_assets);
		ret= res->GetUID();
		std::pair<int, Resource*> p;
		p.first = ret;
		p.second = res;
		resources.insert(p);
	}

	return ret;
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
	case Resources_Type::mesh:
		ret = (Resource*)new ResourceTexture(uid);
		break;

	default:
		break;
	}




	if (ret != nullptr) {
		std::pair<int, Resource*> res_p;
		res_p.first = uid;
		res_p.second = ret;
		resources.insert(res_p);
	}
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

void Resource::Set_New_Resource_Files(std::string file, std::string exported_file)
{
	this->file = file;
	this->exported_file = exported_file;
}

uint Resource::CountReferences() const
{
	return loaded;
}
