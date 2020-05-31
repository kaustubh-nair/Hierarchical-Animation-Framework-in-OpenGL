#include "../../include/scene_node/scene_node.h"


// TODO: exit recursion stack if node inserted. Convert to iteration?
/* Pre order traversal to insert a node */
SceneNode* SceneNode::insertNode(int nodeId, int parentId, SceneNode *newNode, SceneNode *root )
{
    if(root == nullptr)
        return root;

    if(root->id == parentId)
    {
        (root->children).push_back(newNode);
    }
    else
    {
        for(auto itr = (root->children).begin(); itr != (root->children).end(); itr++)
            *itr = insertNode(nodeId, parentId, newNode, *itr);
    }
    return root;

}
void SceneNode::addConnection(SceneNode *node)
{
    connections.push_back(node);
}

void SceneNode::toggleActive()
{
    active = true;
    for(auto itr = children.begin(); itr != children.end(); itr++)
        (*itr)->toggleActive();

}

void SceneNode::toggleInActive()
{
    active = false;
}


SceneNode* SceneNode::findNodeByID(int Id)
{
    for(auto itr = children.begin(); itr != children.end(); itr++)
    {
        if((*itr)->id == Id)
            return *itr;
    }

    SceneNode *ret;
    for(auto itr = children.begin(); itr != children.end(); itr++)
    {
        ret = (*itr)->findNodeByID(Id);
        if(ret != nullptr)
            return ret;
    }
    return nullptr;
}

void SceneNode::deleteChildByID(int ID)
{
    for(auto itr = children.begin(); itr != children.end(); itr++)
    {
        if((*itr)->id == ID)
            children.erase(itr);
    }
}

