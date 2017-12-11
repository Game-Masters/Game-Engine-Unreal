#version 330 core
in vec3 ourColor;
in vec2 TexCoord;
in vec3 pos;
in vec3 Position;
in vec3 Normals;
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
color = vec4(0.0,0.9,0.8,01.0);

if(pos.z > Position.z+0.4)
{
	
color = mix(vec4(0.0,0.9,0.8,1.0),vec4(1.0,1.0,1.0,1.0),vec4(pos.z -Position.z+0.3*0.5,pos.z -Position.z+0.3*0.5,pos.z -Position.z+0.3*0.5,0.5));

}
}