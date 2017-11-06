#include "Material.h"






Material::Material(const char * path_text, const char* fbx, geometry_base_creating *base_text, GameObject * parent): Component(Component_Type_Enum::component_material_type,	parent, true)
{
	//texture_v = App->assimp->ImportGeometry_Texture(fbx);

		path_texture = path_text;
		texture_v = base_text;
		

		glGenBuffers(1, (GLuint*)&(texture_v->id_texture));
		glBindBuffer(GL_ARRAY_BUFFER, texture_v->id_texture);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) *texture_v->num_vertices * 2, &texture_v->textures_coord[0], GL_STATIC_DRAW); 



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


