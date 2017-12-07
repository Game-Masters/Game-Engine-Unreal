#ifndef EDITOR_TEXT_SHADER_H_
#define EDITOR_TEXT_SHADER_H_

#include"TextEditor.h"

class Editor_Text_Shader {
public:
	Editor_Text_Shader();
	~Editor_Text_Shader();

	void Enable_Text_Editor(bool visible = false, const char* path_shader=nullptr);
	void Enable_CreateShader(bool visible = false);
public:
	char str_shad_temp[64] = { 0 };
	std::string name_shader;
	int combo_shaders;
	bool first_time_edit = true;
	TextEditor editor_text_shader;
	std::string text_selected;
	std::string actual_path;
};
#endif // !EDITOR_TEXT_SHADER_H_

