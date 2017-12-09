#version 330 core
in vec3 ourColor;
in vec2 TexCoord;
out vec4 color;
uniform sampler2D ourTexture;
void main()
{
gl_FragColor = vec4( 0.0, 0.0, 1.0, 1.0 );
}