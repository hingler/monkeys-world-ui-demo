#version 430 core


// todo: use shaderprogrambuilder to handle includes?
// do something similar to CPP and add a "//#include" to the code
// if we detect it on its own line, load some other file in
// and replace that include statement with the file
// this will allow us to use perlin noise in multiple functions

layout(location = 0) in vec2 texcoord;

layout(location = 0) uniform float time;
layout(location = 1) uniform float theta;
layout(location = 2) uniform float grid_width;
layout(location = 3) uniform float disp_scale;
layout(location = 4) uniform float grid_scale;
layout(location = 5) uniform float noise_facs;

layout(location = 0) out vec4 fragColor;

/**
 *  Returns a value on the range [0.0, 1.0) 
 */
float rand(vec3 a) {
    // imagine some function which returns the dot product of the input and the gradient
    return fract(sin(dot(a, vec3(121.44, 221.433, 73.22))) * 8141.440595);
}

/**
 *  Turns an inputted vec3 into a perlin gradient vector.
 */
vec3 hash(vec3 a) {
    int hash_input = int(rand(a) * 12.0);
    vec3 res = vec3(0);
    switch (hash_input) {
        case 0: res = vec3(0, -1, -1); break;
        case 1: res = vec3(0, -1,  1); break;
        case 2: res = vec3(0,  1, -1); break;
        case 3: res = vec3(0,  1,  1); break;
        case 4: res = vec3(-1, 0, -1); break;
        case 5: res = vec3(-1, 0,  1); break;
        case 6: res = vec3( 1, 0, -1); break;
        case 7: res = vec3( 1, 0,  1); break;
        case 8: res = vec3(-1, -1, 0); break;
        case 9: res = vec3(-1,  1, 0); break;
        case 10: res = vec3( 1, -1, 0); break;
        case 11: res = vec3( 1,  1, 0); break; 
    }

    return res;
}

float fade(float t) {
    return t * t * t * (10.0 + t * (t * 6.0 - 15.0));
}

float line(vec3 a, vec3 b) {
    vec3 f = floor(a);
    vec3 u = a - f;
    float w = fade(fract(u.x));
    return mix(dot(hash(f), b), dot(hash(f + vec3(1, 0, 0)), b - vec3(1, 0, 0)), w);
}

float plane(vec3 a, vec3 b) {
    float v = fade(fract(a.y));
    return mix(line(a, b), line(a + vec3(0, 1, 0), b - vec3(0, 1, 0)), v);   
}

float cube(vec3 a, vec3 b) {
    float v = fade(fract(a.z));
    return mix(plane(a, b), plane(a + vec3(0, 0, 1), b - vec3(0, 0, 1)), v);
}

float noise3(vec3 i) {
    vec3 u = fract(i);
    return cube(i, u);
}

float noise2(vec2 i) {
    vec3 a = vec3(i, 0.0);
    vec3 u = fract(a);
    return plane(a, u);
}

float noise1(float i) {
    vec3 a = vec3(i, vec2(0.0));
    vec3 u = fract(a);
    return line(a, u);
}

void main() {
  vec2 uv_grid = texcoord * grid_scale;
  vec2 uv_noise = texcoord;

  float acc = 0.0;
  int factors = int(noise_facs);

  for (int i = 0; i < factors; i++) {
    acc += noise3(vec3(uv_noise, time / 3.0));
    uv_noise *= 2.0;
  }

  acc /= noise_facs;
  acc *= disp_scale;

  // grid moves over time
  uv_grid += vec2(-time / 1.6, time / 2.4);

  // displacement
  uv_grid += vec2(acc);

  // rotate grid
  uv_grid = vec2(uv_grid.x * cos(theta) - uv_grid.y * sin(theta), uv_grid.x * sin(theta) + uv_grid.y * cos(theta));

  float grid_val = max(step(fract(uv_grid.x), grid_width), step(fract(uv_grid.y), grid_width));

  fragColor = vec4(mix(vec3(1.0, 0.8, 0.9), vec3(1.0, 0.567, 0.733), 1.0 - grid_val), 1.0);
}