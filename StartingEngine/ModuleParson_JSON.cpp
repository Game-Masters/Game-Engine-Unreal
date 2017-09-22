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

	const char *name = NULL;
	JSON_Value *user_data = nullptr;
	user_data = json_value_init_object();
	json_object_set_string(json_object(user_data), "name", "MIQUEL ES UN GOD DEL UNIVERS");
	json_object_set_string(json_object(user_data), "paco", "MIQUEL ES UN GOD DEL UNIVERS");


	char *serialized_string = NULL;
	json_object_set_string(json_object(user_data), "name", "John Smith");
	json_object_set_number(json_object(user_data), "age", 25);
	json_object_dotset_string(json_object(user_data), "address.city", "Cupertino");
	json_object_dotset_value(json_object(user_data), "contact.emails", json_parse_string("[\"email@example.com\",\"email2@example.com\"]"));


	
	json_serialize_to_file(user_data, "user_data.json");

	//json_value_free(schema);
	json_value_free(user_data);
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