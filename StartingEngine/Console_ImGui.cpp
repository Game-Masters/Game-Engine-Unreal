#include "Console_ImGui.h"
#include"Imgui\imgui.h"
#include"Application.h"
#include "../StartingEngine/Assimp/include/assimp/cimport.h"
#include "../StartingEngine/Assimp/include/assimp/scene.h"
#include "../StartingEngine/Assimp/include/assimp/postprocess.h"
#include "../StartingEngine/Assimp/include/assimp/cfileio.h"

#pragma comment (lib, "../StartingEngine/Assimp/include/libx86/assimp.lib")

Console::Console()
{
}

Console::~Console()
{
}

bool Console::Init()
{
	
	// Stream log messages to Debug window
	struct aiLogStream stream;
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream);	

	return true;
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
