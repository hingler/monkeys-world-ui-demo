#version 430 core

layout(location = 0) in vec2 texcoord;


layout(location = 0) uniform int segment_count;     // num of segments
layout(location = 1) uniform float segment_offset;  // t offset per segment
layout(location = 2) uniform float time;            // shader time
layout(location = 3) uniform sampler2D frame;       // inputted frame we are transitioning out of

layout(location = 0) out vec4 fragColor;

float fade(float input) {
  // if input < 0: return 0
  // if input > 1: return 1
  float fade_output = input * input;
  return min(step(0, input) * fade_output, 1);
}

vec2 getOffset() {
  vec2 texcoord_input = texcoord;
  int segment = int(floor(1 - texcoord.y) * segment_count);
  float start_time = segment_offset * segment;
  float fade_res = fade(time - start_time);
  texcoord_input.x -= fade_res;
  return texcoord_input;
}

void main() {
  vec2 tex = getOffset();
  int in_bounds = int(step(0, tex.x) * step(tex.x, 1));
  vec4 lookup = texture(frame, tex);
  fragColor = vec4(lookup.rgb, lookup.a * in_bounds);
}