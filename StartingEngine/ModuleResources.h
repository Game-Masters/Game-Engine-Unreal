#pragma once
#include "Module.h"
#include<map>

class Resource;


enum Resources_Type {
	mesh,
	texture,
	scene,
	unknown_r
};

class ModuleResources :
	public Module
{
public:
	ModuleResources();
	~ModuleResources();
	update_status Update(float dt);
	int Find_UserRes(const char* file_in_assets) const;
	int Find_EngineRes(const char* file_in_assets) const;
	int ImportFile(const char* new_file_in_assets, bool force = false);
	int GenerateNewUID();
	//const Resource* Get(int uid) const;
	int Create_New_resource_Text(std::string path_in_engine, const char* new_file_in_assets, int uid_r, Resources_Type type);
	Resources_Type DetectFiles_Type(const char* new_file_in_assets);
	Resource* Get(int uid);
	Resource* CreateNewResource(Resources_Type type, int force_uid = 0);
	bool AddResources(Resource* n_res);
private:

	int last_uid = 1;
	std::map<int, Resource*> resources;

};

class Resource{
public:


	Resource(int uid, Resources_Type type);
	virtual ~Resource();
	Resources_Type GetType() const;
	int GetUID() const;
	const char* GetFile() const;
	const char* GetExportedFile() const;
	bool IsLoadedToMemory() const;
	virtual bool LoadToMemory();
	void Set_New_Resource_Files(std::string file, std::string exported_file);
	uint CountReferences() const;
//LOAD SAVE?


protected:
	int uid = 0;
	std::string file;
	std::string exported_file;
	Resources_Type type = Resources_Type::unknown_r;
	uint loaded = 0;



};

