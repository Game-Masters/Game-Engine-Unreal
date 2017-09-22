#ifndef __ModuleParson_JSON_H__
#define __ModuleParson_JSON_H__

#include"Module.h"
#include"JSON\parson.h"
class ModuleParson_JSON :public Module
{
public:
	ModuleParson_JSON();
	~ModuleParson_JSON();

	bool Start();
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool Gui_Engine_Modules(float dt);
	bool CleanUp();

};
#endif
