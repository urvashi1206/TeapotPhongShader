#version 430
in vec3 result;

out vec4 frag_color;

void main() {
  frag_color = vec4(result, 1.0f);
}