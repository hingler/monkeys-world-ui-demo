#version 430 core

#define POWER_FAC 1.8f

layout(location = 0) in mediump float height;

layout(location = 0) uniform float height_factor;

layout(location = 0) out vec4 fragcolor;

const highp float weights[4] = float[4](-0.25f, 0.25f, 0.5f, 0.0f);

void main() {
  ivec2 screen_coord = ivec2(gl_FragCoord.x, gl_FragCoord.y) / 2;
  int index = mod(mod(x, 2) + y + y, 4);
  float fac = pow(1.0 - (height * height_factor), POWER_FAC) + weights[index];
  fragcolor = vec4(vec3(1.0), step(fac, 0.5));
}