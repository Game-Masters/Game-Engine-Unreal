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

	if (first_time_edit ==true && path_shader != nullptr) {

			//In a close future will need to load the text of the shader
			std::string str_temp = "";
			editor_text_shader.SetText(str_temp);
			char* buffer = nullptr;
			int size_file = App->fs_e->LoadFile(path_shader, &buffer,true);
			actual_path = path_shader;
			if ((buffer != nullptr) && size_file>1) {
				buffer[size_file] = '\0';
				std::string str_shader = buffer;
				editor_text_shader.InsertText(str_shader);
				first_time_edit = false;
			}
			else {
				editor_text_shader.InsertText("//This is meant to be an editor of shaders");
				editor_text_shader.InsertText("\n");
			}
			delete[] buffer;
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
				//text_selected = editor_text_shader.GetSelectedText();
				editor_text_shader.Copy();
			}
		}

		if (App->input->GetKey(SDL_SCANCODE_LCTRL) == KEY_REPEAT){
			if (App->input->GetKey(SDL_SCANCODE_V) == KEY_DOWN) {
				//editor_text_shader.InsertText(text_selected);
				editor_text_shader.Paste();
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
		ImGuiIO& io = ImGui::GetIO();
		ImGui::PushFont(io.Fonts->Fonts[1]);
		editor_text_shader.Render("Test_shader_editor");
		//Has crash! Take care!
		ImGui::PopFont();
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
		ResourceShaderObject* temp= (ResourceShaderObject*)App->resources_mod->CreateNewResource(Resources_Type::shader_obj);
		std::string empty_file="";
		ImGui::InputText("Name of the Shader", str_shad_temp, 64);
		name_shader = str_shad_temp;
		
		ImGui::Combo("Shaders Mode", &combo_shaders, "Vertex Shader\0Fragment Shader");
	
	

		if (ImGui::Button("Create")) {
			if (combo_shaders == 0) {
				temp->Set_Type_Shader(ShaderType::vertex_shader);
				App->fs_e->ChangeFormat_File(name_shader.c_str(), "vert", &name_shader, App->fs_e->Shader_User);
			}
			else if (combo_shaders == 1) {
				temp->Set_Type_Shader(ShaderType::fragment_shader);
				App->fs_e->ChangeFormat_File(name_shader.c_str(), "frag", &name_shader, App->fs_e->Shader_User);
			}

			temp->Set_New_Resource_Files(empty_file, name_shader);
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

void Editor_Text_Shader::Enable_LinkShader(bool visible)
{

	if (visible) {
		ImGui::Begin("Link new Shader Program", &App->gui->linkenewshader);

		std::vector<int> Shader_Object_Selection;

		std::vector<Resource*> Shader_Object_Compiled;
		Shader_Object_Compiled=App->resources_mod->Get_TypeResources(Resources_Type::shader_obj);
		std::string shader_options;

		std::string file_name;
		std::string name;
		for (int i = 0; i < Shader_Object_Compiled.size(); i++) {
			file_name=Shader_Object_Compiled[i]->GetExportedFile();
			size_t name_start = file_name.rfind("\\")+1;
			size_t name_end = file_name.rfind(".");
			name = file_name.substr(name_start,name_end-name_start);
			shader_options += name;
			shader_options += '\0';
		}

		ImGui::InputText("Name of the Program Shader", str_progrshad_temp, 64);
		program_name = str_progrshad_temp;

		ImGui::Combo("Shader 1:", &combo_shaders_obj, shader_options.c_str());
		ImGui::Combo("Shader 2:", &combo_shaders_obj2, shader_options.c_str());
	

		if (ImGui::Button("Link Program")) {

			if (combo_shaders_obj != -1) {
				Shader_Object_Compiled[combo_shaders_obj]->LoadToMemory();
				Shader_Object_Selection.push_back(Shader_Object_Compiled[combo_shaders_obj]->GetUID());
			}

			if (combo_shaders_obj2 != -1) {
				Shader_Object_Compiled[combo_shaders_obj2]->LoadToMemory();
				Shader_Object_Selection.push_back(Shader_Object_Compiled[combo_shaders_obj2]->GetUID());
			}
			ResourceShaderMaterial* temp_program;
			temp_program=(ResourceShaderMaterial*)App->resources_mod->CreateNewResource(Resources_Type::shader_program);
			temp_program->SetShaderObj_Vect(Shader_Object_Selection);
			temp_program->SetProgram_Name(program_name.c_str());
			std::string path_str = App->fs_e->ShaderMaterial_Engine->path + "\\" + program_name + ".shadermat";
			temp_program->Set_New_Resource_Files("", path_str);
			temp_program->LoadToMemory();
			temp_program->CreateMeta();
			App->resources_mod->AddResources(temp_program);
			App->gui->linkenewshader = false;
		}


		ImGui::End();
	}
}
