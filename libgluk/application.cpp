#include "./gluk/application.h"

namespace gluk
{
    application::application()
    {
        if (glfwInit() != GL_TRUE)
            throw std::runtime_error("failed to initialize glfw");

        glfwSetErrorCallback([](int err, const char *desc) {
            std::cerr << "GLFW error [" << err << "] :" << desc << std::endl;
            });
    }

    void application::initGlew()
    {
        glewExperimental = GL_TRUE;
        if (glewInit() != GLEW_OK)
            throw std::runtime_error("failed to initialize glew");

        // remove all errors
        GLenum err;
        while ((err = glGetError()) != GL_NO_ERROR)
        {
        }
    }

    application::~application()
    {
        glfwTerminate();
    }
}
