#include "Mesh.h"
#include"GameObject.h"

Mesh::Mesh(GameObject* parent, const char* str, Material* m_text): Component(Component_Type_Enum::component_mesh_type,
	parent,true)
{
	path_fbx = str;
	texture_mesh = m_text;
	mesh_v = App->assimp->ImportGeometry(str);


	for (int i = 0; i < mesh_v.size(); i++) {
		glGenBuffers(1, (GLuint*)&(mesh_v[i]->id_vertices));
		glBindBuffer(GL_ARRAY_BUFFER, mesh_v[i]->id_vertices);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) *mesh_v[i]->num_vertices * 3, &mesh_v[i]->vertices[0], GL_STATIC_DRAW);

		// Buffer for indices
		glGenBuffers(1, (GLuint*)&(mesh_v[i]->id_indices));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_v[i]->id_indices);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * mesh_v[i]->num_indices, &mesh_v[i]->indices[0], GL_STATIC_DRAW);

	}

}

Mesh::~Mesh()
{
}


void Mesh::Update()
{
	for (int i = 0; i < mesh_v.size(); i++) {
		if (mesh_v[i]->num_indices > 0 && mesh_v[i]->num_vertices > 0) {
			if (texture_mesh != nullptr) {
				std::vector<material_base_geometry*> temp_text_vec;
				temp_text_vec = texture_mesh->GetMaterialVec();
				if (temp_text_vec[i] != nullptr) {
					glEnable(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D, 0);
					glBindTexture(GL_TEXTURE_2D, (temp_text_vec[i]->id_image_devil));

					if (temp_text_vec[i]->textures_coord != nullptr) {

						glEnableClientState(GL_TEXTURE_COORD_ARRAY);
						glBindBuffer(GL_ARRAY_BUFFER, temp_text_vec[i]->id_texture);
						glTexCoordPointer(2, GL_FLOAT, 0, NULL);

					}
				}
			}

			if (App->renderer3D->debugnormals == true && mesh_v[i]->normals != nullptr) {
				for (uint k = 0; k < mesh_v[i]->num_vertices * 3; k += 3)
				{
					glLineWidth(2.0f);
					glColor3f(1.0f, 0.0f, 0.0f);

					glBegin(GL_LINES);
					glVertex3f(mesh_v[i]->vertices[k], mesh_v[i]->vertices[k + 1], mesh_v[i]->vertices[k + 2]);
					glVertex3f(mesh_v[i]->vertices[k] + mesh_v[i]->normals[k], mesh_v[i]->vertices[k + 1] + mesh_v[i]->normals[k + 1], mesh_v[i]->vertices[k + 2] + mesh_v[i]->normals[k + 2]);
					glEnd();

					glLineWidth(1.0f);
					glColor3f(1.0f, 1.0f, 1.0f);
				}
			}
			
			glEnableClientState(GL_VERTEX_ARRAY);
			glBindBuffer(GL_ARRAY_BUFFER, mesh_v[i]->id_vertices);
			glVertexPointer(3, GL_FLOAT, 0, NULL);

			glEnableClientState(GL_ELEMENT_ARRAY_BUFFER);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_v[i]->id_indices);
			glDrawElements(GL_TRIANGLES, mesh_v[i]->num_indices, GL_UNSIGNED_INT, NULL);
			glBindTexture(GL_TEXTURE_2D, 0);

			

		}
		else {
			LOG("Impossible to draw the mesh");
		}

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
