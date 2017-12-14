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
uniform sampler2D foam;
uniform sampler2D alphatexture2;
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


//color = texture(ourTexture, TexCoord);
//color = texture2D( ourTexture,aux);
//color = vec4(0.0,0.9,0.8,01.0);

color =vec4( mix( texture2D( watertexture,TexCoord)*vec4(0,0.3,0.5,1),texture2D( watertexture,TexCoord)*vec4(0,0.9,0.9,1),texture2D( alphatexture2,TexCoord)).xyz *dot(Normals, vec3(0,1,1)),1);
//color = mix( texture2D( watertexture,TexCoord)*vec4(0,0.3,0.5,1),texture2D( watertexture,TexCoord)*vec4(0,0.9,0.9,1),texture2D( alphatexture,TexCoord));
//vec3 Norm = Normals *sin(time+pos.x-pos.y);
color =vec4(vec3(0,1,1)*dot(Normals, vec3(0,1,1)),1);
//color = vec4(Normals,1);
//color = mix( texture2D(watertexture,TexCoord),temp, vec4(0.5,0.5,0.5,0.5));
if(pos.z >= Position.z)
{

	
	ar = 0 +( pos.z - (Position.z)/ pos.z);
	ar = mix( Position.z,pos.z, pos.z);
//color = mix( texture2D(watertexture,TexCoord),texture2D(foam,TexCoord),vec4(ar,ar,ar,ar*0.5));
//color = mix( texture2D(watertexture,TexCoord)*vec4(0,0.3,0.5,1),texture2D(foam,TexCoord),texture2D(alphatexture,TexCoord)*ar);
//color = mix(  mix( texture2D( watertexture,TexCoord)*vec4(0,0.3,0.5,1),texture2D( watertexture,TexCoord)*vec4(0,0.9,0.9,1),texture2D( alphatexture,TexCoord)),texture2D(foam,TexCoord),texture2D(alphatexture,TexCoord)*ar);
//color = mix( vec4( mix( texture2D( watertexture,TexCoord)*vec4(0,0.3,0.5,1),texture2D( watertexture,TexCoord)*vec4(0,0.9,0.9,1),texture2D( alphatexture2,TexCoord)).xyz *dot(Normals, vec3(0,1,1)),1),texture2D(foam,TexCoord),texture2D(alphatexture,TexCoord)*ar);
}
}
