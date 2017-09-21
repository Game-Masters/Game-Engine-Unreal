#include "Console_ImGui.h"
#include"Imgui\imgui.h"

Console::Console()
{
}

Console::~Console()
{
}

void Console::Enable_Console_Imgui(bool visible)
{
	if (visible) {
		ImGui::Begin("Console");
		{
			ImGui::Text((*item).c_str());
		}


		ImGui::End();
	}

}
