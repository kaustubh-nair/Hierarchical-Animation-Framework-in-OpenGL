#include "../include/scene_node.h"


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
