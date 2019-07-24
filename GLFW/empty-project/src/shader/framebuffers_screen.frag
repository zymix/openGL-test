// #version 330 core
// in vec2 itex;
// uniform sampler2D screenTexture;
// out vec4 FragColor;
// void main(){
//     FragColor = vec4(texture(screenTexture, itex).rgb, 1.0);
//     // FragColor.a = 1.0;
// }

#version 330 core
out vec4 FragColor;

in vec2 otex;

uniform sampler2D screenTexture;

void main()
{
    vec3 col = texture(screenTexture, otex).rgb;
    FragColor = vec4(col, 1.0);
} 