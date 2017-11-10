#include "Material.h"






Material::Material(int UUID, GameObject * parent): Component(Component_Type_Enum::component_material_type,	parent, true)
{

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


