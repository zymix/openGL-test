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

const char * g_shader_vertex_normal = "#version 330 core \
\nlayout (location = 0) in vec3 aPos; \
\nlayout (location = 1) in vec3 aNormal; \
\nlayout (location = 2) in vec2 aTexCoord; \
\nlayout (location = 3) in vec3 aTangent; \
\nlayout (location = 4) in vec3 aBiTangent; \
\nuniform mat4 model; \
\nuniform mat4 view; \
\nuniform mat4 proj; \
\nuniform vec3 lightPos; \
\nuniform vec3 viewPos; \
\
\nout vec3 tanLightPos; \
\nout vec3 tanViewPos; \
\nout vec3 tanPos; \
\nout vec2 texCoord; \
\nout vec3 fragPos; \
\nvoid main() \
\n{ \
\n		texCoord = aTexCoord; \
\n		fragPos = vec3(model * vec4(aPos, 1.0)); \
\n		gl_Position = proj * view * model * vec4(aPos, 1.0); \
\
\n		mat3 norMat = transpose(inverse(mat3(model))); \
\n		vec3 T = normalize( norMat * aTangent ); \
\n		vec3 N = normalize( norMat * aNormal ); \
\n		T = normalize(T - dot(T, N) * N); \
\n		vec3 B = cross(N, T); \
\n		mat3 tTBN = transpose(mat3(T, B, N)); \
\
\n		tanLightPos = tTBN * lightPos; \
\n		tanViewPos = tTBN * viewPos; \
\n		tanPos = tTBN * fragPos; \
\n}";
