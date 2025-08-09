#version 410 core

uniform sampler2D u_texture;
uniform vec3 u_textcolor;
in vec2 p_texcoord;
out vec4 o_color;

void main() {
    //o_color = texture(u_texture, p_texcoord);
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(u_texture, p_texcoord).r);
    o_color = vec4(u_textcolor, 1.0) * sampled;
}