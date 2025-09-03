#version 330 core

out vec4 FragColor;
in vec2 TexCoord;
in vec3 VertexColor;

uniform sampler2D atlas;

void main()
{
	vec4 texColor = texture(atlas, TexCoord);
	FragColor = vec4(texColor.rgb * VertexColor, texColor.a);
}
