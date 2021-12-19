#include "SpriteRenderer.hpp"
#include "Component.hpp"

Mayhem::ECS::Components::SpriteRenderer::~SpriteRenderer() {
    /* glDeleteVertexArrays(1, &VAO); */
    /* glDeleteBuffers(1, &VBO); */
    /* glDeleteBuffers(1, &EBO); */
    /* delete vertices; */
    /* delete indices; */
}


Mayhem::ECS::Components::SpriteRenderer::SpriteRenderer(Mayhem::Utils::Shader* shader, Math::Vector4f color): shader(shader), color(color) {
    CreateRect();
}

void Mayhem::ECS::Components::SpriteRenderer::genRectVertices() {
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

void Mayhem::ECS::Components::SpriteRenderer::genRectIndices() {
    indices[0] = 0;
    indices[1] = 2;
    indices[2] = 1;
    indices[3] = 3;
    indices[4] = 2;
    indices[5] = 1;
}

void Mayhem::ECS::Components::SpriteRenderer::CreateRect() {
    isRect = true;
    
    if (wasInitialized) { return; }
    if (!isRect || isTriangle) { return; }

    wasInitialized = true;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    vertices = new float[28];
    indices = new unsigned int[6];

    genRectVertices();
    genRectIndices();

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 28 * sizeof(float), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(float), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Mayhem::ECS::Components::SpriteRenderer::DrawRect() {
    if (!isRect || isTriangle) {return;}

    /* genRectVertices(); */

    /* glBindBuffer(GL_ARRAY_BUFFER, VBO); */
    /* glBufferData(GL_ARRAY_BUFFER, 28 * sizeof(float), vertices, GL_DYNAMIC_DRAW); */

    shader->sendMat4("model", gameObject->transform->getTransformMatrix());

    glBindVertexArray(VAO);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    glBindVertexArray(0);
}

void DrawTriangle();
void CreateTriangle();
