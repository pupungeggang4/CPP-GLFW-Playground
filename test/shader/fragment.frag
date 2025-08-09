#version 410 core

uniform sampler2D u_texture;
in vec2 p_texcoord;
out vec4 o_color;

void main() {
    o_color = texture(u_texture, p_texcoord);
}