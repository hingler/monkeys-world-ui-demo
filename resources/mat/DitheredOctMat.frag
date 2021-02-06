#version 430 core

#define POWER_FAC 3.2f

layout(location = 0) in mediump float height;

layout(location = 2) uniform float height_factor;

// add an offset channel so that we can bump it down

layout(location = 0) out vec4 fragcolor;

const highp float weights[4] = float[4](-0.25f, 0.25f, 0.5f, 0.0f);

void main() {
  ivec2 screen_coord = ivec2(gl_FragCoord.x, gl_FragCoord.y) / 2;
  int index = int(mod(mod(screen_coord.x, 2) + screen_coord.y * 2, 4));
  float fac = pow(max(1.0 - (height / height_factor), 0), POWER_FAC) + weights[index];
  if (fac < 0.501) {
    discard;
  }

  fragcolor = vec4(vec3(1.0), step(0.501, fac));
}