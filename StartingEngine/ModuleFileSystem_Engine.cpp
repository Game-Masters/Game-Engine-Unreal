#include "ModuleFileSystem_Engine.h"
#include<filesystem>
#include <iostream>
#include<fstream>

bool ModuleFileSystem_Engine::Start()
{
	RootDirect = nullptr;
	RootDirect = CreateDir("Assets");
	Mesh = CreateDir("Mesh", RootDirect);
	Material= CreateDir("Material", RootDirect);
	return true;
}

bool ModuleFileSystem_Engine::CleanUp()
{
	return true;
}

Directory_* ModuleFileSystem_Engine::CreateDir(const char * name, Directory_ * parent)
{

	Directory_ *temp = new Directory_();
	if (RootDirect == nullptr) {
		temp->name = name;
		temp->path = "..//Game//";temp->path += name;
		temp->parent = nullptr;
		CreateDirectory(temp->path.c_str(), false);
	}
	else {
		if (IterateChild_Exsist(RootDirect, name)==false && parent!= nullptr) {
			temp->name = name;
			temp->parent = parent;
			std::string path_create = parent->path + "//" + name;
			CreateDirectory(path_create.c_str(),false);
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

bool ModuleFileSystem_Engine::LoadFile(const char * path, char ** buffer)
{
	bool ret = false;
	std::ifstream file_stream (path, std::ifstream::binary);
	
	if (file_stream.bad()) {
		LOG("The file %s cannot be readed", path);
	}
	else {
		if (file_stream) {
			//Read file explanation http://www.cplusplus.com/reference/istream/istream/read/
			// get length of file:
			file_stream.seekg(0, file_stream.end);
			int length_file = file_stream.tellg();
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
	return ret;
}

bool ModuleFileSystem_Engine::SaveFile(const char * path, char ** buffer, uint size)
{
	//Save file documentation http://www.cplusplus.com/reference/ostream/ostream/write/
	bool ret = false;
	std::ofstream outfile(path, std::ofstream::binary);

	if (outfile.good()) {
		// write to outfile
		outfile.write(*buffer, size);
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
