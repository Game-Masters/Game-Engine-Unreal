#ifndef EDITOR_TEXT_SHADER_H_
#define EDITOR_TEXT_SHADER_H_

#include"TextEditor.h"

class Editor_Text_Shader {
public:
	Editor_Text_Shader();
	~Editor_Text_Shader();

	void Enable_Text_Editor(bool visible = false);

public:
	bool first_time_edit = true;
	TextEditor editor_text_shader;
	std::string text_selected;
};
#endif // !EDITOR_TEXT_SHADER_H_

