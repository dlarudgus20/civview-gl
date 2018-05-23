#include "pch.h"
#include "./main_scene.h"

#include "../libgluk/gluk/shader.h"
#include "./mainwnd.h"

main_scene::main_scene(mainwnd* wnd)
    : m_wnd(wnd)
{
    wnd->connect_idle(boost::bind(&main_scene::onIdle, this));
}

main_scene::~main_scene() = default;

void main_scene::render(const glm::mat4& projMatrix)
{
    auto shader = gluk::shader::getCurrentShader();

    glm::mat4 vmMatrix = m_cam.getMatrix();

    shader->setUniformMatrix4f("projMatrix", projMatrix);
    shader->setUniformMatrix4f("vmMatrix", vmMatrix);
    m_tri.draw();
}

void main_scene::onIdle()
{
    const float unit = 2.5f;

    int front = 0, right = 0;
    front += glfwGetKey(*m_wnd, GLFW_KEY_W) == GLFW_PRESS ? 1 : 0;
    front += glfwGetKey(*m_wnd, GLFW_KEY_S) == GLFW_PRESS ? -1 : 0;
    right += glfwGetKey(*m_wnd, GLFW_KEY_D) == GLFW_PRESS ? 1 : 0;
    right += glfwGetKey(*m_wnd, GLFW_KEY_A) == GLFW_PRESS ? -1 : 0;

    m_cam.move(front, right,
        static_cast<float>(unit * m_wnd->getDeltaTime()));
}
