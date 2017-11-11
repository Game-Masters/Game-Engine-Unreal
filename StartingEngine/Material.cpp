#include "Material.h"






Material::Material(int UUID, GameObject * parent): Component(Component_Type_Enum::component_material_type,	parent, true)
{
	UUID_mat = UUID;
	Resource* res =	App->resources_mod->Get(UUID_mat);
	path_texture_exported = res->GetExportedFile();
	path_texture = res->GetFile();



}

void Material::Update()
{

}

Material::~Material()
{
}



const char * Material::GetPathMaterial()
{
	return path_texture.c_str();
}

void Material::Save(JSON_Object * root_object_scene)
{

	JSON_Object* node;
	json_object_set_value(root_object_scene, "Mesh", json_value_init_object());
	node = json_object_get_object(root_object_scene, "Mesh");
	json_object_set_number(node, "UUID", this->UUID_comp);
	if (parent != nullptr) {
		json_object_set_number(node, "UUID_parent", this->UUID_parent_GO);
	}
	json_object_set_string(node, "Resource Mesh", path_texture.c_str());

}

void Material::Load(JSON_Object * root_object_scene)
{
}

void Material::CleanUp()
{
	delete this;
}


