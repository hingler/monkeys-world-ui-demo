#version 430 core

precision mediump float;

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texcoord;
layout(location = 2) in vec3 normal;

layout(location = 0) uniform mat4 u_Model;
layout(location = 1) uniform mat4 u_ViewProj;

layout(location = 0) out mediump float height;

void main() {
  vec4 pos = u_ViewProj * u_Model * position;
  height = position.y;
  gl_Position = pos;
}