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
vec4 Color =  mix( texture2D( watertexture,TexCoord)*vec4(0,0.9,0.8,1),texture2D( watertexture,TexCoord)*vec4(0,0.9,0.9,1),texture2D( alphatexture2,TexCoord));
Color = texture2D( watertexture,TexCoord);
//color = mix( texture2D( watertexture,TexCoord)*vec4(0,0.3,0.5,1),texture2D( watertexture,TexCoord)*vec4(0,0.9,0.9,1),texture2D( alphatexture,TexCoord));
//vec3 Norm = Normals *sin(time+pos.x-pos.y);
//color =vec4(Color.xyz*dot(Normals, vec3(1,1,1)),1);


//Normal maps
vec3 NormalMap = texture2D(alphatexture, TexCoord).rgb;
vec3 Light = normalize(vec3(0,-1,1));
vec3 Light2 = normalize(vec3(0,-1,1));

vec3 N = normalize((NormalMap+Normals) * 2.0 - 1.0);

color =max(vec4(Color.rgb*max(dot(N, Light),0),1)*vec4(1,1,1,1),vec4(0,0,0.5,1));
color =max(vec4(vec3(0,0.8,0.9)*max(dot(N, Light),0),1),vec4(0,0.4,0.9,1));
//if(dot(N, Light2)>0.99 &&pos.z >= Position.z)
if(dot(N, Light2)>0.90)
{
//ar = 0 +( dot(N, Light2));
ar = mix( 0,1, ((dot(N, Light2)-0.90)*10));
color =max(max(vec4(vec3(0,0.8,0.9)*max(dot(N, Light2),0),1),vec4(0,0.4,0.9,1)),vec4(1,1,1,1));
color = mix(max(vec4(vec3(0,0.8,0.9)*max(dot(N, Light),0),1),vec4(0,0.4,0.9,1)),vec4(1,1,1,1), vec4(ar,ar,ar,ar));
}



//color = vec4(Normals,1);
//color = mix( texture2D(watertexture,TexCoord),temp, vec4(0.5,0.5,0.5,0.5));
if(pos.z >= Position.z)
{

	
	ar = 0 +( pos.z - (Position.z)/ pos.z);
	ar = mix( Position.z,pos.z, pos.z+0.2);
//color = mix( texture2D(watertexture,TexCoord),texture2D(foam,TexCoord),vec4(ar,ar,ar,ar*0.5));
//color = mix( texture2D(watertexture,TexCoord)*vec4(0,0.3,0.5,1),texture2D(foam,TexCoord),texture2D(alphatexture,TexCoord)*ar);
//color = mix(  mix( texture2D( watertexture,TexCoord)*vec4(0,0.3,0.5,1),texture2D( watertexture,TexCoord)*vec4(0,0.9,0.9,1),texture2D( alphatexture,TexCoord)),texture2D(foam,TexCoord),texture2D(alphatexture,TexCoord)*ar);
//color = mix( vec4( Color.xyz *dot(Normals, vec3(1,1,1)),1),texture2D(foam,TexCoord),texture2D(alphatexture,TexCoord)*ar);
//color = mix(max(vec4(Color.rgb*max(dot(N, Light),0),1)*vec4(1,1,1,1),vec4(0,0,0.5,1)),texture2D(foam,TexCoord),texture2D(alphatexture2,TexCoord)*ar);
//color = mix(max(vec4(vec3(0,0.8,0.9)*max(dot(N, Light),0),1),vec4(0,0.4,0.9,1)),vec4(vec3(1,1,1),1),texture2D(alphatexture2,TexCoord)*ar);

}
}
