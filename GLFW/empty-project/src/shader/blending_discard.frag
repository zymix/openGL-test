#version 330 core
in vec2 texCoord;
uniform sampler2D tex;
void main(){
    vec4 color = texture2D(tex, texCoord);
    if(color.a < 0.1){
        discard;
    }
    gl_FragColor = color;
}