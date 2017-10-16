#include "Material.h"






Material::Material(const char * path_text, const char* fbx, GameObject * parent): Component(Component_Type_Enum::component_material_type,
	parent, true)
{
	texture_v = App->assimp->ImportGeometry_Texture(fbx);
	for (int i = 0; i < texture_v.size(); i++) {

		App->assimp->LoadImage_devil(path_text, &texture_v[i]->id_image_devil);

		glGenBuffers(1, (GLuint*)&(texture_v[i]->id_texture));
		glBindBuffer(GL_ARRAY_BUFFER, texture_v[i]->id_texture);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) *texture_v[i]->num_vertices * 2, &texture_v[i]->textures_coord[0], GL_STATIC_DRAW); 

	}

}

void Material::Update()
{
	for (int i = 0; i < texture_v.size(); i++) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindTexture(GL_TEXTURE_2D, (texture_v[i]->id_image_devil));
	}
}

Material::~Material()
{
}

std::vector<material_base_geometry*> Material::GetMaterialVec()
{
	return texture_v;
}
