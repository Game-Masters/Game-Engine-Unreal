#include "Text_Editor_Shader.h"
#include"Application.h"

Editor_Text_Shader::Editor_Text_Shader()
{
}

Editor_Text_Shader::~Editor_Text_Shader()
{
}

void Editor_Text_Shader::Enable_Text_Editor(bool visible, const char* path_shader)
{

	if (visible) {
	
		ImGui::Begin("Editor Shader", &App->gui->show_editor_shaders);

		if (first_time_edit && path_shader == nullptr) {
			editor_text_shader.InsertText("//This is meant to be an editor of shaders");
			editor_text_shader.InsertText("\n");
			first_time_edit = false;
		}
		else if (first_time_edit ==true && path_shader != nullptr) {

			//In a close future will need to load the text of the shader
			std::string str_temp = "";
			editor_text_shader.SetText(str_temp);
			char* buffer = nullptr;
			int size_file = App->fs_e->LoadFile(path_shader, &buffer);
			actual_path = path_shader;
			if (buffer != nullptr) {
				buffer[size_file] = '\0';
				std::string str_shader = buffer;
				editor_text_shader.InsertText(str_shader);
				first_time_edit = false;
			}

		}


		if (ImGui::Button("Compile"))
		{
			//See if compile
		}
		ImGui::SameLine();
		if (ImGui::Button("Save"))
		{
			//char* text_str_buffer = editor_text_shader.GetText().c_str();
			App->fs_e->SaveFile(actual_path.c_str(), (char*)editor_text_shader.GetText().c_str(), editor_text_shader.GetText().size());
			//Modify txt
		}


		if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) {
			editor_text_shader.InsertText("\n");
		}

		if (App->input->GetKey(SDL_SCANCODE_LCTRL) == KEY_REPEAT ){
			if (App->input->GetKey(SDL_SCANCODE_C) == KEY_DOWN) {
				text_selected = editor_text_shader.GetSelectedText();
			}
		}

		if (App->input->GetKey(SDL_SCANCODE_LCTRL) == KEY_REPEAT){
			if (App->input->GetKey(SDL_SCANCODE_V) == KEY_DOWN) {
				editor_text_shader.InsertText(text_selected);
			}
		}

		if (App->input->GetKey(SDL_SCANCODE_LCTRL) == KEY_REPEAT) {
			if (App->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN) {
				editor_text_shader.Undo();
			}
		}

		if (App->input->GetKey(SDL_SCANCODE_LCTRL) == KEY_REPEAT) {
			if (App->input->GetKey(SDL_SCANCODE_Y) == KEY_DOWN) {
				editor_text_shader.Redo();
			}
		}

		editor_text_shader.Render("Test_shader_editor");

		ImGui::End();
	}
	else {
		first_time_edit = true;
	}

}
