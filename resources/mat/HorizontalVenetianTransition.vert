#version 430 core

layout(location = 0) in vec2 position;

layout(location = 0) out vec2 texcoord;


void main() {
  texcoord = (position + vec2(1)) / 2;
  gl_Position = vec4(position.xy, -1, 1);
}