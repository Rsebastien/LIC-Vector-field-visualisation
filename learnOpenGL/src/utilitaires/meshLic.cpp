#include <glad/glad.h>
#include "../utilitaires/Structures.h"
#include "../utilitaires/Shader.h"
#include "meshLic.h"
using namespace std;

MeshLic::MeshLic(vector<Vertex> sommets, vector<unsigned int> indices) {
    this->sommets = sommets;
    this->indices = indices;
    setUpMesh();
}

MeshLic::~MeshLic(){
    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
    glDeleteBuffers(1,&EBO);
}

void MeshLic::draw(Shader &shader) {
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES,static_cast<unsigned int>(indices.size()),GL_UNSIGNED_INT,0);
    glBindVertexArray(0);
}



void MeshLic::setUpMesh() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    //VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sommets.size() * sizeof(Vertex), &sommets[0], GL_STATIC_DRAW);
    //EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    //Set the vertex attribute pointers
    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, UV));

    glBindVertexArray(0);
}