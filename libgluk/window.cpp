#include "./gluk/window.h"

namespace gluk
{
    window::window(int width, int height, const char* title)
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
        m_wnd = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (!m_wnd)
            throw std::runtime_error("window creation failed");

        glfwSetWindowUserPointer(m_wnd, this);
        glfwMakeContextCurrent(m_wnd);
    }

    window::~window() = default;

    void window::initialize()
    {
        glfwMakeContextCurrent(m_wnd);
        initCallback();

        int width, height;
        glfwGetFramebufferSize(m_wnd, &width, &height);
        m_width = static_cast<GLsizei>(width);
        m_height = static_cast<GLsizei>(height);

        onInitialize();

        onFrameBufferSize(width, height);
    }

    void window::loop(int expectedFPS /* = 60 */)
    {
        auto timeStr = [](double time) {
            int s = static_cast<int>(time);
            char buf[11];
            int hour = s / 3600;
            int minutes = (s % 3600) / 60;
            int seconds = s % 60;
            std::snprintf(buf, 11, "[%02d:%02d:%02d]", hour, minutes, seconds);
            return std::string(buf);
        };

        const double expectedDelta = 1.0 / expectedFPS;

        m_startTime = glfwGetTime();
        m_frameTime = m_startTime;
        m_remainTime = 0;
        m_tmpfps = 0;

        m_fpsResetTime = m_startTime + 1.0;

        while (!glfwWindowShouldClose(m_wnd))
        {
            glfwPollEvents();

            if (m_remainTime <= 0.0f)
            {
                onRender();
                m_tmpfps++;
            }

            onIdle();

            m_prevFrameTime = m_frameTime;
            m_frameTime = glfwGetTime();
            m_deltaTime = m_frameTime - m_prevFrameTime;

            if (m_fpsResetTime <= m_frameTime)
            {
                m_fps = m_tmpfps;
                m_tmpfps = 0;
                m_fpsResetTime += 1.0;
                std::cout << timeStr(m_frameTime) << " fps: " << m_fps << std::endl;
            }

            if (m_remainTime <= 0.0f)
            {
                m_remainTime += expectedDelta - m_deltaTime;
            }
            else
            {
                m_remainTime -= m_deltaTime;
            }
        }
    }

    double window::getDeltaTime() const
    {
        return m_deltaTime;
    }

    int window::getFPS() const
    {
        return m_fps;
    }

    window::operator GLFWwindow*() const
    {
        return m_wnd;
    }

    void window::initCallback()
    {
#define THIZ static_cast<window*>(glfwGetWindowUserPointer(wnd))
        glfwSetFramebufferSizeCallback(m_wnd, [](GLFWwindow* wnd, int width, int height) {
            glfwMakeContextCurrent(wnd);
            THIZ->onFrameBufferSize(width, height);
            });
        glfwSetWindowCloseCallback(m_wnd, [](GLFWwindow* wnd) {
            glfwMakeContextCurrent(wnd);
            THIZ->onWindowClose();
            });
        glfwSetCursorPosCallback(m_wnd, [](GLFWwindow* wnd, double xpos, double ypos) {
            glfwMakeContextCurrent(wnd);
            THIZ->onMouseCursorPos(xpos, ypos);
            });
#undef THIZ
    }

    void window::onInitialize()
    {
    }

    void window::onRender()
    {
    }

    void window::onIdle()
    {
        m_sig_idle();
    }

    void window::onMouseCursorPos(double xpos, double ypos)
    {
    }

    void window::onFrameBufferSize(int width, int height)
    {
        // 최소화 상태일땐 width == height == 0임.
        if (!(width == 0 || height == 0))
        {
            m_width = static_cast<GLsizei>(width);
            m_height = static_cast<GLsizei>(height);

            glViewport(0, 0, width, height);
        }
    }

    void window::onWindowClose()
    {
    }
}
