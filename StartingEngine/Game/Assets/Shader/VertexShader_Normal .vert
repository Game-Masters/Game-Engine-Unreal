#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normals;
layout (location = 3) in vec3 color;
uniform mat4 mat_model;
uniform mat4 projection_view;
void main() { 
vec3 pos = vec3(position[0],position[1],position[2]);
gl_Position = projection_view * mat_model* vec4(pos, 1.0f); 
}