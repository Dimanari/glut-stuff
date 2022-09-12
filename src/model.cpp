#include "model.hpp"

namespace dimanari
{
SimpleMesh::SimpleMesh(vector<Vertex> vertices_, Texture_ texture_) : buffer(0)
{
    this->vertices = vertices_;
    this->indices.clear();
	for(unsigned int i = 0; i < vertices.size(); ++i)
	{
		indices.push_back(i);
	}
    this->texture = texture_;

    setupMesh();

    glm::mat4 mat = glm::mat4(1);
    VectorSetup(&mat, 1);
    BindTransformationBuffer();
}

void SimpleMesh::setupMesh()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
  
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);  

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), 
                 &indices[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);	
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);	
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);	
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    glBindVertexArray(0);
}

void SimpleMesh::VectorSetup(glm::mat4 *vector, unsigned int amount)
{
    if(0 == buffer)
        glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, amount * sizeof(glm::mat4), vector, GL_STATIC_DRAW);
}

void SimpleMesh::Draw(Shader &shader) 
{
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;

	glActiveTexture(GL_TEXTURE0);
	shader.setInt((texture.type).c_str(), 0);
	glBindTexture(GL_TEXTURE_2D, texture.id);
   
    glActiveTexture(GL_TEXTURE0);

    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
} 

void SimpleMesh::DrawInst(Shader& instShader, GLsizei amount)
{
	instShader.use();
	glBindVertexArray(VAO);
    glDrawElementsInstanced(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0, amount);
	glBindVertexArray(0);
}

void SimpleMesh::BindTransformationBuffer()
{
    glBindVertexArray(VAO);
    // vertex attributes
    std::size_t vec4Size = sizeof(glm::vec4);
    glEnableVertexAttribArray(3); 
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(0));
    glEnableVertexAttribArray(4); 
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(1 * vec4Size));
    glEnableVertexAttribArray(5); 
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * vec4Size));
    glEnableVertexAttribArray(6); 
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * vec4Size));

    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);
    glVertexAttribDivisor(6, 1);

    glBindVertexArray(0);
}
}