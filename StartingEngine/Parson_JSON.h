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

public:
	JSON_Value *root_value = nullptr;
	JSON_Object *root_object= nullptr;
	char *serialized_string = NULL;
	std::string file_name;

};
#endif
