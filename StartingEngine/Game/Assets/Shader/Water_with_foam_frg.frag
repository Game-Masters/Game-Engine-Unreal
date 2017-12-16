#version 330 core
in vec3 ourColor;
in vec2 TexCoord;
in vec3 pos;
in vec3 Position;
in vec3 Normals;
in vec3 Vposition;
out vec4 color;


uniform sampler2D NormalTexture;
uniform sampler2D AlphaTexture;

uniform vec4 Color1;
uniform vec4 Color2;
uniform vec4 Color3;

uniform float time;
float Time = time;
float ar = 0;
float ar2 = 0;
void main()
{
vec2 aux = TexCoord;

if(Time>200)
{
Time = 0;
}

aux.x = aux.x + (sin(aux.y*Time*.5)*0.05);


//Normal maps
vec3 NormalMap = texture2D(NormalTexture, TexCoord).rgb;
vec3 Light = normalize(vec3(0,-1,1));
vec3 Light2 = normalize(vec3(0,-1,1));

vec3 N = normalize((NormalMap+Normals) * 2.0 - 1.0);


color =max(vec4(vec3(0,0.8,0.9)*max(dot(N, Light),0),1),vec4(0,0.4,0.9,1));

if(dot(N, Light2)>0.90)
{

ar2 = mix( 0,1, ((dot(N, Light2)-0.90)*10));

color = mix(max(vec4(vec3(0,0.8,0.9)*max(dot(N, Light),0),1),vec4(0,0.4,0.9,1)),vec4(1,1,1,1), vec4(ar2,ar2,ar2,ar2));
}

if(Vposition.z >= Position.z)
{

	
	
	ar = mix( Position.z,pos.z, pos.z+0.2);
	ar = mix( Vposition.z,Position.z, Position.z-0.5);

color = mix(max(vec4(vec3(0,0.8,0.9)*max(dot(N, Light),0),1),vec4(0,0.4,0.9,1)),vec4(vec3(1,1,1),1),texture2D(AlphaTexture,TexCoord)*ar);

}
if(dot(N, Light2)>0.90)
{

ar2 = mix( 0,1, ((dot(N, Light2)-0.90)*10));
color =  mix(mix(max(vec4(vec3(0,0.8,0.9)*max(dot(N, Light),0),1),vec4(0,0.4,0.9,1)),vec4(1,1,1,1), vec4(ar2,ar2,ar2,ar2)),vec4(vec3(1,1,1),1),texture2D(AlphaTexture,TexCoord)*ar);
}

}