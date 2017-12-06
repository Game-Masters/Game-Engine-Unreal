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
#include"Imgui\ImGuizmo.h"
#include"ShaderProgramObject.h"
#include"ResourceShaderObject.h"


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
class QuadTreeZ;
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
	ImVec4 tx_vec;
	GameObject* frustrumtest = nullptr;
	bool load_scene=false;
	bool save_scene=false;
	bool calc_octree_stop_button = false;
	GameObject* root_gameobject= nullptr;
	JSON_Value *root_value_scene = nullptr;
	JSON_Object *root_object_scene = nullptr;
	ImGuizmo::OPERATION Operator_Guiz = ImGuizmo::OPERATION::TRANSLATE;
	void Connect_Load_Gerarchy(std::vector<GameObject*>GO_Load);
	int num_GO=0;
	GameObject* Find_UUID_Root(int uuid);
	std::vector<GameObject*> game_objects_load;
	Texture_Engine *world_texture;
	void StaticAllGameObject(GameObject* temp, bool static_t);

	void Load_Scene(JSON_Object* root_object_scene, bool load_scene = true);
	void drawGrid(int grid_size);
	void drawLines(const vec3 from, const vec3 to, const vec3 color)const;
	QuadTreeZ* scene_quadtree = nullptr;
	int num_gameobjects_empty_created = 0;
	bool draw_quadtree = false;
	ResourceShaderObject* test_shader_vertex = nullptr;
	ResourceShaderObject* test_shader_frag = nullptr;
	std::vector<int> shader_obj_v;
	std::vector<ShaderProgramObject*> shader_program_v;
	ShaderProgramObject* test_program = nullptr;
};