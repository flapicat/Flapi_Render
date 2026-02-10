#version 330 core
out vec4 FragColor;

in vec2 o_TexCords;
in float o_TexIndex;

uniform sampler2D u_Textures[32];

void main()
{
	FragColor = texture(u_Textures[int(o_TexIndex)], o_TexCords);
}