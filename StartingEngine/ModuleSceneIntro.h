#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Geometry.h"
#include"j1PerfTimer.h"
#include"Imgui/imgui.h"
#include "Light.h"
#include<vector>
#include"MathGeoLib\MathGeoLib.h"
#include"MathGeoLib\MathBuildConfig.h"
#include "../StartingEngine/Glew/include/glew.h"
#include "SDL\include\SDL_opengl.h"
#include"Texture_Engine.h"


//#include"Geometry.h"
#include"Cube_prim.h"
/*#include"GameObject.h"
#include"Component.h"
#include"Mesh.h"
#include"Transform.h"*/

#define MAX_SNAKE 2
#define MAX_CUBE 50
#define MAX_LIGHTS 8

enum Tag_Object_Enum;
class Transform;
class Mesh;
class Component;
class GameObject;
struct PhysBody3D;
struct PhysMotor3D;
struct btHingeConstraint;
enum guy {
	bad_guy,
	good_guy,
	unknown
};
class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);
	update_status PostUpdate(float dt);
	bool Gui_Engine_Modules(float dt);
	bool CleanUp();

	Light lights[MAX_LIGHTS];
	
	
	GameObject* CreateNewGameObjects(const char* name, bool active, GameObject* parent, Tag_Object_Enum tag_temp, bool static_s);

public:
	ImVec2 tx_vec;
	GameObject* frustrumtest = nullptr;
	bool load_scene=false;
	bool save_scene=false;
	void IterateChildGameObjects(GameObject* item);
	GameObject* root_gameobject= nullptr;
	JSON_Value *root_value_scene = nullptr;
	JSON_Object *root_object_scene = nullptr;
	void Connect_Load_Gerarchy(std::vector<GameObject*>GO_Load);
	int num_GO=0;
	GameObject* Find_UUID_Root(int uuid);
	std::vector<GameObject*> game_objects_load;
	Texture_Engine *world_texture;
	void Load_Scene(JSON_Object* root_object_scene);
};
