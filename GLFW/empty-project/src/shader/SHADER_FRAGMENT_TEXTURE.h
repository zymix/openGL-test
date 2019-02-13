const char * g_shader_frag_diffuse = "#version 330 core\n \
out vec4 FragColor;\n \
in vec2 texCoord;\n \
uniform sampler2D texture_diffuse1;\n \
void main()\n \
{\n \
	FragColor = texture(texture_diffuse1, texCoord);\n \
}";
