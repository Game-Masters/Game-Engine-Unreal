#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"





ModuleSceneIntro::ModuleSceneIntro(bool start_enabled) : Module(start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	GLfloat LightModelAmbient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LightModelAmbient);
	lights[0].ref = GL_LIGHT0;
	lights[0].ambient.Set(0.5f, 0.5f, 0.5f, 1.0f);
	lights[0].diffuse.Set(.5f, .5f, 0.5f, 1.0f);
	lights[0].SetPos(1.0f, 0.0f, 2.5f);
	lights[0].Init();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	lights[0].Active(true);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	//LOG("Loading Intro assets");
	bool ret = true;
	//
	sphere = new Sphere({ 0,0,0 }, 3);
	sphere->Triangulate(&vect_v, &norm_v, NULL, 6144, false);

	vec p1 = { 2,0,0 };
	vec p2 = { -2,0,0 };
	n_sphere_o = new Sphere(p1, 1);
	//App->scene_intro->n_sphere_one->Intersects(*App->scene_intro->n_sphere_two);

	n_sphere_o->Triangulate(&vec1, &vec2, NULL, 1536, false);


	index = {
		// front
		0, 1, 2,
		2, 3, 0,
		// top
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// bottom
		4, 0, 3,
		3, 7, 4,
		// left
		4, 5, 1,
		1, 0, 4,
		// right
		3, 2, 6,
		6, 7, 3,
	};
	planeindex =
	{
		// bottom
		0, 1, 2,
		2, 3, 0,
	};
	plane_vert =
	{
		100,0,100,
		100,0,-100,
		-100,0,-100,
		-100,0,100,

	};
	cube_vert = {
		// front
		7.0, 4.0,  6.0,
		9.0, 4.0,  6.0,
		9.0,  6.0,  6.0,
		7.0,  6.0,  6.0,
		// back
		7.0, 4.0, 4.0,
		9.0, 4.0, 4.0,
		9.0,  6.0, 4.0,
		7.0,  6.0, 4.0,
	};


	cube_test = new Cube_prim();
	cube_test->mesh.indices = index;
	cube_test->mesh.num_indices = index.size();
	cube_test->mesh.id_indices = 0;
	cube_test->mesh.vertices = cube_vert;
	cube_test->mesh.num_vertices = cube_vert.size();
	cube_test->mesh.id_vertices = 0;

	cube_test->Initialize();



	glGenBuffers(1, (GLuint*)&plane_vertex);
	glBindBuffer(GL_ARRAY_BUFFER, plane_vertex);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) *plane_vert.size() * 3, &plane_vert[0], GL_STATIC_DRAW);

	// Buffer for indices
	glGenBuffers(1, (GLuint*)&plane_indices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, plane_indices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * planeindex.size(), &planeindex[0], GL_STATIC_DRAW);


	// An array of 3 vectors which represents 3 vertices
	g_vertex_buffer_data = {
		0, 1, 0,
		0, 0, 0,
		1, 0, 0,

		0, 1, 0,
		1, 0, 0,
		1, 1, 0,

		1, 1, 0,
		1, 0, 0,
		1, 1, -1,

		1, 0, 0,
		1, 0, -1,
		1, 1, -1,

		0, 1, 0,
		1, 1, 0,
		1, 1, -1,

		0, 1, 0,
		1, 1, -1,
		0, 1,-1,

		0, 1, 0,
		0, 0, -1,
		0, 0, 0,

		0, 1, 0,
		0, 1, -1,
		0, 0,-1,

		1, 1, -1,
		1, 0, -1,
		0, 0, -1,

		1, 1, -1,
		0, 0, -1,
		0, 1, -1,

		0, 0, -0,
		0, 0, -1,
		1, 0, -1,

		0, 0, 0,
		1, 0, -1,
		1, 0, 0,
	};

	// This will identify our vertex buffer
	//	GLuint vertexbuffer;


	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) *g_vertex_buffer_data.size() * 3, &g_vertex_buffer_data[0], GL_STATIC_DRAW);
	// 1rst attribute buffer : vertices




	// This will identify our vertex buffer

	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer1);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer1);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, vec1.size() * sizeof(float) * 3, &vec1[0], GL_STATIC_DRAW);
	// 1rst attribute buffer : vertices

	//	GLuint normalbuffer;
	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, vec2.size() * sizeof(float) * 3, &vec2[0], GL_STATIC_DRAW);




	return ret;
}


update_status ModuleSceneIntro::PreUpdate(float dt)
{

	

	return UPDATE_CONTINUE;
}


// Update
update_status ModuleSceneIntro::Update(float dt)
{
	
	/*
	glLineWidth(2.0f);
	glBegin(GL_TRIANGLES);

	glVertex3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);

	glVertex3f(0, 1, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(1, 1, 0);

	glVertex3f(1, 1, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(1, 1, -1);

	glVertex3f(1, 0, 0);
	glVertex3f(1, 0, -1);
	glVertex3f(1, 1, -1);

	glVertex3f(0, 1, 0);
	glVertex3f(1, 1, 0);
	glVertex3f(1, 1, -1);

	glVertex3f(0, 1, 0);
	glVertex3f(1, 1, -1);
	glVertex3f(0, 1,-1);

	glVertex3f(0, 1, 0);
	glVertex3f(0, 0, -1);
	glVertex3f(0, 0, 0);

	glVertex3f(0, 1, 0);
	glVertex3f(0, 1, -1);
	glVertex3f(0, 0,-1);

	glVertex3f(1, 1, -1);
	glVertex3f(1, 0, -1);
	glVertex3f(0, 0, -1);

	glVertex3f(1, 1, -1);
	glVertex3f(0, 0, -1);
	glVertex3f(0, 1, -1);

	glVertex3f(0, 0, -0);
	glVertex3f(0, 0, -1);
	glVertex3f(1, 0, -1);

	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, -1);
	glVertex3f(1, 0, 0);









	glEnd();
	glLineWidth(1.0f);
	*/


	
	glLineWidth(2.0f);
	glBegin(GL_LINES);
	glColor3f(0, 1, 0);
	glVertex3f(0.f, 0.f, 0.f);
	glVertex3f(0.f, 3.f, 0.f);

	glEnd();
	glColor3f(1, 1, 1);

	glLineWidth(2.0f);
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(0.f, 0.f, 0.f);
	glVertex3f(3.f, 0.f, 0.f);

	glEnd();
	glColor3f(1, 1, 1);


	glLineWidth(2.0f);
	glBegin(GL_LINES);
	glColor3f(0, 0, 1);
	glVertex3f(0.f, 0.f, 0.f);
	glVertex3f(0.f, 0.f, 3.f);

	glEnd();
	glColor3f(1, 1, 1);


	cube_test->Draw();



	glBindBuffer(GL_ARRAY_BUFFER, plane_vertex);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, plane_indices);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, NULL);








	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
	0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
	3,                  // size
	GL_FLOAT,           // type
	GL_FALSE,           // normalized?
	0,                  // stride
	(void*)0            // array buffer offset
	);
	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, g_vertex_buffer_data[0], sizeof(GLfloat) *g_vertex_buffer_data.size() * 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
	glDisableVertexAttribArray(0);


	///-------------------









	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer1);
	glVertexAttribPointer(
	0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
	3,                  // size
	GL_FLOAT,           // type
	GL_FALSE,           // normalized?
	0,                  // stride
	(void*)0            // array buffer offset
	);


	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glVertexAttribPointer(
	2,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
	3,                  // size
	GL_FLOAT,           // type
	GL_FALSE,           // normalized?
	0,                  // stride
	(void*)0            // array buffer offset
	);


	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 1536); // Starting from vertex 0; 3 vertices total -> 1 triangle

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(0);




//	 light 0 on cam pos
	lights[0].SetPos(App->camera->Position.x, App->camera->Position.y, App->camera->Position.z);

	for(uint i = 0; i < MAX_LIGHTS; ++i)
	lights[i].Render();
	

	

	
	
	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	
}

update_status ModuleSceneIntro::PostUpdate(float dt)
{
	
	return UPDATE_CONTINUE;
}

bool ModuleSceneIntro::Gui_Engine_Modules(float dt)
{
	return false;
}




