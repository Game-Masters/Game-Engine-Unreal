#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normals;
layout (location = 3) in vec3 color;
out vec3 ourColor;
out vec2 TexCoord;
uniform mat4 mat_model;
uniform mat4 projection_view;

void main()
{
 gl_Position = projection_view * mat_model* vec4(position, 1.0f);
 TexCoord = texCoord;

}