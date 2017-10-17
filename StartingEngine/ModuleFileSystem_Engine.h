#pragma once
#include "Module.h"
#include<vector>
#include<string>
class Directory_;

class ModuleFileSystem_Engine :
	public Module
{
public:
	bool Start();
	bool CleanUp();
	Directory_* CreateDir(const char* name, Directory_* parent=nullptr);
	bool IterateChild_Exsist(Directory_ *temp, const char* name);
	int LoadFile(const char* path, char** buffer);
	bool SaveFile(const char* path, char* buffer, uint size, Directory_* parent=nullptr);
	ModuleFileSystem_Engine();
	~ModuleFileSystem_Engine();
	void ChangeFormat_File(const char* path, const char* n_format, std::string *new_path, Directory_ *Parent);
public:
	Directory_ *RootDirect=nullptr;
	Directory_ *Mesh = nullptr;
	Directory_ *Material = nullptr;

};

class File_data {

public:
	File_data() {
	};
	~File_data() {
	};

public:
	Directory_* parent;
	std::string name;
	char** buffer=nullptr;

};

class Directory_ {
public:
	Directory_() {
	};
	~Directory_() {
	};
public:
	Directory_* parent;
	std::string name;
	std::string path;
	std::vector<File_data> files_cont_v;
	std::vector<Directory_*> dir_cont_v;
};