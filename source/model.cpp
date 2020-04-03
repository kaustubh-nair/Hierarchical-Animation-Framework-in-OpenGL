#include "../include/model.h"

Model::Model()
{
    selectedMesh = -1;
    renderSplats = false;
}

void Model::setup(std::vector<std::string> filepaths, std::vector<glm::vec3> meshPos, std::vector<std::string> texturePaths)
{
    std::vector<std::string>::iterator filepath;
    std::vector<glm::vec3>::iterator position = meshPos.begin();
    std::vector<std::string>::iterator texturePath = texturePaths.begin();

    for (filepath = filepaths.begin(); filepath < filepaths.end(); filepath++)
    {
        Mesh mesh(*filepath, *position, *texturePath);
        mesh.setup();
        meshes.push_back(mesh);

        position++;
        texturePath++;
    }

}

/* refresh for rendering splats */
void Model::refresh()
{
    std::vector<Mesh>::iterator mesh;

    for (mesh = meshes.begin(); mesh < meshes.end(); mesh++)
    {
        if(this->renderSplats)
            mesh->setupSplats();
        else
            mesh->setup();
    }
}

void Model::draw(Shader shader, Shader lightingShader)
{
    std::vector<Mesh>::iterator mesh;

    for (mesh = meshes.begin(); mesh < meshes.end(); mesh++)
    {
        if(this->renderSplats)
            mesh->drawSplats(shader);
        else
            mesh->draw(shader);
    }
    Lighting lighting;
    lighting.draw(lightingShader);
}


void Model::unselect()
{
    std::vector<Mesh>::iterator mesh;

    for (mesh = meshes.begin(); mesh < meshes.end(); mesh++)
    {
        if(mesh->id == this->selectedMesh)
        {
            mesh->selected = false;
            break;
        }
    }
    this->selectedMesh = -1;
}

void Model::select(int id)
{
    if(this->selectedMesh != -1)
        return;
    this->selectedMesh = id;

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
    if(this->selectedMesh == -1)
        return;
    meshes[this->selectedMesh - 1].translate(direction);
}

void Model::scale(int direction)
{
    if(this->selectedMesh == -1)
        return;

    meshes[this->selectedMesh - 1].scale(direction);
}

void Model::rotate(glm::vec2 direction)
{
    if(this->selectedMesh == -1)
        return;
    meshes[this->selectedMesh - 1].rotate(direction);

}

void Model::changeSplatRadius(int direction)
{
    if(this->selectedMesh == -1)
        return;
    meshes[this->selectedMesh - 1].changeSplatRadius(direction);
}

