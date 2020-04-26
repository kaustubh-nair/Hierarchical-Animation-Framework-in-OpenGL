#include "../include/model.h"

Model::Model()
{
    renderSplats = false;
}

void Model::setup(std::vector<std::string> filepaths, std::vector<glm::vec3> meshPos,
                  std::vector<std::string> texturePaths, int sceneID)
{
    std::vector<std::string>::iterator filepath;
    std::vector<glm::vec3>::iterator position = meshPos.begin();
    std::vector<std::string>::iterator texturePath = texturePaths.begin();
    Scene scene;

    for (filepath = filepaths.begin(); filepath < filepaths.end(); filepath++)
    {
        Mesh mesh(*filepath, *position, *texturePath);
        mesh.setup();
        scene.add_mesh(mesh);

        position++;
        texturePath++;
    }

    scenes[sceneID] = scene;

}

/* refresh for rendering splats */
void Model::refresh()
{
    int currentScene = settings.currentScene;
    std::vector<Mesh>::iterator mesh;

    for (mesh = scenes[currentScene].meshes.begin(); mesh < scenes[currentScene].meshes.end(); mesh++)
    {
        if(this->renderSplats)
            mesh->setupSplats();
        else
            mesh->setup();
    }
}

void Model::draw(Shader shader)
{
    int currentScene = settings.currentScene;
    std::vector<Mesh>::iterator mesh;

    for (mesh = scenes[currentScene].meshes.begin(); mesh < scenes[currentScene].meshes.end(); mesh++)
    {
        if(this->renderSplats)
            mesh->drawSplats(shader);
        else
            mesh->draw(shader);
    }
}


void Model::drawLighting(Shader shader, Shader lightingShader)
{
    glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 1.0f);

    shader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
    shader.setVec3("lightPos",lightPos.x, lightPos.y, lightPos.z);

    Lighting lighting;
    lighting.draw(lightingShader, lightPos);
}


void Model::unselect()
{
    int currentScene = settings.currentScene;
    std::vector<Mesh>::iterator mesh;

    for (mesh = scenes[currentScene].meshes.begin(); mesh < scenes[currentScene].meshes.end(); mesh++)
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
    for (mesh = scenes[currentScene].meshes.begin(); mesh < scenes[currentScene].meshes.end(); mesh++)
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
    scenes[currentScene].meshes[settings.selectedMesh - 1].translate(direction);
}

void Model::scale(int direction)
{
    int currentScene = settings.currentScene;
    if(settings.selectedMesh == -1)
        return;

    scenes[currentScene].meshes[settings.selectedMesh - 1].scale(direction);
}

void Model::rotate(glm::vec2 direction)
{
    int currentScene = settings.currentScene;
    if(settings.selectedMesh == -1)
        return;
    scenes[currentScene].meshes[settings.selectedMesh - 1].rotate(direction);

}

void Model::changeSplatRadius(int direction)
{
    int currentScene = settings.currentScene;
    if(settings.selectedMesh == -1)
        return;
    scenes[currentScene].meshes[settings.selectedMesh - 1].changeSplatRadius(direction);
}

void Model::subdivide()
{
    int currentScene = settings.currentScene;
    if(settings.selectedMesh == -1)
        return;
    scenes[currentScene].meshes[settings.selectedMesh - 1].subdivide();

}
