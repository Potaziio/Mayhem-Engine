#include "Rect.hpp"

Mayhem::Draw::Sprite2D::Rect::~Rect() {
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);
}

void Mayhem::Draw::Sprite2D::Rect::generateVertices() {
    vertices[0] = 0.0f;
    vertices[1] = 0.0f;
    vertices[2] = 0.0f;
    vertices[3] = color.x;
    vertices[4] = color.y;
    vertices[5] = color.z;
    vertices[6] = color.w;

    vertices[7] = 1.0f;
    vertices[8] = 0.0f;
    vertices[9] = 0.0f;
    vertices[10] = color.x;
    vertices[11] = color.y;
    vertices[12] = color.z;
    vertices[13] = color.w;

    vertices[14] = 0.0f;
    vertices[15] = 1.0f;
    vertices[16] = 0.0f;
    vertices[17] = color.x;
    vertices[18] = color.y;
    vertices[19] = color.z;
    vertices[20] = color.w;

    vertices[21] = 1.0f;
    vertices[22] = 1.0f;
    vertices[23] = 0.0f;
    vertices[24] = color.x;
    vertices[25] = color.y;
    vertices[26] = color.z;
    vertices[27] = color.w;
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
    glBufferSubData(GL_ARRAY_BUFFER, 0, 28 * sizeof(float), vertices);
}

void Mayhem::Draw::Sprite2D::Rect::setupVBO() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 28 * sizeof(float), vertices, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(float), indices, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Mayhem::Draw::Sprite2D::Rect::init() {
    generateVertices();
    generateIndices();
    setupVBO();
}

void Mayhem::Draw::Sprite2D::Rect::render() {
    glBindVertexArray(VAO);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    glBindVertexArray(0);
}
