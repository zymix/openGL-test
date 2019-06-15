#version 330 core
out vec4 FragColor;

in vec3 tanLightPos;
in vec3 tanViewPos;
in vec3 tanPos;
in vec2 texCoord;
in vec3 fragPos;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_normal1;
uniform sampler2D texture_specular1;

void main(){
    vec3 n = normalize(texture(texture_normal1, texCoord).xyz * 2.0 -1.0);
    vec3 v = tanViewPos - fragPos;
    vec3 l = tanLightPos - fragPos;
    vec3 h = normalize(v+l);

    vec3 color = texture(texture_diffuse1, texCoord).rgb;
    vec3 diffuse = color * max(dot(n, l), 0);
    vec3 ambient = color * 0.1;
    vec3 specular = vec3(0.2) * pow(max(dot(h, l), 0), 16.0);
    FragColor = vec4(diffuse + ambient + specular, 1.0);
}
