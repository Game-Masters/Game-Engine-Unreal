#include "ModuleFileSystem_Engine.h"
#include<filesystem>
#include <iostream>
#include<fstream>

bool ModuleFileSystem_Engine::Start()
{
	RootDirect_User = nullptr;
	RootDirect_User = CreateDir("Assets", Directory_Type::user_directory_type);
	Mesh_User = CreateDir("Mesh", Directory_Type::user_directory_type, RootDirect_User);
	Material_User = CreateDir("Material", Directory_Type::user_directory_type, RootDirect_User);



	RootDirect_Engine = nullptr;
	RootDirect_Engine = CreateDir("Library", Directory_Type::engine_directory_type, nullptr,false);
	Mesh_Engine = CreateDir("Mesh", Directory_Type::engine_directory_type, RootDirect_Engine,false);
	Material_Engine = CreateDir("Material", Directory_Type::engine_directory_type, RootDirect_Engine,false);



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
		temp->path = "..//Game//";temp->path += name;
		temp->parent = nullptr;
		CreateDirectory(temp->path.c_str(), false);
		if (visible == false) {
			SetFileAttributes(temp->path.c_str(), FILE_ATTRIBUTE_HIDDEN);
		}
	}
	else {
		if (IterateChild_Exsist(Root_node_temp, name)==false && parent!= nullptr) {
			temp->name = name;
			temp->parent = parent;
			std::string path_create = parent->path + "//" + name;
			temp->path = path_create;
			CreateDirectory(path_create.c_str(),false);
			if (visible == false) {
				SetFileAttributes(temp->path.c_str(), FILE_ATTRIBUTE_HIDDEN);
			}
			parent->dir_cont_v.push_back(temp);
		}

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

void ModuleFileSystem_Engine::ChangeFormat_File(const char * path, const char * n_format, std::string *new_path, Directory_ *Parent)
{
	std::string full_path_complete = path;
	std::size_t pos_to_find = full_path_complete.rfind("\\");
	pos_to_find += 1;
	std::size_t pos_to_find_end = full_path_complete.rfind(".");
	std::size_t diff = pos_to_find_end - pos_to_find;
	std::string Imp_Path = full_path_complete.substr(pos_to_find, diff);

	std::string parent_path = Parent->path;
	std::string final_path = parent_path + "//" + Imp_Path;
	std::string n_form_std = n_format;
	final_path += "." + n_form_std;
	*new_path = final_path.c_str();
}
