#include "../include/model.h"

Model::Model()
{
    renderSplats = false;
}

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
    int currentScene = settings.currentScene;
    std::vector<Mesh>::iterator mesh;

    for (mesh = meshes.begin(); mesh < meshes.end(); mesh++)
    {
        if(this->renderSplats)
            mesh->setupSplats();
        else
            mesh->setup();
    }
}

void Model::draw(Shader shader)
{
    std::vector<Mesh>::iterator mesh;

    for (mesh = meshes.begin(); mesh < meshes.end(); mesh++)
    {
        if(this->renderSplats)
            mesh->drawSplats(shader);
        else
            mesh->draw(shader);
    }
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
    int currentScene = settings.currentScene;
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
    int currentScene = settings.currentScene;
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
    int currentScene = settings.currentScene;
    if(settings.selectedMesh == -1)
        return;
    meshes[settings.selectedMesh - 1].translate(direction);
}

void Model::scale(int direction)
{
    int currentScene = settings.currentScene;
    if(settings.selectedMesh == -1)
        return;

    meshes[settings.selectedMesh - 1].scale(direction);
}

void Model::rotate(glm::vec2 direction)
{
    int currentScene = settings.currentScene;
    if(settings.selectedMesh == -1)
        return;
    meshes[settings.selectedMesh - 1].rotate(direction);

}

void Model::changeSplatRadius(int direction)
{
    int currentScene = settings.currentScene;
    if(settings.selectedMesh == -1)
        return;
    meshes[settings.selectedMesh - 1].changeSplatRadius(direction);
}

void Model::subdivide()
{
    int currentScene = settings.currentScene;
    if(settings.selectedMesh == -1)
        return;
    meshes[settings.selectedMesh - 1].subdivide();

}
