#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normals;
layout (location = 3) in vec3 color;
out vec3 ourColor;
out vec2 TexCoord;
uniform mat4 mat_model;
uniform mat4 projection_view;
uniform float time;
varying vec3 Vposition;
void main()
{

float wave = sin(time);
if(wave < 0)
{
wave = -wave;
}



vec3 pos = vec3(position[0],position[1],position[2]);

pos.z = pos.z + (sin(pos.x*pos.y*time*0.25)*0.15);


 gl_Position = projection_view * mat_model* vec4(pos, 1.0f);

 

 TexCoord = texCoord;
 Vposition = position;
}