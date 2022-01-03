#include "Rect.hpp"

Mayhem::Draw::Sprite2D::Rect::~Rect() {
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);
    
    delete vertices;
}

void Mayhem::Draw::Sprite2D::Rect::generateVertices() {
    vertices[0].position[0] = 0;
    vertices[0].position[1] = 0;
    vertices[0].position[2] = 0;
      
    vertices[0].color[0] = color.x;
    vertices[0].color[1] = color.y;
    vertices[0].color[2] = color.z; 
    vertices[0].color[3] = color.w;

    /* ---------------------------- */

    vertices[1].position[0] = 1;
    vertices[1].position[1] = 0;
    vertices[1].position[2] = 0;
      
    vertices[1].color[0] = color.x;
    vertices[1].color[1] = color.y;
    vertices[1].color[2] = color.z; 
    vertices[1].color[3] = color.w;

    /* ---------------------------- */

    vertices[2].position[0] = 0;
    vertices[2].position[1] = -1;
    vertices[2].position[2] = 0;
      
    vertices[2].color[0] = color.x;
    vertices[2].color[1] = color.y;
    vertices[2].color[2] = color.z; 
    vertices[2].color[3] = color.w;

    /* ---------------------------- */

    vertices[3].position[0] = 1;
    vertices[3].position[1] = -1;
    vertices[3].position[2] = 0;
      
    vertices[3].color[0] = color.x;
    vertices[3].color[1] = color.y;
    vertices[3].color[2] = color.z; 
    vertices[3].color[3] = color.w;

    /* ---------------------------- */
}

void Mayhem::Draw::Sprite2D::Rect::generateIndices() {
    indices[0] = 0;
    indices[1] = 2;
    indices[2] = 1;
    indices[3] = 3;
    indices[4] = 2;
    indices[5] = 1;
}

void Mayhem::Draw::Sprite2D::Rect::regenVBOAttributes() {
    generateVertices();
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * 4, vertices);
}

void Mayhem::Draw::Sprite2D::Rect::setupVBO() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 4, vertices, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(uint8_t), indices, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_BYTE, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_BYTE, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(int8_t)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Mayhem::Draw::Sprite2D::Rect::init() {
    vertices = new Vertex[sizeof(Vertex) * 4];
    generateVertices();
    generateIndices();
    setupVBO();
}

void Mayhem::Draw::Sprite2D::Rect::render() {
    glBindVertexArray(VAO);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    glBindVertexArray(0);
}
