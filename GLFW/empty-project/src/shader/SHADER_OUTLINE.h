const char * g_shader_vert_outline = "#version 330 core \
\nlayout (location = 0) in vec3 aPos; \
\nlayout (location = 1) in vec3 aNormal; \
\nlayout (location = 2) in vec2 aTexCoord; \
\nuniform mat4 model; \
\nuniform mat4 view; \
\nuniform mat4 proj; \
\nuniform sampler2D texture_height1;\n \
\nout vec2 texCoord; \
\nvoid main() \
\n{ \
\n		texCoord = aTexCoord; \
\n		gl_Position = proj * view * model * vec4(aPos + normalize(aNormal)*0.05, 1.0); \
\n}";

const char * g_shader_frag_outline = "#version 330 core \
\n  \
\nout vec4 FragColor; \
\nvoid main() \
\n{ \
\n		FragColor = vec4(1.0,1.0,1.0,1.0); \
\n}";
