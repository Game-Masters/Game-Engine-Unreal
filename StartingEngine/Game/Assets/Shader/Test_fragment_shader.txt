#version 330 core
in vec3 ourColor;
in vec2 TexCoord;
out vec4 color;
vec4 temp = vec4(0.2,0.2,0.5,1);
uniform sampler2D ourTexture;
uniform float time;
varying vec3 Vposition;
float Time = time;
void main()
{
vec2 aux = TexCoord;

if(Time>200)
{
Time = 0;
}


aux.x = aux.x + (sin(aux.y*Time*.5)*0.05);


color = texture(ourTexture, TexCoord);
color = texture2D( ourTexture,aux);
}