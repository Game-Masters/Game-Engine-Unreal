#include "Mesh.h"
#include"GameObject.h"

Mesh::Mesh(GameObject* parent, geometry_base_creating* vec_mesh, const char* path, Material* m_text): Component(Component_Type_Enum::component_mesh_type,
	parent,true)
{
	path_fbx = path;
	texture_mesh = m_text;

	mesh_v = vec_mesh;

	if (mesh_v->vertices != nullptr && mesh_v->indices!=nullptr) {
		glGenBuffers(1, (GLuint*)&(mesh_v->id_vertices));
		glBindBuffer(GL_ARRAY_BUFFER, mesh_v->id_vertices);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) *mesh_v->num_vertices * 3, &mesh_v->vertices[0], GL_STATIC_DRAW);

		// Buffer for indices
		glGenBuffers(1, (GLuint*)&(mesh_v->id_indices));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_v->id_indices);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * mesh_v->num_indices, &mesh_v->indices[0], GL_STATIC_DRAW);
	}
	Copy_aabb = mesh_v->BoundBox;
	this->mesh_v->vertex_aabb = new float[8 * 3];
	this->mesh_v->index_aabb = new uint[8 * 3];
	uint indices[] =
	{
		0,2,
		0,4,
		0,1,
		7,6,
		7,3,
		7,5,
		5,1,
		5,4,
		2,3,
		2,6,
		6,4,
		3,1
	};
	memcpy(this->mesh_v->index_aabb, indices, sizeof(uint) * 24);
	Update_AABB();
	
}


Mesh::~Mesh()
{
	delete mesh_v;
}

void Mesh::Update_AABB() {

	if (mesh_v->id_aabb != 0) {
		glDeleteBuffers(1, &mesh_v->id_aabb);
	}
	if (mesh_v->id_index_aabb != 0) {
		glDeleteBuffers(1, &mesh_v->id_index_aabb);
	}



	float vertex_Aabb[] = {
		Copy_aabb.CornerPoint(0).x,Copy_aabb.CornerPoint(0).y,Copy_aabb.CornerPoint(0).z,
		Copy_aabb.CornerPoint(1).x,Copy_aabb.CornerPoint(1).y,Copy_aabb.CornerPoint(1).z,
		Copy_aabb.CornerPoint(2).x,Copy_aabb.CornerPoint(2).y,Copy_aabb.CornerPoint(2).z,
		Copy_aabb.CornerPoint(3).x,Copy_aabb.CornerPoint(3).y,Copy_aabb.CornerPoint(3).z,
		Copy_aabb.CornerPoint(4).x,Copy_aabb.CornerPoint(4).y,Copy_aabb.CornerPoint(4).z,
		Copy_aabb.CornerPoint(5).x,Copy_aabb.CornerPoint(5).y,Copy_aabb.CornerPoint(5).z,
		Copy_aabb.CornerPoint(6).x,Copy_aabb.CornerPoint(6).y,Copy_aabb.CornerPoint(6).z,
		Copy_aabb.CornerPoint(7).x,Copy_aabb.CornerPoint(7).y,Copy_aabb.CornerPoint(7).z
	};
	memcpy(this->mesh_v->vertex_aabb, vertex_Aabb, sizeof(float) * 24);


	glGenBuffers(1, (GLuint*)&(mesh_v->id_aabb));
	glBindBuffer(GL_ARRAY_BUFFER, mesh_v->id_aabb);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8 * 3, &this->mesh_v->vertex_aabb[0], GL_STATIC_DRAW);

	glGenBuffers(1, (GLuint*)&(mesh_v->id_index_aabb));
	glBindBuffer(GL_ARRAY_BUFFER, mesh_v->id_index_aabb);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uint) * 8 * 3, &mesh_v->index_aabb[0], GL_STATIC_DRAW);
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

void Mesh::Update()
{

	App->renderer3D->Render_3D(this, mesh_v, texture_mesh);	
	float4x4 p = parent->GetMatrix_Trans();
	Copy_aabb= mesh_v->BoundBox;
	Copy_aabb.TransformAsAABB(p);

	Update_AABB();
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

geometry_base_creating * Mesh::GetGeometryBaseMesh()
{
	return mesh_v;
	
}

AABB Mesh::GetAABB() const
{
	return this->Copy_aabb;
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
	json_object_set_string(node, "Path FBX", this->path_fbx.c_str());

}

void Mesh::Load(JSON_Object * root_object_scene)
{
}
