#include "ModuleFileSystem_Engine.h"
#include"Application.h"
#include<filesystem>
#include <iostream>
#include <experimental/filesystem>
#include<fstream>
#include"Imgui\imgui.h"

bool ModuleFileSystem_Engine::Init()
{
	RootDirect_User = nullptr;
	RootDirect_User = CreateDir("Assets", Directory_Type::user_directory_type);
	Mesh_User = CreateDir("Mesh", Directory_Type::user_directory_type, RootDirect_User);
	Material_User = CreateDir("Material", Directory_Type::user_directory_type, RootDirect_User);
	Scene_User = CreateDir("Scene", Directory_Type::user_directory_type, RootDirect_User);

	Directories_User_V.push_back(RootDirect_User);
	Directories_User_V.push_back(Mesh_User);
	Directories_User_V.push_back(Material_User);
	Directories_User_V.push_back(Scene_User);

	RootDirect_Engine = nullptr;
	RootDirect_Engine = CreateDir("Library", Directory_Type::engine_directory_type, nullptr, true);
	Mesh_Engine = CreateDir("Mesh", Directory_Type::engine_directory_type, RootDirect_Engine, true);
	Material_Engine = CreateDir("Material", Directory_Type::engine_directory_type, RootDirect_Engine, true);

	return true;
}

bool ModuleFileSystem_Engine::Start()
{
	//E:\CITM\3ero VJ\Game-Engine-Unreal\StartingEngine\Game\Data\Icons
	
	return true;
}

bool ModuleFileSystem_Engine::CleanUp()
{
	delete RootDirect_User;
	delete RootDirect_Engine;
	delete Mesh_User;
	delete Material_User;
	delete Mesh_Engine;
	delete Material_Engine;

	return true;
}

Directory_* ModuleFileSystem_Engine::CreateDir(const char * name, Directory_Type type, Directory_ * parent, bool visible)
{

	Directory_ *Root_node_temp = nullptr;

	if (type== Directory_Type::engine_directory_type) {
		Root_node_temp = RootDirect_Engine;
	}
	else if(type == Directory_Type::user_directory_type) {
		Root_node_temp = RootDirect_User;
	}

	Directory_ *temp = new Directory_();
	if (Root_node_temp == nullptr) {
		temp->name = name;
		temp->path = "..\\Game\\";temp->path += name;
		temp->parent = nullptr;
		CreateDirectory(temp->path.c_str(), false);
	}
	else {
		if (IterateChild_Exsist(Root_node_temp, name)==false && parent!= nullptr) {
			temp->name = name;
			temp->parent = parent;
			std::string path_create = parent->path + "\\" + name;
			temp->path = path_create;
			CreateDirectory(path_create.c_str(),false);
			parent->dir_cont_v.push_back(temp);
		}

	}

	if (visible == false) {
		SetFileAttributes(temp->path.c_str(), FILE_ATTRIBUTE_HIDDEN);
	}
	else {
		SetFileAttributes(temp->path.c_str(), FILE_ATTRIBUTE_READONLY);
	}

	return temp;
}

bool  ModuleFileSystem_Engine::IterateChild_Exsist(Directory_ *temp, const char* name) {
	//bool ret = false;
	for (int i = 0; i < temp->dir_cont_v.size(); i++) {
		if (temp->dir_cont_v[i]->name == name) {
			return true;
		}
		bool ret = IterateChild_Exsist(temp->dir_cont_v[i], name);
		if (ret == true)
			return true;
	}
	return false;
}

int ModuleFileSystem_Engine::LoadFile(const char * path, char ** buffer)
{
	bool ret = false;
	int length_file = 0;
	std::ifstream file_stream (path, std::ifstream::binary);
	
	if (file_stream.bad()) {
		LOG("The file %s cannot be readed", path);
	}
	else {
		if (file_stream) {
			//Read file explanation http://www.cplusplus.com/reference/istream/istream/read/
			// get length of file:
			file_stream.seekg(0, file_stream.end);
			length_file = file_stream.tellg();
			file_stream.seekg(0, file_stream.beg);
			LOG("Reading File %s of %i characters", path, length_file);
			*buffer = new char[length_file];
			// read data as a block:
			file_stream.read(*buffer, length_file);

			if (file_stream) {
				LOG("File load correctly");
				ret = true;
			}
			else {
				LOG("File load without succes");
				ret = false;
			}

			file_stream.close();

		}
	}
	return length_file;
}

bool ModuleFileSystem_Engine::SaveFile(const char * path, char * buffer, uint size, Directory_* parent)
{
	//Save file documentation http://www.cplusplus.com/reference/ostream/ostream/write/
	bool ret = false;
	
	std::ofstream outfile(path, std::ofstream::binary);

	if (outfile.good()) {
		// write to outfile
		outfile.write(buffer, size);
	}
	else {
		LOG("Failed to write the file %s", path);
	}


	outfile.close();
	return ret;
}




ModuleFileSystem_Engine::ModuleFileSystem_Engine()
{
}


ModuleFileSystem_Engine::~ModuleFileSystem_Engine()
{
}

bool ModuleFileSystem_Engine::SerchInDirectorySystem(const char * path, File_type type)
{
	std::string n_path;
	size_t s_str = 0;
	switch (type) {
	case File_type::fbx_type:
		ChangeFormat_File(path, "ric", &n_path, Mesh_Engine);
			break;

	case File_type::png_type:
		ChangeFormat_File(path, "dds", &n_path, Material_Engine);
		break;
	}

	for (std::experimental::filesystem::recursive_directory_iterator::value_type item : std::experimental::filesystem::recursive_directory_iterator(RootDirect_Engine->path)) {
		std::string str_path = item.path().string().c_str();
			if (n_path==str_path) {
				return true;
			}
	}
	n_path.clear();
	return false;
}

void ModuleFileSystem_Engine::ChangeFormat_File(const char * path, const char * n_format, std::string *new_path, Directory_ *Parent)
{
	std::string full_path_complete = path;
	std::size_t pos_to_find = full_path_complete.rfind("\\");
	pos_to_find += 1;
	std::size_t pos_to_find_end = full_path_complete.rfind(".");
	std::size_t diff = pos_to_find_end - pos_to_find;
	std::string Imp_Path = full_path_complete.substr(pos_to_find, diff);

	std::string parent_path = Parent->path;
	std::string final_path = parent_path + "\\" + Imp_Path;
	std::string n_form_std = n_format;
	final_path += "." + n_form_std;
	*new_path = final_path.c_str();
}

void ModuleFileSystem_Engine::IterateAllDirect(const char* path_dir, std::string *new_path) {

	*new_path = "-1";

	for (std::experimental::filesystem::directory_iterator::value_type item : std::experimental::filesystem::directory_iterator(path_dir)) {
		std::string str_path = item.path().string().c_str();
		bool is_dir = false;
		if (ImGui::TreeNode(str_path.c_str()))
		{

			if (ImGui::IsItemClicked()) {
				if (ImGui::IsMouseDoubleClicked(0)) {
					*new_path = str_path.c_str();
				}
			}

			if (item.status().type() == std::experimental::filesystem::file_type::directory) {
				IterateAllDirect(str_path.c_str(), new_path);
			}
			ImGui::TreePop();
		}


		//ImGui::TreePop();
	}

}

void ModuleFileSystem_Engine::IterateAllDirect_To_Save(const char * path_dir, std::string * new_path)
{

	for (std::experimental::filesystem::directory_iterator::value_type item : std::experimental::filesystem::directory_iterator(path_dir)) {
		std::string str_path = item.path().string().c_str();
		bool is_dir = false;
		if (item.status().type() == std::experimental::filesystem::file_type::directory) {
			if (ImGui::TreeNode(str_path.c_str()))
			{

				if (ImGui::IsItemClicked()) {
					if (ImGui::IsMouseDoubleClicked(0)) {
						*new_path = str_path.c_str();
					}
				}


				IterateAllDirect_To_Save(str_path.c_str(), new_path);

				ImGui::TreePop();
			}
		}
	}
}

void ModuleFileSystem_Engine::Asset_User_File_Iteration() {
	for (std::experimental::filesystem::recursive_directory_iterator::value_type item : std::experimental::filesystem::recursive_directory_iterator(RootDirect_User->path)) {
		std::string str_path = item.path().string().c_str();

		//Check extension
		size_t start_ext = str_path.rfind("\\") + 1;
		std::string name_str= str_path.substr(start_ext, str_path.size());
		size_t start_ext_r = str_path.rfind(".") + 1;
		std::string name_str_r = str_path.substr(start_ext_r, str_path.size());
		std::string str_path_meta = str_path+".meta";
		if (!Find_in_Asset(str_path_meta.c_str())) {
			App->resources_mod->ImportFile(str_path.c_str());
		}
		else {
			App->resources_mod->ImportResources_Path_Usable(str_path_meta.c_str());
		}

	}
}

bool ModuleFileSystem_Engine::Find_in_Asset(const char* path) {
	for (std::experimental::filesystem::recursive_directory_iterator::value_type item : std::experimental::filesystem::recursive_directory_iterator(RootDirect_User->path)) {
		std::string str_path = item.path().string().c_str();
		if (str_path == path) {
			return true;
		}
	}

	return false;
}

bool ModuleFileSystem_Engine::Asset_Editor(const char* path, std::string * new_path, bool asset_editor) {

	std::string ptr = "-1";
	std::string dir_last = "-1";
	std::string dir_last_del = "-1";
	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN) {
		App->gui->Current_Dir = RootDirect_User->path.c_str();
	}

	if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_DOWN && App->gui->assets_dock_focus == true) {
		ImGui::OpenPopup("File Settings");

	}
	
	if (ImGui::BeginPopup("File Settings")) {
		if (ImGui::MenuItem("Create Directory"))
		{
			creating_dir = true;
		}
		/*if (ImGui::MenuItem("Delete Directory"))
		{
			deleting_dir = true;
		}*/
		ImGui::EndPopup();
	}

	if (creating_dir) {
		ImGui::Begin("Name Dir:",&creating_dir);
		if (ImGui::InputText("Directory:", directory_save, 64, ImGuiInputTextFlags_EnterReturnsTrue)) {
			Directory_* dir = nullptr;
			for (int i = 0; i < Directories_User_V.size(); i++) {
				if (Directories_User_V[i]->path == path) {
					dir = Directories_User_V[i];
					break;
				}
			}
			CreateDir(directory_save, Directory_Type::user_directory_type, dir);
			creating_dir = false;
		}
		ImGui::End();
	}

	if (deleting_dir) {
		ImGui::Begin("Delete Dir:", &creating_dir);
		IterateAllDirect_To_Save(path, &dir_last_del);
		if (dir_last_del != "-1") {
			std::experimental::filesystem::path path_t = "..\\Game\\Assets\\Scene";
			std::experimental::filesystem::remove_all(path_t);
			deleting_dir = false;
		}
		ImGui::End();
	}


	for (std::experimental::filesystem::directory_iterator::value_type item : std::experimental::filesystem::directory_iterator(path)) {
		std::string str_path = item.path().string().c_str();

		size_t end_name = str_path.rfind(".");
		size_t sart_name = str_path.rfind("\\") + 1;
		std::string name = str_path.substr(sart_name, end_name - sart_name);
		std::string ext_str= str_path.substr(end_name, str_path.size());
		if (item.status().type() == std::experimental::filesystem::file_type::directory) {
			ImGui::ImageButton_with_text((void*)Dir_Image, name.c_str(), ImVec2(45, 45), ImVec2(0, 0), ImVec2(1, -1), 0);
			ImGui::SameLine(0, 50);
			if (ImGui::IsItemClicked()) {
				if (ImGui::IsMouseDoubleClicked(0)) {
					App->gui->Current_Dir = str_path;
				}
			}
		}

		if (ext_str==".fbx" || ext_str == ".FBX") {
			ImGui::ImageButton_with_text((void*)Fbx_Image, name.c_str(), ImVec2(45, 45), ImVec2(0, 0), ImVec2(1, -1), 0);
			if(asset_editor)
			ImGui::SameLine(0, 50);
			if (ImGui::IsItemClicked()) {
				if (ImGui::IsMouseDoubleClicked(0)) {
					ptr = str_path.c_str();
				}
			}
		}

		if (ext_str == ".json" || ext_str == ".JSON") {
			ImGui::ImageButton_with_text((void*)Scene_Image, name.c_str(), ImVec2(45, 45), ImVec2(0, 0), ImVec2(1, -1), 0);
			if (asset_editor)
				ImGui::SameLine(0, 50);
			if (ImGui::IsItemClicked()) {
				if (ImGui::IsMouseDoubleClicked(0)) {
					ptr = str_path.c_str();
				}
			}
		}

		if (ext_str == ".png" || ext_str == ".PNG" || ext_str == ".tga" || ext_str == ".TGA") {
			ImGui::ImageButton_with_text((void*)Png_Image, name.c_str(), ImVec2(45, 45), ImVec2(0, 0), ImVec2(1, -1), 0);
			if(asset_editor)
			ImGui::SameLine(0, 50);
			if (ImGui::IsItemClicked()) {
				if (ImGui::IsMouseDoubleClicked(0)) {
					ptr = str_path.c_str();
				}
			}
		}

	}
	if (new_path != nullptr) {
		*new_path = ptr;
	}

	return true;
}