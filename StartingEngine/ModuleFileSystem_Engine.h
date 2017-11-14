#pragma once
#include "Module.h"
#include"Glew\include\glew.h"
#include<vector>
#include<string>

class Directory_;

enum File_type {
	fbx_type,
	png_type,
	other_type
};

enum Directory_Type {
	user_directory_type,
	engine_directory_type
};

class ModuleFileSystem_Engine :
	public Module
{
public:
	bool Init();

	bool Start();
	bool CleanUp();
	Directory_* CreateDir(const char* name, Directory_Type type, Directory_* parent=nullptr, bool visible=true);
	bool IterateChild_Exsist(Directory_ *temp, const char* name);
	int LoadFile(const char* path, char** buffer);
	bool SaveFile(const char* path, char* buffer, uint size, Directory_* parent=nullptr);
	ModuleFileSystem_Engine();
	~ModuleFileSystem_Engine();
	bool SerchInDirectorySystem(const char* path, File_type type);
	void ChangeFormat_File(const char* path, const char* n_format, std::string *new_path, Directory_ *Parent);
	void IterateAllDirect_To_Save(const char * path_dir, std::string * new_path);
	void IterateAllDirect(const char* path_dir, std::string *new_path);
	void Asset_User_File_Iteration();
	bool Find_in_Asset(const char* path);
	bool Asset_Editor(const char* path, std::string * new_path=nullptr, bool asset_editor=true);
	
public:
	Directory_ *RootDirect_User=nullptr;
	Directory_ *Mesh_User = nullptr;
	Directory_ *Material_User= nullptr;

	std::vector<Directory_*>Directories_User_V;

	Directory_ *RootDirect_Engine = nullptr;
	Directory_ *Mesh_Engine = nullptr;
	Directory_ *Material_Engine = nullptr;

	GLuint Dir_Image;
	GLuint Png_Image;
	GLuint Fbx_Image;

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