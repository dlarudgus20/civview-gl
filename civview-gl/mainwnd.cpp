#include "pch.h"
#include "./mainwnd.h"

#include "../libgluk/gluk/shader_manager.h"
#include "./main_scene.h"

mainwnd::mainwnd()
    : window(800, 600, "civview-gl")
{
}

mainwnd::~mainwnd() = default;

void mainwnd::onInitialize()
{
    glfwSetInputMode(*this, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    window::onInitialize();

    gluk::shader_manager::init();

    m_pScene = std::make_unique<main_scene>(this);

    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_FRAMEBUFFER_SRGB);
}

void mainwnd::onRender()
{
    window::onRender();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    gluk::shader_manager::get_shader().use();
    if (m_pScene)
        m_pScene->render(m_projection);

    glfwSwapBuffers(*this);
}

void mainwnd::onIdle()
{
    window::onIdle();
}

void mainwnd::onFrameBufferSize(int width, int height)
{
    window::onFrameBufferSize(width, height);

    float aspect = static_cast<float>(width) / height;

    m_projection = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 100.0f);
}
