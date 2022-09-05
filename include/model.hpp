#ifndef DIMA_PROJ_MODEL_HPP
#define DIMA_PROJ_MODEL_HPP
#include "GL_include.hpp"
#include <string>
#include <vector>
#include "shader.hpp"
using std::string;
using std::vector;
namespace dimanari
{
struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};
struct Texture_ {
    unsigned int id;
    string type;
};

class Mesh {
    public:
        // mesh data
        vector<Vertex>       vertices;
        vector<unsigned int> indices;
        vector<Texture_>      textures;

        Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture_> textures);
        void Draw(Shader &shader);
    private:
        //  render data
        unsigned int VAO, VBO, EBO;

        void setupMesh();
};  

class SimpleMesh
{
    public:
        SimpleMesh(vector<Vertex> vertices, Texture_ texture);
        void Draw(Shader &shader);
		void DrawInst(Shader& instShader, GLsizei amount);
		void BindTransformationBuffer();
        void VectorSetup(glm::mat4 *vector, unsigned int amount);
    private:
        // mesh data
        vector<Vertex> vertices;
        vector<unsigned int> indices;
        Texture_ texture;
        //  render data
        unsigned int VAO, VBO, EBO, buffer;

        void setupMesh();
};

}
#endif //!DIMA_PROJ_MODEL_HPP