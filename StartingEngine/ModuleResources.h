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
	bool Start();
	bool CleanUp();
	update_status Update(float dt);
	int Find_UserRes(const char* file_in_assets) const;
	int Find_EngineRes(const char* file_in_assets) const;
	void ImportResources_Path_Usable(const char* new_file_in_assets);
	int ImportFile(const char* new_file_in_assets, bool force = false);
	int GenerateNewUID() const;
	//const Resource* Get(int uid) const;
	int Create_New_resource_Text(std::string path_in_engine, const char* new_file_in_assets, int uid_r, Resources_Type type);
	Resources_Type DetectFiles_Type(const char* new_file_in_assets);
	Resource* Get(int uid)const;
	Resource* CreateNewResource(Resources_Type type, int force_uid = 0);
	bool AddResources(Resource* n_res);
	//void SelectResourceUpdate(Resource* res);
private:
	Timer tim_check_Assets;
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
	void CreateMeta();
	virtual bool ReadMetaModif();
	void Set_New_Resource_Files(std::string file, std::string exported_file);
	uint CountReferences() const;
	uint GetLoadedNum()const;
	void SetLastTimeModf(double time);
	virtual void Update_Resource();
	virtual void DeleteRes();


protected:
	int uid = 0;
	std::string file;
	std::string exported_file;
	double time_from_last_modify = 0;
	Resources_Type type = Resources_Type::unknown_r;
	uint loaded = 0;
	JSON_Value* val_doc;
	JSON_Object* obj_doc;


};

