#version 430 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texcoord;
layout(location = 3) in vec3 normals;

layout(location = 0) uniform mat4 model_mat;
layout(location = 1) uniform mat4 vp_mat;

layout(location = 2) uniform float stroke_width;

void main() {
  vec4 pos_stroke = position + (normals * stroke_width);
  gl_Position = vp_mat * model_mat * pos_stroke;
}