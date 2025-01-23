#version 450 core
in vec3 iPosition;
in vec3 iColor;
out vec4 vColor;
void main(){
    gl_Position = vec4(iPosition, 1.0);
    vColor = vec4(iColor, 1.0);
}