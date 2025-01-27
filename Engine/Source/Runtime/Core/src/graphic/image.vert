#version 450 core
in vec3 iPosition;
in vec2 iTexCoord;
out vec2 vTexCoord;
void main(){
    gl_Position = vec4(iPosition, 1.0);
    vTexCoord = iTexCoord;
}