#include "ModuleResources.h"
#include"Application.h"
#include"ResourceTexture.h"
#include<string>;
#include"Timer.h"
#include <chrono>
#include <experimental/filesystem>
#include"ResourceShaderMaterial.h"

ModuleResources::ModuleResources()
{
}


ModuleResources::~ModuleResources()
{
}

bool ModuleResources::Start() {

	App->fs_e->Asset_User_File_Iteration();
	tim_check_Assets.Start();
	return true;
}

update_status ModuleResources::Update(float dt)
{
	resources;
	if (tim_check_Assets.ReadSec()>3) {
		tim_check_Assets.Stop();
		for (std::map<int, Resource*>::iterator it = resources.begin(); it != resources.end(); ++it){
				it->second->ReadMetaModif();
		}
		tim_check_Assets.Start();
	}

	return update_status::UPDATE_CONTINUE;
}

int ModuleResources::Find_UserRes(const char * file_in_assets) const
{
	
	for (std::map<int, Resource*>::const_iterator it = resources.begin(); it != resources.end(); ++it ) {
		std::string str = it->second->GetExportedFile();

		if (str == file_in_assets) {
			return it->second->GetUID();
		}
	}

	return -1;
}

int ModuleResources::Find_EngineRes(const char * file_in_assets) const
{
	for (std::map<int, Resource*>::const_iterator it = resources.begin(); it != resources.end(); ++it) {
		std::string str = it->second->GetFile();

		if (str == file_in_assets) {
			return it->second->GetUID();
		}
	}

	return -1;
}

void ModuleResources::ImportResources_Path_Usable(const char * new_file_in_assets)
{

	JSON_Value* val_doc;
	JSON_Object* obj_doc;
	std::string str_type;
	Resource* temp_mesh = nullptr;
	App->json_class->Create_JSON_DOC(&val_doc, &obj_doc, new_file_in_assets);

	str_type=json_object_get_string(obj_doc, "Type");

	if (str_type == "Texture") {
		temp_mesh= CreateNewResource(Resources_Type::texture);
	}
	else if (str_type == "Mesh") {
		temp_mesh = CreateNewResource(Resources_Type::mesh);
	}
	else if (str_type == "Shader") {
		temp_mesh = CreateNewResource(Resources_Type::shader_obj);
	}
	else if (str_type == "ShaderMaterial") {
		temp_mesh = CreateNewResource(Resources_Type::shader_program);
	}
	temp_mesh->Set_New_Resource_Files(json_object_get_string(obj_doc, "Path File"), json_object_get_string(obj_doc, "Path File Exported"));
	temp_mesh->SetLastTimeModf(json_object_get_number(obj_doc, "Last Time Modification"));
	if (temp_mesh->GetType() == Resources_Type::shader_program) {

		std::string path_t1 = temp_mesh->GetExportedFile();
		size_t end_name = path_t1.rfind(".");
		size_t sart_name = path_t1.rfind("\\") + 1;
		std::string name_t1 = path_t1.substr(sart_name, end_name - sart_name);
		((ResourceShaderMaterial*)temp_mesh)->SetProgram_Name(name_t1.c_str());
		((ResourceShaderMaterial*)temp_mesh)->GetJsonShaderProgram();
		((ResourceShaderMaterial*)temp_mesh)->LoadToMemory();
	}
	else if (temp_mesh->GetType() == Resources_Type::shader_obj) {
		std::string path_t1 = temp_mesh->GetExportedFile();
		size_t end_name = path_t1.rfind(".");
		std::string ext_t1 = path_t1.substr(end_name, path_t1.size());
		if (ext_t1 == ".vert") {
			((ResourceShaderObject*)temp_mesh)->Set_Type_Shader(ShaderType::vertex_shader);
		}
		else if (ext_t1 == ".frag") {
			((ResourceShaderObject*)temp_mesh)->Set_Type_Shader(ShaderType::fragment_shader);
		}
		((ResourceShaderObject*)temp_mesh)->LoadToMemory();
	}

	std::pair<int, Resource*> p;
	p.first = temp_mesh->GetUID();
	p.second = temp_mesh;
	resources.insert(p);

	json_value_free(val_doc);
}


bool ModuleResources::CleanUp() {

	for (std::map<int, Resource*>::iterator it = resources.begin(); it != resources.end(); ++it) {
		it->second->DeleteRes();
	}

	return true;
}

int ModuleResources::ImportFile(const char * new_file_in_assets, bool force)
{
	
	int ret = -1;
	Resources_Type type = DetectFiles_Type(new_file_in_assets);
	Resource* res = nullptr;
	std::string file_in_engine = "-1";


		if (type== Resources_Type::texture) {
			
			std::string path_in_engine = "-1";
			App->imp_mat->ImportMaterial(new_file_in_assets, &path_in_engine);
			//App->fs_e->ChangeFormat_File(new_file_in_assets, "dds", &path_in_engine, App->fs_e->Material_Engine);

			int uid_r = Find_UserRes(new_file_in_assets);
			
			res = Get(Create_New_resource_Text(path_in_engine, new_file_in_assets, uid_r, type));
			std::string str = new_file_in_assets;
			int s_t=str.rfind("\\");
			if (s_t!= -1) {
				res->CreateMeta();
			}
		}
		else if (type == Resources_Type::mesh) {
			std::string path_in_engine = "-1";
			App->assimp->ImportGeometry(new_file_in_assets, &file_in_engine);
			
			type = Resources_Type::mesh;
		}
	

	return ret;
}

int ModuleResources::GenerateNewUID() const
{
	LCG p;
	return p.Int();
}

int ModuleResources::Create_New_resource_Text(std::string path_in_engine, const char * new_file_in_assets, int uid_r, Resources_Type type)
{

	Resource* res = nullptr;

	if (uid_r == -1) {
		res = CreateNewResource(type);
		res->Set_New_Resource_Files(path_in_engine, new_file_in_assets);
	}
	else {
		res = Get(uid_r);
	}

	if (res->LoadToMemory() && res != nullptr) {

		std::pair<int, Resource*> p;
		p.first = res->GetUID();
		p.second = res;
		resources.insert(p);
	
	}
	return res->GetUID();

}

Resources_Type ModuleResources::DetectFiles_Type(const char * new_file_in_assets)
{
	std::string file_imported = new_file_in_assets;
	size_t find_ext = file_imported.rfind("."); find_ext += 1;
	std::string ext_file = file_imported.substr(find_ext, file_imported.size());
	Resources_Type type = Resources_Type::unknown_r;
	if (ext_file == "png" || ext_file == "PNG" || ext_file == "tga" || ext_file == "TGA") {
		type= Resources_Type::texture;
	}
	else if (ext_file == "fbx" || ext_file == "FBX") {
		type = Resources_Type::mesh;
	}
	else if (ext_file == "frag" || ext_file == "vert") {
		type = Resources_Type::shader_obj;
	}
	else if (ext_file == "shadermat") {
		type = Resources_Type::shader_program;
	}
	
	return type;
}

Resource * ModuleResources::Get(int uid)const
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
		ret = (Resource*)new ResourceMesh(uid);
		break;
	case Resources_Type::shader_obj:
		ret = (Resource*)new ResourceShaderObject(uid);
		break;
	case Resources_Type::shader_program:
		ret = (Resource*)new ResourceShaderMaterial(uid);
		break;
	default:
		break;
	}


	return ret;
}

std::vector<Resource*> ModuleResources::Get_TypeResources(Resources_Type type)
{
	std::vector<Resource*> shader_resources;
	for (std::map<int, Resource*>::const_iterator it = resources.begin(); it != resources.end(); ++it) {
		if (it->second->GetType() == type) {
			shader_resources.push_back(it->second);
		}
	}

	return shader_resources;
}

bool ModuleResources::AddResources(Resource * n_res)
{
	if (n_res!=nullptr) {

		std::pair<int, Resource*> p_res;
		p_res.first = n_res->GetUID();
		p_res.second = n_res;
		resources.insert(p_res);

		return true;
	}

	return false;
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

bool Resource::IsLoadedToMemory() const
{
	return loaded>0;
}

bool Resource::LoadToMemory()
{
	if (loaded == 0) {
		return true;
	}
	loaded++;
	return false;
}

void Resource::CreateMeta()
{
	std::string final_dest_str = exported_file + ".meta";
	App->json_class->Create_JSON_DOC(&val_doc, &obj_doc, final_dest_str.c_str());
	json_object_clear(obj_doc);
	if (type== Resources_Type::texture) {
		json_object_set_string(obj_doc, "Type", "Texture");
	}
	else if (type == Resources_Type::mesh) {
		json_object_set_string(obj_doc, "Type", "Mesh");
	}
	else if (type == Resources_Type::shader_obj) {
		json_object_set_string(obj_doc, "Type", "Shader");
	}
	else if (type == Resources_Type::shader_program) {
		json_object_set_string(obj_doc, "Type", "ShaderMaterial");
	}
	json_object_set_string(obj_doc, "Path File Exported", exported_file.c_str());
	json_object_set_string(obj_doc, "Path File", file.c_str());
	std::experimental::filesystem::path p = exported_file;

		auto ftime = std::experimental::filesystem::last_write_time(p);
		std::time_t cftime = decltype(ftime)::clock::to_time_t(ftime);
		time_from_last_modify = cftime;
		json_object_set_number(obj_doc, "Last Time Modification", cftime);

	char* serialized_string = json_serialize_to_string_pretty(val_doc);
	json_serialize_to_file(val_doc, final_dest_str.c_str());
}

bool Resource::ReadMetaModif()
{
	bool ret = false;

	std::experimental::filesystem::path p = exported_file;
	auto ftime = std::experimental::filesystem::last_write_time(p);
	std::time_t cftime = decltype(ftime)::clock::to_time_t(ftime);
	double last_mod = cftime;

	if (time_from_last_modify != last_mod && type== Resources_Type::texture || type == Resources_Type::shader_obj) {
		Update_Resource();
		SetLastTimeModf(last_mod);
		ret= true;
	}
	else {
		ret= false;
	}
	return ret;
}

void Resource::DeleteRes() {

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

uint Resource::GetLoadedNum() const
{
	return loaded;
}

void Resource::SetLastTimeModf(double time)
{
	time_from_last_modify = time;
}

void Resource::Update_Resource()
{
}
