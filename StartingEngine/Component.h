#pragma once

enum Component_Type_Enum {
	component_null_type,
	component_transform_type,
	component_mesh_type,
	component_material_type
};

class Component
{

	Component_Type_Enum type_component = component_null_type;
	bool active = true;

public:
	Component(Component_Type_Enum type_component, bool active);
	~Component();
	virtual void SetActive(bool state);
	virtual void Update();

};

