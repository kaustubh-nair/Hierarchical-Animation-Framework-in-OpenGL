#version 330 core
out vec4 FragColor;

#define NUMBER_OF_LIGHTS 2

in vec3 Normal;  
in vec3 FragPos;  
in vec2 TexCoord;
  
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform sampler2D Texture;
uniform vec3 viewPos;
uniform bool noTextures;

struct Light {
    vec3 Pos;
    float diffuseStrength;
    float specularStrength;
};

uniform Light lights[NUMBER_OF_LIGHTS];

vec3 calculateLightStrength()
{
    float ambientStrength = 0.2;
    vec3 result = vec3(0.0f, 0.0f, 0.0f);
    for(int i = 0; i < NUMBER_OF_LIGHTS; i++)
    {
    vec3 lightPos = lights[i].Pos;
    float dist = distance(lightPos, FragPos);
    float difDist = 10.0f/pow(dist, 2);
    float diffuseStrength = lights[i].diffuseStrength;

    // ambient
    vec3 ambient = ambientStrength * lightColor;

    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = difDist*diff * lightColor;

    //specular
    float specDist = (16.5f - dist)/6.5f;
    float specularStrength = lights[i].specularStrength;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specDist*specularStrength * spec * lightColor;  
    result += (ambient+ specular+ diffuse);

}
    return result * objectColor;
}

void main()
{

    if(noTextures)
    {

        vec3 result = calculateLightStrength();
        FragColor = vec4(result, 1.0);
    }
    else
    {
        FragColor = texture(Texture, TexCoord);
    }
  

} 
