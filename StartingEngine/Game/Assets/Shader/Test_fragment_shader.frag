#version 330 core
in vec3 ourColor;
in vec2 TexCoord;
in vec3 pos;
in vec3 Position;
in vec3 Normals;
out vec4 color;
vec4 temp = vec4(0.2,0.2,0.5,1);
uniform sampler2D ourTexture;
uniform sampler2D alphatexture;
uniform sampler2D watertexture;
uniform float time;
varying vec3 Vposition;
float Time = time;
float ar = 0;
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
color = texture2D( alphatexture,TexCoord);
//color = mix( texture2D( alphatexture,TexCoord),texture2D(watertexture,TexCoord), vec4(0.5,0.5,0.5,0.5));
if(pos.z >= Position.z)
{

	
	ar = 0 +( pos.z - (Position.z)/ pos.z);
	ar = mix( Position.z,pos.z, pos.z);
color = mix( texture2D(watertexture,TexCoord),vec4(1,1,1,1),vec4(ar,ar,ar,ar));
}
}