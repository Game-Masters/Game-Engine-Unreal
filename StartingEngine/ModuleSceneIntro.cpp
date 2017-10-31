#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include"GameObject.h"
#include"Component.h"
#include"Mesh.h"
#include"Transform.h"


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


	world_texture = new Texture_Engine();
	world_texture->Create(nullptr, App->window->win_width, App->window->win_height);
	std::string path_temp = "..\\Game\\Data\\BakerHouse.fbx";
	std::string path_temp2 = "..\\Game\\Data\\Baker_house.png";
	Material* temp = nullptr;

	GameObject* frustrumtest = nullptr;



	root_gameobject = CreateNewGameObjects("root", true, nullptr, Tag_Object_Enum::root_tag, false);


	frustrumtest =CreateNewGameObjects("Frustrum test", true, root_gameobject, Tag_Object_Enum::no_obj_tag, false);
	frustrumtest->AddNewTransform(float3(0,0,0), float3(1, 1, 1), Quat(0,0,0,1));
	frustrumtest->AddNewFrustum();

	App->json_class->Create_JSON_DOC(&root_value_scene, &root_object_scene, "Scene1");
	//Load_Scene();

	



	return ret;
}


update_status ModuleSceneIntro::PreUpdate(float dt)
{
	world_texture->Bind();
	//world_texture->Resize()

	return UPDATE_CONTINUE;
}


// Update
update_status ModuleSceneIntro::Update(float dt)
{

	
	
	root_gameobject->Update();
	

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
	

	if (App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN) {
		Load_Scene();
	}
	if (App->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN) {
		root_gameobject->Save(root_object_scene);
		char* serialized_string = json_serialize_to_string_pretty(root_value_scene);
		json_serialize_to_file(root_value_scene, "Scene1");

	}
	

	
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


	for (int i = 0; i < root_gameobject->Childrens_GameObject_Vect.size(); i++) {
		delete root_gameobject->Childrens_GameObject_Vect[i];
		for (int i = 0; i < root_gameobject->Childrens_GameObject_Vect[i]->Component_Vect.size(); i++) {
			delete root_gameobject->Childrens_GameObject_Vect[i]->Component_Vect[i];
		}
	}
	root_gameobject->Childrens_GameObject_Vect.clear();
	root_gameobject->Component_Vect.clear();
	delete world_texture;
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

void ModuleSceneIntro::Load_Scene()
{
	GameObject* temp_go = nullptr;
	int i = 0;
	std::string g_temp = "GameObject" + std::to_string(i + 1);
	JSON_Object* node;
	node = json_object_get_object(root_object_scene, g_temp.c_str());
	while(node!=nullptr){
		std::string g_temp = "GameObject" + std::to_string(i + 1);
		JSON_Object* node;
		node = json_object_get_object(root_object_scene, g_temp.c_str());
		if (node != nullptr) {
			int UUID = json_object_get_number(node, "UUID");
			int UUID_parent = json_object_get_number(node, "UUID_parent");
			std::string name_go = json_object_get_string(node, "Name");

			temp_go = CreateNewGameObjects(name_go.c_str(), true, App->scene_intro->root_gameobject, Tag_Object_Enum::no_obj_tag, false);
			game_objects_load.push_back(temp_go);
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
			JSON_Object* node_mesh;
			node_mesh = json_object_get_object(node, "Mesh");
			if (node_mesh != nullptr) {
				std::string fbx_path = json_object_get_string(node_mesh, "Path FBX");
				geometry_base_creating* temp_geom = App->imp_mesh->Create_Base_Geometry(fbx_path.c_str(), name_go.c_str(), fbx_path.c_str());
				temp_go->AddNewMesh(temp_geom, fbx_path.c_str());
			}
			

		}
		else {
			break;
		}
		i++;

	}

	//I need to connect the gerarchy of UUID



}








