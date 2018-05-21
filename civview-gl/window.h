#pragma once

#include <string_view>

class window
{
public:
    window(int width, int height, const char* title);
    virtual ~window();

    void initialize();
    void loop(int expectedFPS = 60);

    int getFPS() const;
    operator GLFWwindow*() const;

protected:
    virtual void onInitialize();
    virtual void onRender();
    virtual void onIdle();

    virtual void onMouseCursorPos(double xpos, double ypos);
    virtual void onFrameBufferSize(int width, int height);
    virtual void onWindowClose();

private:
    void initCallback();
    void adjustViewport();

    GLFWwindow* m_wnd;

    double m_startTime;
    double m_frameTime;
    double m_prevFrameTime;
    double m_remainTime;
    double m_fpsResetTime;
    int m_tmpfps;

    double m_deltaTime = 0.0;
    int m_fps = 0;

    GLsizei m_width = 0;
    GLsizei m_height = 0;
};
