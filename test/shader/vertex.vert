#version 410 core
in vec4 a_position;
in vec2 a_texcoord;
out vec2 p_texcoord;

void main() {
    gl_Position = a_position;
    p_texcoord = a_texcoord;
}