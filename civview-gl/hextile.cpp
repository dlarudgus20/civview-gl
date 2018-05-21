#include "pch.h"
#include "./hextile.h"

namespace
{
    GLfloat vertices[] = {
        // position, normal, texture
        -0.25f, +0.43f, 0.0f,   0.0f, 0.0f, 1.0f,   0.36f, 1.00f,
        -0.50f, +0.00f, 0.0f,   0.0f, 0.0f, 1.0f,   0.21f, 0.50f,
        -0.25f, -0.43f, 0.0f,   0.0f, 0.0f, 1.0f,   0.36f, 0.00f,

        -0.25f, +0.43f, 0.0f,   0.0f, 0.0f, 1.0f,   0.36f, 1.00f,
        -0.25f, -0.43f, 0.0f,   0.0f, 0.0f, 1.0f,   0.36f, 0.00f,
        +0.25f, -0.43f, 0.0f,   0.0f, 0.0f, 1.0f,   0.64f, 0.00f,

        -0.25f, +0.43f, 0.0f,   0.0f, 0.0f, 1.0f,   0.36f, 1.00f,
        +0.25f, -0.43f, 0.0f,   0.0f, 0.0f, 1.0f,   0.64f, 0.00f,
        +0.25f, +0.43f, 0.0f,   0.0f, 0.0f, 1.0f,   0.64f, 1.00f,

        +0.25f, +0.43f, 0.0f,   0.0f, 0.0f, 1.0f,   0.64f, 1.00f,
        +0.25f, -0.43f, 0.0f,   0.0f, 0.0f, 1.0f,   0.64f, 0.00f,
        +0.50f, +0.00f, 0.0f,   0.0f, 0.0f, 1.0f,   0.79f, 1.00f,
    };
    GLsizei strides = 8 * sizeof(GLfloat);
}

hextile::hextile()
{
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);

    glBindVertexArray(m_vao);
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, strides, (GLvoid*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, strides, (GLvoid*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, strides, (GLvoid*)(6 * sizeof(GLfloat)));
        glEnableVertexAttribArray(2);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    glBindVertexArray(0);
}

hextile::~hextile()
{
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
}

void hextile::draw() const
{
    glDisable(GL_CULL_FACE);

    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / strides);
    glBindVertexArray(0);
}
