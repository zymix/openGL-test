const char * g_shader_vert_skybox = "#version 330 core \
\n layout (location=0) in vec3 aPos; \
\n out vec3 texCoord; \
\n uniform mat4 view; \
\n uniform mat4 proj; \
\n void main() \
\n{ \
\n  texCoord = aPos;\
\n  vec4 pos = proj * view * vec4(aPos, 1.0); \
\n  gl_Position = pos.xyww;\
\n} \
";

const char * g_shader_frag_skybox = "#version 330 core \
\n in vec3 texCoord;\
\n out vec4 FragColor;\
\n uniform samplerCube skybox; \
\n void main() \
\n { \
\n    FragColor = texture(skybox, texCoord);\
\n } \
";