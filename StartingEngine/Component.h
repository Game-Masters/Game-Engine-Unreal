#pragma once
#include"JSON\parson.h"
class GameObject;



enum Component_Type_Enum {
	component_null_type,
	component_transform_type,
	component_mesh_type,
	component_camera,
	component_material_type
};

class Component
{
protected:
	GameObject* parent = nullptr;
	Component_Type_Enum type_component = component_null_type;
	bool active = true;
	int UUID_comp=0;
	int UUID_parent_GO = 0;
public:
	Component(Component_Type_Enum type_component, GameObject* parent, bool active);
	~Component();
	virtual void SetActive(bool state);
	virtual void PreUpdate();
	virtual void Update();
	const Component_Type_Enum GetComponentType()const;
	void Set_Parent(GameObject& par);
	GameObject* Get_Parent()const;
	virtual void Save(JSON_Object *root_object_scene);
	virtual void Load(JSON_Object *root_object_scene);
	virtual void CleanUp();
};

