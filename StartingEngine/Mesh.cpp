#include "Mesh.h"
#include"GameObject.h"

Mesh::Mesh(GameObject* parent, geometry_base_creating* vec_mesh, Material* m_text): Component(Component_Type_Enum::component_mesh_type,
	parent,true)
{
	
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


	this->mesh_v->vertex_aabb = new float[8 * 3];
	
	float vertex_Aabb[] = {
		this->mesh_v->BoundBox.CornerPoint(0).x,this->mesh_v->BoundBox.CornerPoint(0).y,this->mesh_v->BoundBox.CornerPoint(0).z,
		this->mesh_v->BoundBox.CornerPoint(1).x,this->mesh_v->BoundBox.CornerPoint(1).y,this->mesh_v->BoundBox.CornerPoint(1).z,
		this->mesh_v->BoundBox.CornerPoint(2).x,this->mesh_v->BoundBox.CornerPoint(2).y,this->mesh_v->BoundBox.CornerPoint(2).z,
		this->mesh_v->BoundBox.CornerPoint(3).x,this->mesh_v->BoundBox.CornerPoint(3).y,this->mesh_v->BoundBox.CornerPoint(3).z,
		this->mesh_v->BoundBox.CornerPoint(4).x,this->mesh_v->BoundBox.CornerPoint(4).y,this->mesh_v->BoundBox.CornerPoint(4).z,
		this->mesh_v->BoundBox.CornerPoint(5).x,this->mesh_v->BoundBox.CornerPoint(5).y,this->mesh_v->BoundBox.CornerPoint(5).z,
		this->mesh_v->BoundBox.CornerPoint(6).x,this->mesh_v->BoundBox.CornerPoint(6).y,this->mesh_v->BoundBox.CornerPoint(6).z,
		this->mesh_v->BoundBox.CornerPoint(7).x,this->mesh_v->BoundBox.CornerPoint(7).y,this->mesh_v->BoundBox.CornerPoint(7).z
	};
	memcpy(this->mesh_v->vertex_aabb, vertex_Aabb, sizeof(float) * 24);


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

		glGenBuffers(1, (GLuint*)&(mesh_v->id_aabb));
		glBindBuffer(GL_ARRAY_BUFFER, mesh_v->id_aabb);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) *8 * 3, &this->mesh_v->vertex_aabb[0], GL_STATIC_DRAW);

		glGenBuffers(1, (GLuint*)&(mesh_v->id_index_aabb));
		glBindBuffer(GL_ARRAY_BUFFER, mesh_v->id_index_aabb);
		glBufferData(GL_ARRAY_BUFFER, sizeof(uint) * 8 * 3, &mesh_v->index_aabb[0], GL_STATIC_DRAW);
		



}


Mesh::~Mesh()
{
}


void Mesh::ParentHasTransform(float3 & position, float3 & scaling, Quat & rotation)
{

	if (this->parent!=nullptr) {

		for (int i = 0; i < parent->Component_Vect.size(); i++) {

			if (parent->Component_Vect[i]->GetComponentType()== Component_Type_Enum::component_transform_type) {
				position = ((Transform*)parent->Component_Vect[i])->GetPosition();
				scaling = ((Transform*)parent->Component_Vect[i])->GetScale();
				rotation = ((Transform*)parent->Component_Vect[i])->GetRotation();
			}
		}
	}

}

void Mesh::Update()
{


	if (App->gui->inspection_node == this->parent) {
		glPushMatrix();
		float3 position;
		float3 scale;
		Quat rotation;
		ParentHasTransform(position, scale, rotation);
		float4x4 transform_mesh = float4x4::FromTRS(position, rotation, scale);
		transform_mesh.Transpose();
		GLfloat trans_point[16] = {
			transform_mesh[0][0],transform_mesh[0][1],transform_mesh[0][2],transform_mesh[0][3],
			transform_mesh[1][0],transform_mesh[1][1],transform_mesh[1][2],transform_mesh[1][3],
			transform_mesh[2][0],transform_mesh[2][1],transform_mesh[2][2],transform_mesh[2][3],
			transform_mesh[3][0],transform_mesh[3][1],transform_mesh[3][2],transform_mesh[3][3]
		};
		//glLoadMatrixf(trans_point);
		glMultMatrixf(trans_point);
		glLineWidth(2.0f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glEnableClientState(GL_VERTEX_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER, mesh_v->id_aabb);
		glVertexPointer(3, GL_FLOAT, 0, NULL);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_v->id_index_aabb);
		glDrawElements(GL_LINES, 8 * 3, GL_UNSIGNED_INT, NULL);
		glLineWidth(1.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glPopMatrix();
	}



		if (mesh_v->num_indices > 0 && mesh_v->num_vertices > 0) {
			if (texture_mesh != nullptr) {
				material_base_geometry* temp_text_vec;
				temp_text_vec = texture_mesh->GetMaterialVec();
				if (temp_text_vec != nullptr) {
					glEnable(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D, 0);
					glBindTexture(GL_TEXTURE_2D, (temp_text_vec->id_image_devil));

					if (temp_text_vec->textures_coord != nullptr) {

						glEnableClientState(GL_TEXTURE_COORD_ARRAY);
						glBindBuffer(GL_ARRAY_BUFFER, temp_text_vec->id_texture);
						glTexCoordPointer(2, GL_FLOAT, 0, NULL);

					}
				}
			}

			if (App->renderer3D->debugnormals == true && mesh_v->normals != nullptr) {
				for (uint k = 0; k < mesh_v->num_vertices * 3; k += 3)
				{
					glLineWidth(2.0f);
					glColor3f(1.0f, 0.0f, 0.0f);

					glBegin(GL_LINES);
					glVertex3f(mesh_v->vertices[k], mesh_v->vertices[k + 1], mesh_v->vertices[k + 2]);
					glVertex3f(mesh_v->vertices[k] + mesh_v->normals[k], mesh_v->vertices[k + 1] + mesh_v->normals[k + 1], mesh_v->vertices[k + 2] + mesh_v->normals[k + 2]);
					glEnd();

					glLineWidth(1.0f);
					glColor3f(1.0f, 1.0f, 1.0f);
				}
			}
			
			
			glPushMatrix();
			float3 position;
			float3 scale;
			Quat rotation;
			ParentHasTransform(position, scale, rotation);
			float4x4 transform_mesh = float4x4::FromTRS(position, rotation, scale);
			transform_mesh.Transpose();
			GLfloat trans_point[16] = {
				transform_mesh[0][0],transform_mesh[0][1],transform_mesh[0][2],transform_mesh[0][3],
				transform_mesh[1][0],transform_mesh[1][1],transform_mesh[1][2],transform_mesh[1][3],
				transform_mesh[2][0],transform_mesh[2][1],transform_mesh[2][2],transform_mesh[2][3],
				transform_mesh[3][0],transform_mesh[3][1],transform_mesh[3][2],transform_mesh[3][3]
			};			
			//glLoadMatrixf(trans_point);
			glMultMatrixf(trans_point);
			if (mesh_v->vertices != nullptr && mesh_v->indices != nullptr) {
				glEnableClientState(GL_VERTEX_ARRAY);
				glBindBuffer(GL_ARRAY_BUFFER, mesh_v->id_vertices);
				glVertexPointer(3, GL_FLOAT, 0, NULL);

				glEnableClientState(GL_ELEMENT_ARRAY_BUFFER);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_v->id_indices);
				glDrawElements(GL_TRIANGLES, mesh_v->num_indices, GL_UNSIGNED_INT, NULL);
			}
			glPopMatrix();
			glBindTexture(GL_TEXTURE_2D, 0);
			
			

		}
		else {
			LOG("Impossible to draw the mesh");
		}

	}
	




PrimitiveTypes_Mesh Mesh::GetType() const
{
	return type;
}

const char * Mesh::GetGeometryPath()
{
	return path_fbx.c_str();
}
