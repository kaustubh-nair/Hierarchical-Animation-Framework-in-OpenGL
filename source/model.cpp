#include "../include/model.h"


Model::Model()
{
    sceneRoot = new GroupNode(0);
}

void Model::setup(Shader shader)
{
    sceneRoot->setup(shader);
}


void Model::addNode(SceneNode *node, int parentId)
{
    sceneRoot = SceneNode::insertNode(node->id, parentId, node, sceneRoot);
}


void Model::addCameraNode(SceneNode *node, int parentId)
{
    addNode(node, parentId);

    if(!firstCameraId) { firstCameraId = node->id; }
    numCameras++;

}


SceneNode* Model::addLightNode(int id, int parentId, glm::vec3 position, std::string meshPath, glm::vec3 direction, int type)
{
    SceneNode *newNode = new LightNode(id, position, numLights, meshPath, direction, type);
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

CameraGroupNode* Model::getCameraGroup()
{
    /* Note: this assumes camera group node is always the second child of root */
    return (CameraGroupNode *)(sceneRoot->children).at(1);

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

void Model::update(int timer, int event, int eventTargetNodeId, Shader shader, GLFWwindow *activeWindow)
{
    sceneRoot->update(timer, event, eventTargetNodeId, shader, false, glm::vec3(0.0f, 0.0f, 0.0f), activeWindow);
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

void Model::toggleObjectsActive()
{
    sceneRoot->toggleActive();

}


void Model::toggleObjectsInActive()
{
    sceneRoot->toggleInActive();

}
