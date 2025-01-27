#version 450 core
in vec2 vTexCoord;
uniform sampler2D iTexture;
out vec4 fColor;
void main(){
    fColor = texture(iTexture, vTexCoord);
}