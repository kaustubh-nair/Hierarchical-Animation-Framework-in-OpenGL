#include "../include/model.h"


Model::Model()
{
    sceneRoot = new GroupNode(0);
}

void Model::setup(Shader shader)
{
    sceneRoot->setup(shader);
}

void Model::addGroupNode(int id, int parentId)
{
    SceneNode *newNode = new GroupNode(id);
    sceneRoot = SceneNode::insertNode(id, parentId, newNode, sceneRoot);
}


// REMOVE?
void Model::addCameraGroupNode(int id, int parentId)
{
    SceneNode *newNode = new CameraGroupNode(id);
    sceneRoot = SceneNode::insertNode(id, parentId, newNode, sceneRoot);
}


void Model::addMeshNode(int id, int parentId, std::string meshPath,
                           std::string texturePath, glm::mat4 translationMat)
{
    SceneNode *newNode = new MeshNode(id, meshPath, texturePath,
                                      translationMat);
    sceneRoot = SceneNode::insertNode(id, parentId, newNode, sceneRoot);
}


void Model::addCameraNode(int id, int parentId, glm::vec3 position,
                          glm::vec3 front, glm::vec3 up)
{
    SceneNode *newNode = new CameraNode(id, position, front, up);
    sceneRoot = SceneNode::insertNode(id, parentId, newNode, sceneRoot);

    if(!firstCameraId) { firstCameraId = id; }
    numCameras++;
}


void Model::addLightNode(int id, int parentId, glm::vec3 position)
{
    SceneNode *newNode = new LightNode(id, position);
    sceneRoot = SceneNode::insertNode(id, parentId, newNode, sceneRoot);
}


CameraNode* Model::getCamera(int camId)
{
    /* Note: this assumes camera group node is always the second child of root */
    CameraGroupNode *cameraGroup = (CameraGroupNode *)(sceneRoot->children).at(1);
    return cameraGroup->getCamera(camId);
}

void Model::render(Shader shader)
{
    if(sceneRoot == nullptr)
    {
        print("No objects in scene!\n");
        exit(0);
    }
    else
    {
        std::vector <glm::mat4> stack;
        sceneRoot->render(shader, &stack);
    }
}

void Model::update(int timer, int event, int eventTargetId)
{
    sceneRoot->update(timer, event, eventTargetId);
}


void Model::drawLighting(Shader shader, Shader lightingShader)
{
    /*
    glm::vec3 lightPos = glm::vec3(15.0f, 0.0f, -2.0f);

    shader.setVec3("lights[0].Pos",lightPos.x, lightPos.y, lightPos.z);
    shader.setFloat("lights[0].diffuseStrength",0.0f);
    shader.setFloat("lights[0].specularStrength",4.0f);
    lightPos = glm::vec3(-1.2f, 1.2f, -2.0f);
    shader.setVec3("lights[1].Pos",lightPos.x, lightPos.y, lightPos.z);
    shader.setFloat("lights[1].diffuseStrength",0.5f);
    shader.setFloat("lights[1].specularStrength",0.0f);


    Lighting lighting;
    lighting.draw(lightingShader, lightPos);
    */
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
