#include"Application.h"
#include "Geometry.h"



Geometry_Manager::Geometry_Manager(PrimitiveTypes prim_type) : type(prim_type)
{
}

Geometry_Manager::Geometry_Manager(const Geometry_Manager & con_copy) : color(con_copy.color), type(con_copy.type), mesh(con_copy.mesh), geometry_div(con_copy.geometry_div)
{

}

Geometry_Manager::~Geometry_Manager()
{
}

void Geometry_Manager::Initialize()
{
	// Buffer for vertex
	glGenBuffers(1, (GLuint*)&(mesh.id_vertices));
	glBindBuffer(GL_ARRAY_BUFFER, mesh.id_vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) *mesh.num_vertices * 3, &mesh.vertices[0], GL_STATIC_DRAW);

	// Buffer for indices
	glGenBuffers(1, (GLuint*)&(mesh.id_indices));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.id_indices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * mesh.num_indices, &mesh.indices[0], GL_STATIC_DRAW);

	/*if (mesh.normals!=nullptr) {
		glGenBuffers(1, (GLuint*)&(mesh.id_normales));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.id_normales);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) *mesh.num_vertices * 3, &mesh.normals[0], GL_STATIC_DRAW);
	}
	


	if (mesh.colors != nullptr) {
		glGenBuffers(1, (GLuint*)&(mesh.id_colors));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.id_colors);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) *mesh.num_vertices * 3, &mesh.colors[0], GL_STATIC_DRAW);
	}
	*/
	

	
	
	if (mesh.textures_coord != nullptr) {


	App->assimp->LoadImage_devil(mesh.texture_str.c_str(), &mesh.id_image_devil);

	glGenBuffers(1, (GLuint*)&(mesh.id_texture));
	glBindBuffer(GL_ARRAY_BUFFER, mesh.id_texture);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) *mesh.num_vertices*2, &mesh.textures_coord[0], GL_STATIC_DRAW);
	
	

	}

	

	
}

void Geometry_Manager::Draw()
{
	if (mesh.num_indices>0 && mesh.num_vertices>0) {



		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindTexture(GL_TEXTURE_2D, mesh.id_image_devil);

		
		
		if (App->renderer3D->debugnormals == true && mesh.normals != nullptr) {
			for (uint i = 0; i < mesh.num_vertices * 3; i += 3)
			{
				glLineWidth(2.0f);
				glColor3f(1.0f, 0.0f, 0.0f);

				glBegin(GL_LINES);
				glVertex3f(mesh.vertices[i], mesh.vertices[i + 1], mesh.vertices[i + 2]);
				glVertex3f(mesh.vertices[i] + mesh.normals[i], mesh.vertices[i + 1] + mesh.normals[i + 1], mesh.vertices[i + 2] + mesh.normals[i + 2]);
				glEnd();

				glLineWidth(1.0f);
				glColor3f(1.0f, 1.0f, 1.0f);
			}
		}

		


		if (mesh.textures_coord != nullptr) {

			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBuffer(GL_ARRAY_BUFFER, mesh.id_texture);
			glTexCoordPointer(2, GL_FLOAT,0, NULL);
			
		}

	//	
		
		glEnableClientState(GL_VERTEX_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER, mesh.id_vertices);
		glVertexPointer(3, GL_FLOAT, 0, NULL);

		glEnableClientState(GL_ELEMENT_ARRAY_BUFFER);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.id_indices);
		glDrawElements(GL_TRIANGLES, mesh.num_indices, GL_UNSIGNED_INT, NULL);
		glBindTexture(GL_TEXTURE_2D, 0);



	}
	else {
		LOG("Impossible to draw the mesh");
	}
}

void Geometry_Manager::SetColor(const Color & oth_color)
{
	color = oth_color;
}

/*void Geometry_Manager::SetType(PrimitiveTypes oth_type)
{
type = oth_type;
}

void Geometry_Manager::SetDivisions(uint divis)
{
geometry_div = divis;
}*/

Color Geometry_Manager::GetColor() const
{
	return color;
}

PrimitiveTypes Geometry_Manager::GetType() const
{
	return type;
}


