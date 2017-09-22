#include "ModuleParson_JSON.h"
#include"Application.h"



static int malloc_count;
static void *counted_malloc(size_t size);
static void counted_free(void *ptr);

ModuleParson_JSON::ModuleParson_JSON()
{
}


ModuleParson_JSON::~ModuleParson_JSON()
{
}

bool ModuleParson_JSON::Start()
{
	JSON_Value *json_test;
	
	json_set_allocation_functions(counted_malloc, counted_free);
	
	//Example to show that JSON WORKS

	JSON_Value *root_value = json_value_init_object();
	JSON_Object *root_object = json_value_get_object(root_value);
	char *serialized_string = NULL;
	const char *name = NULL;

	for (std::list<Module*>::reverse_iterator item = App->list_modules.rbegin(); item != App->list_modules.crend(); ++item) {
		
			json_object_set_string(root_object, (*item)->name.c_str(), "miquel");
	}

	serialized_string = json_serialize_to_string_pretty(root_value);
	puts(serialized_string);


	json_serialize_to_file(root_value, "test_json.json");
	JSON_Value* value = json_object_get_value(root_object, "window");
	const char* string = json_value_get_string(value);

	json_value_free(root_value);
	json_free_serialized_string(serialized_string);



	



	return true;
}

update_status ModuleParson_JSON::Update(float dt)
{
	return update_status::UPDATE_CONTINUE;
}

update_status ModuleParson_JSON::PostUpdate(float dt)
{
	return update_status::UPDATE_CONTINUE;
}

bool ModuleParson_JSON::Gui_Engine_Modules(float dt)
{
	return true;
}

bool ModuleParson_JSON::CleanUp()
{
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