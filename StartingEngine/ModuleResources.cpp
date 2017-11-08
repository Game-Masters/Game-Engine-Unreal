#include "ModuleResources.h"
#include"Application.h"
#include"ResourceTexture.h"


ModuleResources::ModuleResources()
{
}


ModuleResources::~ModuleResources()
{
}

update_status ModuleResources::Update(float dt)
{
	resources;
	return update_status::UPDATE_CONTINUE;
}

int ModuleResources::Find(const char * file_in_assets) const
{
	
	for (std::map<int, Resource*>::const_iterator it = resources.begin(); it != resources.end(); ++it ) {
		std::string str = it->second->GetExportedFile();

		if (str == file_in_assets) {
			return it->second->GetUID();
		}
	}

	return -1;
}



int ModuleResources::ImportFile(const char * new_file_in_assets, bool force)
{
	int ret = -1;
	std::string file_imported = new_file_in_assets;
	size_t find_ext = file_imported.rfind("."); find_ext += 1;
	std::string ext_file = file_imported.substr(find_ext, file_imported.size());
	std::string file_in_engine="-1";
	Resources_Type type = Resources_Type::unknown_r;
	Resource* res = nullptr;

	if (ext_file == "png" || ext_file == "PNG" || ext_file == "tga" || ext_file == "TGA") {
		App->imp_mat->ImportMaterial(new_file_in_assets, &file_in_engine);
		type = Resources_Type::texture;
		res = CreateNewResource(type);
		res->Set_New_Resource_Files(file_in_engine, new_file_in_assets);
		App->assimp->LoadImage_devil(file_in_engine.c_str(), &((ResourceTexture*)res)->id_image_devil);
		ret = res->GetUID();
	}
	else if (ext_file == "fbx" || ext_file == "FBX") {
		App->assimp->ImportGeometry(new_file_in_assets, &file_in_engine);
		App->imp_mesh->LoadMesh(file_in_engine.c_str());
		type = Resources_Type::mesh;
	}

	if (file_in_engine != "-1" && type!= Resources_Type::unknown_r) {
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

Resource * ModuleResources::Get(int uid)
{
	if (uid == -1) {
		return nullptr;
	}
	return resources.find(uid)->second;
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
