// #version 330 core
// layout (location = 0) in vec3 apos;
// layout (location = 1) in vec2 atex;

// out vec2 otex;
// uniform mat4 proj;
// uniform mat4 view;
// uniform mat4 model;
// void main(){
//     otex = atex;
//     gl_Position = proj * view * model * vec4(apos, 1.0);
// }
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    TexCoords = aTexCoords;    
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}