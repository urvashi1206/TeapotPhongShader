#version 430
in vec3 color;
in vec4 normal;
in vec4 lightDir1; 
in vec4 lightDir2;

// Define varying variables
in vec4 FragPos;
in vec4 viewPosition;

out vec4 FragColor;

void main()
{
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
    FragColor = vec4(result, 1.0);
}