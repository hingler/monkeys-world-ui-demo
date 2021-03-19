#version 430 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texcoord;
layout(location = 2) in vec3 normals;

layout(location = 0) uniform mat4 model_mat;
layout(location = 1) uniform mat4 vp_mat;

layout(location = 2) uniform mat3 norm_mat;

layout(location = 3) uniform float stroke_width;

void main() {
  vec3 norm_tf = normalize(norm_mat * normals);
  vec4 pos_stroke = (model_mat * position) + vec4(vec3(norm_tf * stroke_width), 0);
  gl_Position = vp_mat * pos_stroke;
}