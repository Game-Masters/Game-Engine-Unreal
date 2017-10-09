#include "Component.h"

Component::Component(Component_Type_Enum type_component, bool active): type_component(type_component), active(active)
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


