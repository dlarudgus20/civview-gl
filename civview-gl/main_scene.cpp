#include "pch.h"
#include "./main_scene.h"

#include "./shader.h"

main_scene::main_scene() = default;
main_scene::~main_scene() = default;

void main_scene::render(const glm::mat4& projMatrix, const glm::mat4 &viewMatrix)
{
    auto shader = shader::getCurrentShader();

    glm::mat4 vmMatrix = viewMatrix;

    shader->setUniformMatrix4f("projMatrix", projMatrix);
    shader->setUniformMatrix4f("vmMatrix", viewMatrix);
    m_tri.draw();
}
