#version 430

uniform mat4 modelMat;
uniform mat4 viewMat; 
uniform mat4 projMat; 
uniform vec3 lightPos1;
uniform vec3 lightPos2;
uniform vec3 viewPos;

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_normal;

out vec3 result;


void main() {
  vec4 lpos1 = viewMat * vec4(lightPos1, 1.0f);
  vec4 lpos2 = viewMat * vec4(lightPos2, 1.0f);
  vec4 ppos = viewMat * modelMat * vec4 (vertex_position, 1.0f);
  
  vec4 lightDir1 = normalize(lpos1 - ppos);
  vec4 lightDir2 = normalize(lpos2 - ppos);
  vec4 viewPosition = viewMat * modelMat * vec4(viewPos, 1.0);
  vec4 normal = vec4(normalize(mat3(transpose(inverse(viewMat*modelMat))) * vertex_normal),0.0f);
  //normal = viewMat * modelMat * vec4(vertex_normal, 0.0f);
  vec4 FragPos = viewMat * modelMat * vec4(vertex_position, 1.0);
  vec3 color = vec3(1.0, 1.0, 1.0);
	
  vec3 ambientColor1 = vec3(0.0, 0.15, 0.0);
  vec3 diffuseColor1 = vec3(1.0, 1.0, 0.0);
  vec3 specularColor1 = vec3(1.0, 0.0, 0.0);
  float shininess1 = 10;

  vec3 ambientColor2 = vec3(0.0, 0.0, 0.15);
  vec3 diffuseColor2 = vec3(1.0, 0.0, 1.0);
  vec3 specularColor2 = vec3(1.0, 0.0, 0.0);
  float shininess2 = 10;

  // Ambient lighting calculation for light 1
  // float ambientStrength = 0.1;
  // vec3 ambient = ambientStrength * ambientColor;
  vec3 ambient1 = ambientColor1;

  // Ambient lighting calculation for light 2
  vec3 ambient2 = ambientColor2;

  // Diffuse lighting calculation for point light 1
  float diff1 = max(dot(normal, lightDir1), 0.0);
  vec3 diffuse1 = diffuseColor1 * diff1;

  // Diffuse lighting calculation for point light 2
  float diff2 = max(dot(normal, lightDir2), 0.0);
  vec3 diffuse2 = diffuseColor2 * diff2;

  // Specular lighting calculation for point light 1
  vec4 viewDir1 = normalize(viewPosition - FragPos);
  vec4 reflectDir1 = reflect(-lightDir1, normal);  
  float spec1 = pow(max(dot(viewDir1, reflectDir1), 0.0), shininess1);
  vec3 specular1 = specularColor1 * spec1;

  // Specular lighting calculation for point light 2
  vec4 viewDir2 = normalize(viewPosition - FragPos);
  vec4 reflectDir2 = reflect(-lightDir2, normal);  
  float spec2 = pow(max(dot(viewDir2, reflectDir2), 0.0), shininess2);
  vec3 specular2 = specularColor2 * spec2;


  // Final lighting calculation
  vec3 result = (ambient1 + ambient2 + diffuse1 + diffuse2 + specular1 + specular2)/2;
  
  gl_Position = projMat * viewMat * modelMat * vec4(vertex_position, 1.0f);
}