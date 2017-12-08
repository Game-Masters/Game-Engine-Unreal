#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include"GameObject.h"
#include"Component.h"
#include"Mesh.h"
#include"Transform.h"
#include"Imgui\Data.h"
#include"Imgui\imguidock.h"
#include"Quadtree.h"
#include"ResourceTexture.h"

ModuleSceneIntro::ModuleSceneIntro(bool start_enabled) : Module(start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	bool ret = true;

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


	root_gameobject = CreateNewGameObjects("root", true, nullptr, Tag_Object_Enum::root_tag, false);
	scene_quadtree = new QuadTreeZ();
	scene_quadtree->SetBoundaries(&(AABB(float3(-10.0f, -10.0f, -10.0f), float3(10.0f, 10.0f, 10.0f))));
	



	tx_vec=ImGui::GetSizeDock(3);
	world_texture = new Texture_Engine();
	world_texture->Create(nullptr, tx_vec.z, tx_vec.w);

	App->renderer3D->OnResize(tx_vec.z, tx_vec.w);

	world_texture->Bind();
	std::string path_temp = "..\\Game\\Data\\BakerHouse.fbx";
	std::string path_temp2 = "..\\Game\\Data\\Baker_house.png";
	Material* temp = nullptr;

	//Testing shaders

	std::string temp_str=" ";
	std::string name_shader_vert;
	std::string name_shader_frag;
	std::string name_shader_frag2;
	App->fs_e->ChangeFormat_File("Test_vertex_shader", "txt", &name_shader_vert, App->fs_e->Shader_User);
	App->fs_e->ChangeFormat_File("Test_fragment_shader", "txt", &name_shader_frag, App->fs_e->Shader_User);
	App->fs_e->ChangeFormat_File("Test_fragment_shader2", "txt", &name_shader_frag2, App->fs_e->Shader_User);


	test_shader_vertex = (ResourceShaderObject*)App->resources_mod->CreateNewResource(Resources_Type::shader);
	test_shader_vertex->Set_New_Resource_Files(temp_str, name_shader_vert);
	test_shader_vertex->Set_Type_Shader(ShaderType::vertex_shader);
	test_shader_vertex->LoadToMemory();
	test_shader_vertex->CreateMeta();
	test_shader_frag = (ResourceShaderObject*)App->resources_mod->CreateNewResource(Resources_Type::shader);
	test_shader_frag->Set_Type_Shader(ShaderType::fragment_shader);
	test_shader_frag->Set_New_Resource_Files(temp_str, name_shader_frag);
	test_shader_frag->LoadToMemory();
	test_shader_frag->CreateMeta();
	test_shader_frag2 = (ResourceShaderObject*)App->resources_mod->CreateNewResource(Resources_Type::shader);
	test_shader_frag2->Set_Type_Shader(ShaderType::fragment_shader);
	test_shader_frag2->Set_New_Resource_Files(temp_str, name_shader_frag2);
	test_shader_frag2->LoadToMemory();
	test_shader_frag2->CreateMeta();
	App->resources_mod->AddResources(test_shader_vertex);
	App->resources_mod->AddResources(test_shader_frag);
	App->resources_mod->AddResources(test_shader_frag2);
	shader_obj_v.push_back(test_shader_vertex->GetUID());
	shader_obj_v.push_back(test_shader_frag->GetUID());
	test_program = new ShaderProgramObject(shader_obj_v,"Default");
	test_program->Link_Program();
	shader_obj_v.clear();
	shader_obj_v.push_back(test_shader_vertex->GetUID());
	shader_obj_v.push_back(test_shader_frag2->GetUID());
	test_program2 = new ShaderProgramObject(shader_obj_v, "Color");
	test_program2->Link_Program();
	
	App->shaders_manager->shader_program_v.push_back(test_program);
	App->shaders_manager->shader_program_v.push_back(test_program2);

	//Load_Scene();

	



	return ret;
}


update_status ModuleSceneIntro::PreUpdate(float dt)
{
	world_texture->Bind();
	tx_vec = ImGui::GetSizeDock(3);
	world_texture->Resize(tx_vec.z, tx_vec.w);
	//world_texture->Resize()
	root_gameobject->PreUpdate();

	return UPDATE_CONTINUE;
}


// Update
update_status ModuleSceneIntro::Update(float dt)
{
	
	drawGrid(50);
	
	root_gameobject->Update();
	

	if(draw_quadtree)
	scene_quadtree->DebugDraw();



	glLineWidth(5.0f);
	glBegin(GL_LINES);
	glColor3f(0, 1, 0);
	glVertex3f(0.f, 0.f, 0.f);
	glVertex3f(0.f, 3.f, 0.f);

	glEnd();
	glColor3f(1, 1, 1);

	glLineWidth(5.0f);
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(0.f, 0.f, 0.f);
	glVertex3f(3.f, 0.f, 0.f);

	glEnd();
	glColor3f(1, 1, 1);


	glLineWidth(5.0f);
	glBegin(GL_LINES);
	glColor3f(0, 0, 1);
	glVertex3f(0.f, 0.f, 0.f);
	glVertex3f(0.f, 0.f, 3.f);

	glEnd();
	glColor3f(1, 1, 1);


//	 light 0 on cam pos
	lights[0].SetPos(App->camera->Position.x, App->camera->Position.y, App->camera->Position.z);

	for(uint i = 0; i < MAX_LIGHTS; ++i)
	lights[i].Render();
	

	/*if (load_scene) {
		App->json_class->Create_JSON_DOC(&root_value_scene, &root_object_scene, "..//Game//Assets//Scenes//Scene1");
		Load_Scene(root_object_scene);
		load_scene = false;
	}*/

	/*if (save_scene) {
		App->json_class->Create_JSON_DOC(&root_value_scene, &root_object_scene, "..//Game//Assets//Scenes//Scene1");
		json_object_clear(root_object_scene);
		root_gameobject->Save(root_object_scene);
		char* serialized_string = json_serialize_to_string_pretty(root_value_scene);
		json_serialize_to_file(root_value_scene, "..//Game//Assets//Scenes//Scene1");
		save_scene = false;

	}*/
	

	
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

	root_gameobject->CleanUp();
	delete world_texture;
	//json_value_free(root_value_scene);
	return true;
}

GameObject * ModuleSceneIntro::CreateNewGameObjects(const char * name, bool active, GameObject* parent, Tag_Object_Enum tag_temp, bool static_s)
{

	std::string name_f = name;

	GameObject* n_gameobject = new GameObject(name_f, parent, active, tag_temp, static_s);
	if(parent!=nullptr)
	parent->Childrens_GameObject_Vect.push_back(n_gameobject);
	return n_gameobject;
}

void ModuleSceneIntro::StaticAllGameObject(GameObject * temp, bool static_t)
{

	temp->static_obj = static_t;

	for (int i = 0; i < temp->Childrens_GameObject_Vect.size(); i++) {
		StaticAllGameObject(temp->Childrens_GameObject_Vect[i], static_t);
	}


}

void ModuleSceneIntro::Load_Scene(JSON_Object* root_object_scene, bool load_scene)
{
	std::vector<GameObject*> GO_Load;
	GameObject* temp_go = nullptr;
	int i = 0;
	std::string g_temp = "GameObject" + std::to_string(i + 1);
	JSON_Object* node;
	node = json_object_get_object(root_object_scene, g_temp.c_str());
	if (node == nullptr) {
		if (load_scene) {
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Fail Loading", "You can only load Scene Files with this option", App->window->window);
		}
		App->gui->inspection_node = nullptr;
	}

	while(node!=nullptr){
		std::string g_temp = "GameObject" + std::to_string(i + 1);
		JSON_Object* node;
		node = json_object_get_object(root_object_scene, g_temp.c_str());
		if (node != nullptr) {
			int UUID = json_object_get_number(node, "UUID");
			int UUID_parent = json_object_get_number(node, "UUID_parent");
			std::string name_go = json_object_get_string(node, "Name");

			if (UUID_parent==0) {
				temp_go = CreateNewGameObjects(name_go.c_str(), true, App->scene_intro->root_gameobject, Tag_Object_Enum::no_obj_tag, false);
			}
			else {
				temp_go = CreateNewGameObjects(name_go.c_str(), true, nullptr, Tag_Object_Enum::no_obj_tag, false);
			}
			temp_go->active=json_object_get_boolean(node, "Active");
			temp_go->static_obj=json_object_get_boolean(node, "Static");

			temp_go->Set_UUID(UUID);
			temp_go->Set_UUID_parent(UUID_parent);

			JSON_Object* node_trans;
			node_trans = json_object_get_object(node, "Transform");
			if (node != nullptr) {
				JSON_Array* array_t = json_object_get_array(node_trans, "Position");
				math::float3 pos;
				pos.x = (float)json_value_get_number(json_array_get_value(array_t, 0));
				pos.y = (float)json_value_get_number(json_array_get_value(array_t, 1));
				pos.z = (float)json_value_get_number(json_array_get_value(array_t, 2));

				array_t = json_object_get_array(node_trans, "Scale");
				math::float3 scale;
				scale.x = (float)json_value_get_number(json_array_get_value(array_t, 0));
				scale.y = (float)json_value_get_number(json_array_get_value(array_t, 1));
				scale.z = (float)json_value_get_number(json_array_get_value(array_t, 2));

				array_t = json_object_get_array(node_trans, "Rotation");
				math::Quat quat;
				quat.x = (float)json_value_get_number(json_array_get_value(array_t, 0));
				quat.y = (float)json_value_get_number(json_array_get_value(array_t, 1));
				quat.z = (float)json_value_get_number(json_array_get_value(array_t, 2));
				quat.w = (float)json_value_get_number(json_array_get_value(array_t, 3));
				temp_go->AddNewTransform(pos, scale, quat);
			}

			JSON_Object* node_mat;
			Material *mat=nullptr;
			node_mat = json_object_get_object(node, "Material");
			if (node_mat != nullptr) {
				std::string str_p_t = json_object_get_string(node_mat, "Resource Material");
				std::string str_p_t_Ex = json_object_get_string(node_mat, "Resource Material exported");
				int uuid_text = App->resources_mod->Find_EngineRes(str_p_t.c_str());
				if (uuid_text == -1) {
					ResourceTexture* res_text = (ResourceTexture*)App->resources_mod->CreateNewResource(Resources_Type::texture);
					res_text->Set_New_Resource_Files(str_p_t, str_p_t_Ex);
					res_text->LoadToMemory();

				}
				else {
					ResourceTexture* res_text = (ResourceTexture*)App->resources_mod->Get(uuid_text);
					res_text->LoadToMemory();
				}
				mat=temp_go->AddNewMaterial(uuid_text);
			}
		
			ResourceMesh* temp_mesh_try = nullptr;
			JSON_Object* node_mesh;
			node_mesh = json_object_get_object(node, "Mesh");
			if (node_mesh != nullptr) {
				std::string str_p_fbx = json_object_get_string(node_mesh, "General_Path_FBX");
				std::string str_p_ex = json_object_get_string(node_mesh, "Resource Mesh exported");
				std::string str_p = json_object_get_string(node_mesh, "Resource Mesh");
				int uuid_pp = App->resources_mod->Find_EngineRes(str_p.c_str());
				if (uuid_pp == -1) {
					temp_mesh_try=(ResourceMesh*)App->resources_mod->CreateNewResource(Resources_Type::mesh);
					temp_mesh_try->Set_New_Resource_Files(str_p, str_p_fbx);
					if (temp_mesh_try->GetLoadedNum() == 0) {
						temp_mesh_try->CreateOnlyMesh();
					}
					App->resources_mod->AddResources(temp_mesh_try);
				}
				else {
					temp_mesh_try= (ResourceMesh*)App->resources_mod->Get(uuid_pp);
				}

				if (temp_mesh_try != nullptr) {
					temp_go->AddNewMesh(temp_mesh_try->GetUID(), str_p_fbx.c_str(), mat);
				}
			}
			node_mesh = json_object_get_object(node, "Frustum Comp");
			if (node_mesh != nullptr) {
				temp_go->AddNewFrustum();
			}


			GO_Load.push_back(temp_go);

		}
		else {
			break;
		}
		i++;

	}
	//connect the gerarchy of UUID
	Connect_Load_Gerarchy(GO_Load);

	num_GO = 0;
}

void ModuleSceneIntro::Connect_Load_Gerarchy(std::vector<GameObject*>GO_Load)
{

	for (int i = 0; i <GO_Load.size(); i++) {
		GameObject *temp_comp = GO_Load[i];
		if (temp_comp->Get_UUID_Parent() != 0) {
			GameObject *parent_t = Find_UUID_Root(temp_comp->Get_UUID_Parent());
			if (parent_t != nullptr) {
				temp_comp->parent = parent_t;
				parent_t->Childrens_GameObject_Vect.push_back(temp_comp);
			}
		}

	}

}

GameObject * ModuleSceneIntro::Find_UUID_Root(int uuid)
{
	return this->root_gameobject->FindUUID(uuid);
}

void ModuleSceneIntro::drawLines(const vec3 from, const vec3 to, const vec3 color) const
{
	glLineWidth(2.0f);
	glBegin(GL_LINES);
	glColor3f(color.x, color.y, color.z);
	glVertex3f(from.x, from.y, from.z);
	glVertex3f(to.x, to.y, to.z);
	glColor3f(1.0f, 1.0f, 1.0f);
	glEnd();
}

void ModuleSceneIntro::drawGrid(int grid_size)
{
	/*
	vec3 line_color = { 1, 1 ,1 };

	for (int i = -grid_size; i <= grid_size; i++)
	{
		vec3 vect = { (float)i, 0 , (float)-grid_size };
		vec3 vect2 = { (float)i, 0 , (float)grid_size };
		drawLines(vect, vect2, line_color);

		vect = { (float)-grid_size, 0 , (float)i };
		vect2 = { (float)grid_size, 0 , (float)i };
		drawLines(vect, vect2, line_color);
		
	}*/
}



