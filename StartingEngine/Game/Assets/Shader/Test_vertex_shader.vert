#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normals;
layout (location = 3) in vec3 color;
out vec3 ourColor;
out vec2 TexCoord;
out vec3 pos;
out vec3 Position;
out vec3 Normals;
uniform mat4 mat_model;
uniform mat4 projection_view;
uniform float time;
varying vec3 Vposition;
void main()
{
Position = position;
float wave = sin(time);
if(wave < 0)
{
wave = -wave;
}



pos = vec3(position[0],position[1],position[2]);

pos.z = position.z + (sin(((pos.y*pos.x)*0.5)*time/100*0.25));
pos.z = position.z + (sin(time+pos.x+pos.y));

 gl_Position = projection_view * mat_model* vec4(pos, 1.0f);

 
 Normals = color;
 TexCoord = texCoord;
 Vposition = position;
}