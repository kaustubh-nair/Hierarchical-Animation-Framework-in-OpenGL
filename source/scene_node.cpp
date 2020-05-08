#include "../include/scene_node.h"


// TODO: exit recursion stack if node inserted. Convert to iteration?
/* Pre order traversal to insert a node */
SceneNode* SceneNode::insertNode(int nodeId, int parentId, SceneNode *newNode, SceneNode *root )
{
    if(root == nullptr)
        return root;

    if(root->id == parentId)
    {
        if(root->leftChild == nullptr)
            root->leftChild = newNode;
        else
            root->rightChild = newNode;
    }
    else
    {
        root->leftChild = insertNode(nodeId, parentId, newNode, root->leftChild);
        root->rightChild = insertNode(nodeId, parentId, newNode, root->rightChild);
    }
    return root;

}
