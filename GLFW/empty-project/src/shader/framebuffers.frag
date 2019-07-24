// #version 330 core
// in vec2 otex;
// uniform sampler2D texture1;
// out vec4 FragColor;

// void main(){
//     FragColor = texture(texture1, otex);
// }

#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture1;

void main()
{    
    FragColor = texture(texture1, TexCoords);
}