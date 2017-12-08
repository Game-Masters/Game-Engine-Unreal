#ifndef EDITOR_TEXT_SHADER_H_
#define EDITOR_TEXT_SHADER_H_

#include"TextEditor.h"

class Editor_Text_Shader {
public:
	Editor_Text_Shader();
	~Editor_Text_Shader();

	void Enable_Text_Editor(bool visible = false, const char* path_shader=nullptr);
	void Enable_CreateShader(bool visible = false);
	void Enable_LinkShader(bool visible = false);
public:
	char str_shad_temp[64] = { 0 };
	char str_progrshad_temp[64] = { 0 };
	std::string name_shader;
	std::string program_name;
	int combo_shaders;
	int combo_shaders_obj=-1;
	int combo_shaders_obj2 = -1;
	bool first_time_edit = true;
	TextEditor editor_text_shader;
	std::string text_selected;
	std::string actual_path;
};
#endif // !EDITOR_TEXT_SHADER_H_

