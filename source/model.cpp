#include "../include/model.h"


Model::Model()
{
    sceneRoot = new GroupNode(0);
}

void Model::setup(Shader shader)
{
    sceneRoot->setup(shader);
}

SceneNode* Model::addGroupNode(int id, int parentId)
{
    SceneNode *newNode = new GroupNode(id);
    sceneRoot = SceneNode::insertNode(id, parentId, newNode, sceneRoot);

    return newNode;
}


// REMOVE?
SceneNode* Model::addCameraGroupNode(int id, int parentId)
{
    SceneNode *newNode = new CameraGroupNode(id);
    sceneRoot = SceneNode::insertNode(id, parentId, newNode, sceneRoot);

    return newNode;
}


SceneNode* Model::addMeshNode(int id, int parentId, std::string meshPath,
                           std::string texturePath, int mappingStyle, glm::mat4 translationMat,
                           glm::mat4 scalingMat, glm::mat4 rotationMat, glm::vec3 pos)
{
    SceneNode *newNode = new MeshNode(id, meshPath, texturePath, mappingStyle,
                                      translationMat, scalingMat,
                                      rotationMat, pos);
    sceneRoot = SceneNode::insertNode(id, parentId, newNode, sceneRoot);

    return newNode;
}


SceneNode* Model::addCameraNode(int id, int parentId, glm::vec3 position,
                          glm::vec3 front, glm::vec3 up)
{
    SceneNode *newNode = new CameraNode(id, position, front, up);
    sceneRoot = SceneNode::insertNode(id, parentId, newNode, sceneRoot);

    if(!firstCameraId) { firstCameraId = id; }
    numCameras++;

    return newNode;
}


SceneNode* Model::addLightNode(int id, int parentId, glm::vec3 position)
{
    SceneNode *newNode = new LightNode(id, position, numLights);
    sceneRoot = SceneNode::insertNode(id, parentId, newNode, sceneRoot);
    numLights++;

    return newNode;
}


void Model::addConnection(SceneNode *node1, SceneNode *node2)
{
    node1->addConnection(node2);
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
        shader.setInt("NUMBER_OF_LIGHTS", numLights);
        std::vector <glm::mat4> stack;
        sceneRoot->render(shader, &stack);
    }
}

void Model::update(int timer, int event, int eventTargetId, Shader shader)
{
    sceneRoot->update(timer, event, eventTargetId, shader);
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
