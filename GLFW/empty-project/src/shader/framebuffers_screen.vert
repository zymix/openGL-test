// #version 330 core
// layout (location = 0) in vec3 apos;
// layout (location = 1) in vec2 atex;

// out vec2 otex;
// uniform mat4 proj;
// uniform mat4 view;
// uniform mat4 model;
// void main(){
//     otex = atex;
//     gl_Position = vec4(apos.x, apos.y, 0.0, 1.0);
// }
#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 otex;

void main()
{
    otex = aTexCoords;
    gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0); 
}  