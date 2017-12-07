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

void Editor_Text_Shader::Enable_CreateShader(bool visible)
{

	if (visible) {
		ImGui::Begin("Shader Options", &App->gui->createnewshader);
		ResourceShaderObject* temp= (ResourceShaderObject*)App->resources_mod->CreateNewResource(Resources_Type::shader);
		std::string empty_file="";
		ImGui::InputText("Name of the Shader", str_shad_temp, 64);
			name_shader = str_shad_temp;
		

		App->fs_e->ChangeFormat_File(name_shader.c_str(), "txt", &name_shader, App->fs_e->Shader_User);
	
		temp->Set_New_Resource_Files(empty_file, name_shader);
		
		ImGui::Combo("Shaders Mode", &combo_shaders, "Vertex Shader\0Fragment Shader");
		if (combo_shaders==1) {
			temp->Set_Type_Shader(ShaderType::vertex_shader);
		}
		else if (combo_shaders == 2) {
			temp->Set_Type_Shader(ShaderType::fragment_shader);
		}
		
		if (ImGui::Button("Create")) {
			App->gui->createnewshader = false;
			App->fs_e->SaveFile(name_shader.c_str(), "", 1);
			temp->LoadToMemory();
			temp->CreateMeta();
			App->resources_mod->AddResources(temp);
			App->gui->show_editor_shaders = true;
			App->gui->gui_editor_text_shader.first_time_edit = true;
			App->gui->gui_editor_text_shader.Enable_Text_Editor(App->gui->show_editor_shaders, temp->GetExportedFile());
		}

		ImGui::End();
	}

}
