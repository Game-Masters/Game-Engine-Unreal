#include "Mesh.h"
#include"GameObject.h"

Mesh::Mesh(GameObject* parent, int uuid, const char* path, Material* m_text): Component(Component_Type_Enum::component_mesh_type,
	parent,true)
{
	general_fb_path = path;
	texture_mesh = m_text;
	uuid_mesh = uuid;
	mesh_r = App->resources_mod->Get(uuid_mesh);
	path_fbx = mesh_r->GetExportedFile();
	path_fbx_mesh = mesh_r->GetFile();
	float4x4 p = parent->GetMatrix_Trans();
	Copy_aabb_using = ((ResourceMesh*)mesh_r)->Copy_aabb;
	Copy_aabb_using.TransformAsAABB(p);
	Update_AABB();
	
}


Mesh::~Mesh()
{

}

void Mesh::Update_AABB() {

	this;
	Resource_Mesh_Base* m_t = ((ResourceMesh*)mesh_r)->Res_Mesh_Base;

	if (m_t->id_aabb != 0) {
		glDeleteBuffers(1, &(m_t->id_aabb));
	}
	if (m_t->id_index_aabb != 0) {
		glDeleteBuffers(1, &(m_t->id_index_aabb));
	}

	float vertex_Aabb[] = {
		Copy_aabb_using.CornerPoint(0).x,Copy_aabb_using.CornerPoint(0).y,Copy_aabb_using.CornerPoint(0).z,
		Copy_aabb_using.CornerPoint(1).x,Copy_aabb_using.CornerPoint(1).y,Copy_aabb_using.CornerPoint(1).z,
		Copy_aabb_using.CornerPoint(2).x,Copy_aabb_using.CornerPoint(2).y,Copy_aabb_using.CornerPoint(2).z,
		Copy_aabb_using.CornerPoint(3).x,Copy_aabb_using.CornerPoint(3).y,Copy_aabb_using.CornerPoint(3).z,
		Copy_aabb_using.CornerPoint(4).x,Copy_aabb_using.CornerPoint(4).y,Copy_aabb_using.CornerPoint(4).z,
		Copy_aabb_using.CornerPoint(5).x,Copy_aabb_using.CornerPoint(5).y,Copy_aabb_using.CornerPoint(5).z,
		Copy_aabb_using.CornerPoint(6).x,Copy_aabb_using.CornerPoint(6).y,Copy_aabb_using.CornerPoint(6).z,
		Copy_aabb_using.CornerPoint(7).x,Copy_aabb_using.CornerPoint(7).y,Copy_aabb_using.CornerPoint(7).z
	};
	memcpy(m_t->vertex_aabb, vertex_Aabb, sizeof(float) * 24);

	
	glGenBuffers(1, (GLuint*)&(m_t->id_aabb));
	glBindBuffer(GL_ARRAY_BUFFER, m_t->id_aabb);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8 * 3, &m_t->vertex_aabb[0], GL_STATIC_DRAW);

	glGenBuffers(1, (GLuint*)&(m_t->id_index_aabb));
	glBindBuffer(GL_ARRAY_BUFFER, m_t->id_index_aabb);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uint) * 8 * 3, &m_t->index_aabb[0], GL_STATIC_DRAW);

	
}

float4x4 Mesh::ParentHasTransform(float3 & position, float3 & scaling, Quat & rotation)
{
	float4x4 matrix;
	if (this->parent!=nullptr) {

		for (int i = 0; i < parent->Component_Vect.size(); i++) {

			if (parent->Component_Vect[i]->GetComponentType()== Component_Type_Enum::component_transform_type) {
				position = ((Transform*)parent->Component_Vect[i])->GetPosition();
				scaling = ((Transform*)parent->Component_Vect[i])->GetScale();
				rotation = ((Transform*)parent->Component_Vect[i])->GetRotation();
				matrix = ((Transform*)parent->Component_Vect[i])->GetMatrix();
			}
		}
	}
	
	return matrix;
}

void Mesh::PreUpdate()
{

	float4x4 p = parent->GetMatrix_Trans();
	Copy_aabb_using = ((ResourceMesh*)mesh_r)->Copy_aabb;
	Copy_aabb_using.TransformAsAABB(p);

}

void Mesh::Update()
{
	Update_AABB();
	App->renderer3D->Render_3D(this, uuid_mesh, texture_mesh);

}


PrimitiveTypes_Mesh Mesh::GetType() const
{
	return type;
}

void Mesh::CleanUp()
{
	delete this;
}

const char * Mesh::GetGeometryPath()
{
	return path_fbx.c_str();
}

Resource_Mesh_Base* Mesh::GetGeometryBaseMesh()
{
	return ((ResourceMesh*)mesh_r)->Res_Mesh_Base;
	
}

AABB Mesh::GetAABB() const
{
	return Copy_aabb_using;
}

void Mesh::SetMaterial(Material * mat)
{
	texture_mesh = mat;
}

Material * Mesh::GetMaterial() const
{
	return texture_mesh;
}

void Mesh::Save(JSON_Object * root_object_scene)
{
	JSON_Object* node;
	json_object_set_value(root_object_scene, "Mesh", json_value_init_object());
	node = json_object_get_object(root_object_scene, "Mesh");
	json_object_set_number(node, "UUID", this->UUID_comp);
	if (parent != nullptr) {
		json_object_set_number(node, "UUID_parent", this->UUID_parent_GO);
	}
	
	json_object_set_string(node, "General_Path_FBX", general_fb_path.c_str());
	json_object_set_string(node, "Resource Mesh exported", path_fbx.c_str());
	json_object_set_string(node, "Resource Mesh", path_fbx_mesh.c_str());

}

void Mesh::Load(JSON_Object * root_object_scene)
{
}
