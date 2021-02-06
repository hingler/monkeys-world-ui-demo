#version 430 core

#define POWER_FAC 3.2f
#define MOD_WEIGHT 0.08f
#define MOD_PERIOD 16.0f
#define HEIGHT_OFF 0.06f

layout(location = 0) in mediump float height;
layout(location = 1) in vec4 v_pos;

layout(location = 2) uniform float height_factor;

// add an offset channel so that we can bump it down

layout(location = 0) out vec4 fragcolor;

const highp float weights[16] = float[16](-0.4375f, 0.0625f, -0.3125f, 0.1875f,
                                          0.3125f, -0.1875f, 0.4375f, -0.0625f,
                                          -0.25f, 0.25f, -0.375f, 0.125f,
                                          0.5f, 0.0f, 0.375f, -0.125f);

float l_i(vec4 pos) {
  return sin(pos.x) + cos(pos.z);
}

void main() {
  ivec2 screen_coord = ivec2(gl_FragCoord.x, gl_FragCoord.y);
  int index = int(mod(mod(screen_coord.x, 4) + screen_coord.y * 4, 16));
  float light_mod = MOD_WEIGHT * l_i(v_pos * MOD_PERIOD);
  float fac = pow(max(1.0 - ((HEIGHT_OFF + height + light_mod) / height_factor), 0), POWER_FAC) + weights[index];
  if (fac < 0.501) {
    discard;
  }

  fragcolor = vec4(vec3(1.0), step(0.501, fac));
}