#include"GameObject.h"
#include "Component.h"

Component::Component(Component_Type_Enum type_component, GameObject* parent, bool active): type_component(type_component), parent(parent), active(active)
{
}

Component::~Component()
{
}

void Component::SetActive(bool state)
{
	active = state;
}

void Component::Update()
{



}


