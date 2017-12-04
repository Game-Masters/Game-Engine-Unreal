#include "Text_Editor_Shader.h"
#include"Application.h"

Editor_Text_Shader::Editor_Text_Shader()
{
}

Editor_Text_Shader::~Editor_Text_Shader()
{
}

void Editor_Text_Shader::Enable_Text_Editor(bool visible)
{

	if (visible) {
	
		ImGui::Begin("Test window", &App->gui->show_editor_shaders);

		if (ImGui::Button("Compile"))
		{
			//See if compile
		}
		ImGui::SameLine();
		if (ImGui::Button("Save"))
		{
			//Modify txt
		}

		if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) {
			editor_text_shader.InsertText("\n");
		}

		if (first_time_edit) {
			editor_text_shader.InsertText("//This is mean to be an editor of shaders");
			editor_text_shader.InsertText("\n");
			first_time_edit = false;
		}

		editor_text_shader.Render("Test_shader_editor");

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
		//TextEditor::Render()
		ImGui::End();
	}
	else {
		first_time_edit = true;
	}

}
