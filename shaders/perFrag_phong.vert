#version 430

uniform mat4 modelMat;
uniform mat4 viewMat; 
uniform mat4 projMat; 
uniform vec3 lightPos1;
uniform vec3 lightPos2;
uniform vec3 viewPos;

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_normal;

out vec3 color;

out vec4 normal;
out vec4 lightDir1;
out vec4 lightDir2;
out vec4 FragPos;
out vec4 viewPosition;


void main() {
  vec4 lpos1 = viewMat * vec4(lightPos1, 1.0f);
  vec4 lpos2 = viewMat * vec4(lightPos2, 1.0f);
  vec4 ppos = viewMat * modelMat * vec4 (vertex_position, 1.0f);
  
  lightDir1 = normalize(lpos1 - ppos);
  lightDir2 = normalize(lpos2 - ppos);
  viewPosition = viewMat * modelMat * vec4(viewPos, 1.0);
  normal = vec4(normalize(mat3(transpose(inverse(viewMat*modelMat))) * vertex_normal),0.0f);
  //normal = viewMat * modelMat * vec4(vertex_normal, 0.0f);
  FragPos = viewMat * modelMat * vec4(vertex_position, 1.0);
  color = vec3(1.0, 1.0, 1.0);
	
  gl_Position = projMat * viewMat * modelMat * vec4(vertex_position, 1.0f);
}