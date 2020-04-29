#include "../include/model.h"


void Model::setup(std::vector<std::string> filepaths, std::vector<glm::vec3> meshPos,
                  std::string texturePath)
{
    std::vector<std::string>::iterator filepath;
    std::vector<glm::vec3>::iterator position = meshPos.begin();

    for (filepath = filepaths.begin(); filepath < filepaths.end(); filepath++)
    {
        Mesh mesh(*filepath, *position, texturePath);
        mesh.setup();
        meshes.push_back(mesh);

        position++;
    }

}

void Model::refresh()
{
    for(auto mesh = meshes.begin(); mesh < meshes.end(); mesh++)
        mesh->setup();
}

void Model::draw(Shader shader)
{
    for(auto mesh = meshes.begin(); mesh < meshes.end(); mesh++)
        mesh->draw(shader);
}


void Model::drawLighting(Shader shader, Shader lightingShader)
{
    glm::vec3 lightPos = glm::vec3(15.0f, 0.0f, -2.0f);

    shader.setVec3("lights[0].Pos",lightPos.x, lightPos.y, lightPos.z);
    shader.setFloat("lights[0].diffuseStrength",0.0f);
    shader.setFloat("lights[0].specularStrength",4.0f);
    lightPos = glm::vec3(-1.2f, 1.2f, -2.0f);
    shader.setVec3("lights[1].Pos",lightPos.x, lightPos.y, lightPos.z);
    shader.setFloat("lights[1].diffuseStrength",0.5f);
    shader.setFloat("lights[1].specularStrength",0.0f);

    shader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);

    Lighting lighting;
    lighting.draw(lightingShader, lightPos);
}


void Model::unselect()
{
    std::vector<Mesh>::iterator mesh;

    for (mesh = meshes.begin(); mesh < meshes.end(); mesh++)
    {
        if(mesh->id == settings.selectedMesh)
        {
            mesh->selected = false;
            break;
        }
    }
    settings.selectedMesh = -1;
}

void Model::select(int id)
{
    if(settings.selectedMesh != -1)
        return;
    settings.selectedMesh = id;

    std::vector<Mesh>::iterator mesh;
    for (mesh = meshes.begin(); mesh < meshes.end(); mesh++)
    {
        if(mesh->id == id)
        {
            mesh->selected = true;
            break;
        }
    }
}

void Model::translate(glm::vec2 direction)
{
    if(settings.selectedMesh == -1)
        return;
    meshes[settings.selectedMesh - 1].translate(direction);
}
