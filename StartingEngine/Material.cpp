#include "Material.h"






Material::Material(const char * path_text, const char* fbx, geometry_base_creating *base_text, GameObject * parent): Component(Component_Type_Enum::component_material_type,	parent, true)
{
		path_texture = path_text;
		texture_v = base_text;
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
}

void Material::Load(JSON_Object * root_object_scene)
{
}

void Material::CleanUp()
{
	delete this;
}


