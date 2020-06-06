#ifndef MESH_NODE_H
#define MESH_NODE_H

#include "../../include/scene_node/target_node.h"

#include "../../include/stb_image.h"
#include "../../include/vertex.h"
#include "../../include/triangle.h"
#include "../../include/ply_parser.h"



class MeshNode : public SceneNode
{
    public:
        void render(Shader shader, std::vector<glm::mat4> *stack);
        void update(int timer, int event, int eventTargetNodeId, Shader shader, bool isConnection, glm::vec3 data, GLFWwindow *activeWindow) {};
        void setup(Shader shader);


        MeshNode(int nodeId, std::string meshPath, std::string texturePath,
                   glm::vec3 pos, glm::mat4 scalingMatrix,
                   glm::mat4 rotationMatrix, glm::mat4 selfScalingMatrix);


        TargetNode *target = nullptr; 
        glm::vec3 size = glm::vec3(2.0f, 2.0f, 2.0f);
    protected:
        glm::vec3 position;
        glm::vec3 front;
        glm::vec3 up;

        glm::mat4 translationMat;
        glm::mat4 rotationMat;
        glm::mat4 scalingMat;
        glm::mat4 selfScalingMat;
        
        glm::vec3 boundingSpherePos;
        float boundingSphereRad;
        float minimumSeperation(SceneNode *node);  //check for collision
    private:
        unsigned int VAO, VBO, EBO;
        unsigned int texture;
        std::vector<Vertex> vertices;
        std::vector<Triangle> triangles;
        void generateTextureObject();
        std::string texPath;

};

#endif
