#include "Parson_JSON.h"
#include"Application.h"



static int malloc_count;
static void *counted_malloc(size_t size);
static void counted_free(void *ptr);

Parson_JSON::Parson_JSON()
{
	json_set_allocation_functions(counted_malloc, counted_free);

	root_value = json_value_init_object();
	root_object = json_value_get_object(root_value);
	file_name = "config.json";
}


Parson_JSON::~Parson_JSON()
{
}

bool Parson_JSON::CleanUp() {
	free(root_value);
	free(root_object);
	return true;
}

bool Parson_JSON::Init()
{
	
	root_value = json_parse_file(file_name.c_str());
	if (root_value == NULL) {
		root_value = json_value_init_object();
		json_serialize_to_file(root_value, file_name.c_str());
	}
	else {
		root_object = json_value_get_object(root_value);
	}
	
	for (std::list<Module*>::reverse_iterator item = App->list_modules.rbegin(); item != App->list_modules.crend(); ++item) {
		if(json_object_get_object(root_object, (*item)->name.c_str())==NULL)
		json_object_set_value(root_object, (*item)->name.c_str(), json_value_init_object());
	}






	//How to acces node with JSON
	/*JSON_Value* value = json_object_get_value(root_object, "window");
	const char* string = json_value_get_string(value);*/
	
	//REMEMBER TO MAKE FREE

	/*json_value_free(root_value);
	json_free_serialized_string(serialized_string);*/



	return true;
}

bool Parson_JSON::Load()
{
	char* serialized_string = json_serialize_to_string_pretty(root_value);
	//root_object
	JSON_Object* node;


	for (std::list<Module*>::reverse_iterator item = App->list_modules.rbegin(); item != App->list_modules.crend(); ++item) {
		node = json_object_get_object(root_object, (*item)->name.c_str());
		(*item)->LoadConfig(node);
	}
	free(serialized_string);
	return true;
}

bool Parson_JSON::Save()
{

	JSON_Object* node;

	for (std::list<Module*>::reverse_iterator item = App->list_modules.rbegin(); item != App->list_modules.crend(); ++item) {
		node = json_object_get_object(root_object, (*item)->name.c_str());
		(*item)->SaveConfig(node);
	}
	char* serialized_string = json_serialize_to_string_pretty(root_value);
	json_serialize_to_file(root_value, file_name.c_str());

	free(node);
	return true;
}





static void *counted_malloc(size_t size) {
	void *res = malloc(size);
	if (res != NULL) {
		malloc_count++;
	}
	return res;
}

static void counted_free(void *ptr) {
	if (ptr != NULL) {
		malloc_count--;
	}
	free(ptr);
}