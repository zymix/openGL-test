const char * g_shader_vertex_mvp = "#version 330 core \
\nlayout (location = 0) in vec3 aPos; \
\nlayout (location = 1) in vec3 aNormal; \
\nlayout (location = 2) in vec2 aTexCoord; \
\nuniform mat4 model; \
\nuniform mat4 view; \
\nuniform mat4 proj; \
\nout vec2 texCoord; \
\nout vec2 normal; \
\nvoid main() \
\n{ \
\n		texCoord = aTexCoord; \
\n		//vec3 newPos = aPos + vec3(0 , h, 0); \
\n		gl_Position = proj * view * model * vec4(aPos, 1.0); \
\n}";
