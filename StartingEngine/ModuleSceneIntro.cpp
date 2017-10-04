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
	



	cube_test = new Cube_prim();

	cube_test->mesh.num_vertices = 8;

	cube_test->mesh.num_indices = 36;

	cube_test->mesh.vertices = new float[cube_test->mesh.num_vertices * 3];
	cube_test->mesh.indices = new uint[cube_test->mesh.num_indices];
	memcpy(cube_test->mesh.vertices, &cube_vert[0], sizeof(float) * cube_test->mesh.num_vertices * 3);
	for (uint i = 0; i < 36; ++i)
	{
		memcpy(&cube_test->mesh.indices[i], &index[i], sizeof(uint));
	}

	cube_test->Initialize();

	//-----

	plane_test = new Cube_prim();

	plane_test->mesh.num_vertices = 4;

	plane_test->mesh.num_indices = 6;

	plane_test->mesh.vertices = new float[plane_test->mesh.num_vertices * 3];
	plane_test->mesh.indices = new uint[plane_test->mesh.num_indices];
	memcpy(plane_test->mesh.vertices, &plane_vert[0], sizeof(float) * plane_test->mesh.num_vertices * 3);
	for (uint i = 0; i < 6; ++i)
	{
		memcpy(&plane_test->mesh.indices[i], &planeindex[i], sizeof(uint));
	}

	plane_test->Initialize();




	
	// An array of 3 vectors which represents 3 vertices
	/*
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

	*/


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


	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < 256; j++) {
			int c = ((((i & 0x8) == 0) ^ (((j & 0x8)) == 0))) * 255;
			checkImage[i][j][0] = (GLubyte)c;
			checkImage[i][j][1] = (GLubyte)c;
			checkImage[i][j][2] = (GLubyte)c;
			checkImage[i][j][3] = (GLubyte)255;
		}
	}



	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &ImageName);
	glBindTexture(GL_TEXTURE_2D, ImageName);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256, 256,
		0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);
	
	return ret;
}


update_status ModuleSceneIntro::PreUpdate(float dt)
{

	

	return UPDATE_CONTINUE;
}


// Update
update_status ModuleSceneIntro::Update(float dt)
{
	
	

	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindTexture(GL_TEXTURE_2D, ImageName);


	glBegin(GL_TRIANGLES);

	glTexCoord2f(0.0f, 1.0f); glVertex3f(0, 1, 0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, 0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1, 0, 0);


	glTexCoord2f(0.0f, 1.0f); glVertex3f(0, 1, 0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1, 0, 0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1, 1, 0);


	glTexCoord2f(0.0f, 1.0f); glVertex3f(1, 1, 0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1, 0, 0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1, 1, -1);


	glTexCoord2f(0.0f, 0.0f); glVertex3f(1, 0, 0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1, 0, -1);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1, 1, -1);

	
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0, 1, 0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1, 1, 0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1, 1, -1);


	glTexCoord2f(0.0f, 1.0f); glVertex3f(0, 1, 0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1, 1, -1);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0, 1, -1);

	
	//----

	glTexCoord2f(1.0f, 1.0f); glVertex3f(0, 1, 0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, -1);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 0, 0);


	glTexCoord2f(1.0f, 1.0f); glVertex3f(0, 1, 0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0, 1, -1);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, -1);

	
	//----

	glTexCoord2f(0.0f, 1.0f); glVertex3f(1, 1, -1);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1, 0, -1);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 0, -1);


	glTexCoord2f(0.0f, 1.0f); glVertex3f(1, 1, -1);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 0, -1);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0, 1, -1);

	
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0, 0, -0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, -1);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1, 0, -1);


	glTexCoord2f(0.0f, 1.0f); glVertex3f(0, 0, 0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1, 0, -1);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1, 0, 0);



	
	

	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	glLineWidth(1.0f);







	
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


	/*cube_test->Draw();
	plane_test->Draw();*/







	/*
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
	*/

	///-------------------








	/*
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


	*/

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
	return true;
}

bool ModuleSceneIntro::CleanUp()
{
	delete cube_test;
	delete plane_test;
	return true;
}




