#ifndef __CONSOLE_IMGUI_H__
#define __CONSOLE_IMGUI_H__
#include<list>
#include<string>





class Console
{
public:

	Console();

	// Destructor
	virtual ~Console();
	bool Init();
	void Enable_Console_Imgui(bool visible=false);
	bool CleanUp();
public:
	std::list<std::string> console_log_str;

};

#endif

