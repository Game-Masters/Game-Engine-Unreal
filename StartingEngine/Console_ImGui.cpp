#include "Console_ImGui.h"
#include"Imgui\imgui.h"
#include"Application.h"


Console::Console()
{
}

Console::~Console()
{
}


void Console::Enable_Console_Imgui(bool visible)
{
	if (visible) {
		ImGui::Begin("Console", &App->gui->show_console);
		std::list<std::string>::iterator item = console_log_str.begin();
		while (item != console_log_str.end())
		{
			ImGui::Text((*item).c_str());
			item++;
		}
		ImGui::End();
	}

}

