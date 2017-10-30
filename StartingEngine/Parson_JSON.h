#ifndef __Parson_JSON_H__
#define __Parson_JSON_H__

#include"Module.h"
#include"JSON\parson.h"
class Parson_JSON
{
public:
	Parson_JSON();
	~Parson_JSON();

	bool Init();
	bool Load();
	bool Save();
	bool CleanUp();
	void Create_JSON_DOC(JSON_Value **root_value_scene, JSON_Object **root_object_scene, const char* namefile);
public:
	JSON_Value *root_value = nullptr;
	JSON_Object *root_object= nullptr;
	char *serialized_string = NULL;
	std::string file_name;

};
#endif
