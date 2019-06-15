const char * g_shader_frag_normal = "#version 330 core \n \
out vec4 FragColor;\n \
\n \
in vec3 tanLightPos;\n \
in vec3 tanViewPos;\n \
in vec3 tanPos;\n \
in vec2 texCoord;\n \
in vec3 fragPos;\n \
\n \
uniform sampler2D texture_diffuse1;\n \
uniform sampler2D texture_normal1;\n \
uniform sampler2D texture_specular1;\n \
\n \
void main(){\n \
    vec3 n = normalize(texture(texture_normal1, texCoord).xyz * 2.0 -1.0);\n \
    vec3 h = normalize(v+l);\n \
\n \
    vec3 color = texture(texture_diffuse1, texCoord).rgb;\n \
    vec3 diffuse = color * max(dot(n, l), 0);\n \
    vec3 ambient = color * 0.1;\n \
\n \
	vec3 specColor = texture(texture_specular1, texCoord).rgb; \n \
    FragColor = vec4(ambient+diffuse+specular, 1.0);\n \
}";
