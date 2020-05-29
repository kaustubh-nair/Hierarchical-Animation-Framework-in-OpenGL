#version 330 core
out vec4 FragColor;

#define NUMBER_OF_LIGHTS 2

in vec3 Normal;  
in vec3 FragPos;  
in vec2 TexCoord;
  
uniform sampler2D Texture;
uniform vec3 viewPos;

struct Light {
    vec3 Pos;
    float diffuseStrength;
    float specularStrength;
};

uniform Light lights[NUMBER_OF_LIGHTS];

void main()
{
    float ambientStrength = 0.3;
    vec3 color = vec3(texture(Texture, TexCoord));

    vec3 result;
    if(color == vec3(0.0f, 0.0f, 0.0f))  //TODO hacky for no textures - light nodes
        result = vec3(1.0f, 1.0f, 1.0f);
    else
    {

    result = vec3(0.0f, 0.0f, 0.0f);

    for(int i = 0; i < NUMBER_OF_LIGHTS; i++)
    {
        vec3 lightPos = lights[i].Pos;
        float diffuseStrength = lights[i].diffuseStrength;
        float specularStrength = lights[i].specularStrength;

        // diffuse 
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(lightPos - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diffuseStrength * diff * color;

        //specular
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);  
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
        vec3 specular = specularStrength * spec * color;  
        result += ( diffuse + specular );

    }

    // ambient
    vec3 ambient = ambientStrength * color;
    result += ambient;
    }

    FragColor =  vec4(result, 1.0f);
}
