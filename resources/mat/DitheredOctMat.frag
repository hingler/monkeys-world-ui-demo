#version 430 core

#define POWER_FAC 3.2f

layout(location = 0) in mediump float height;

layout(location = 2) uniform float height_factor;

// add an offset channel so that we can bump it down

layout(location = 0) out vec4 fragcolor;

const highp float weights[16] = float[16](-0.4375f, 0.0625f, -0.3125f, 0.1875f,
                                          0.3125f, -0.1875f, 0.4375f, -0.0625f,
                                          -0.25f, 0.25f, -0.375f, 0.125f,
                                          0.5f, 0.0f, 0.375f, -0.125f);

void main() {
  ivec2 screen_coord = ivec2(gl_FragCoord.x, gl_FragCoord.y);
  int index = int(mod(mod(screen_coord.x, 4) + screen_coord.y * 4, 16));
  float fac = pow(max(1.0 - (height / height_factor), 0), POWER_FAC) + weights[index];
  if (fac < 0.501) {
    discard;
  }

  fragcolor = vec4(vec3(1.0), step(0.501, fac));
}