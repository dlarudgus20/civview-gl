#pragma once

#include "../libgluk/gluk/window.h"
#include "../libgluk/gluk/camera.h"
#include "../libgluk/gluk/scene.h"

class mainwnd : public gluk::window
{
public:
    mainwnd();
    virtual ~mainwnd();

protected:
    virtual void onInitialize() override;
    virtual void onRender() override;
    virtual void onIdle() override;

    virtual void onFrameBufferSize(int width, int height) override;

private:
    std::unique_ptr<gluk::scene> m_pScene;

    glm::mat4 m_projection;
    glm::mat4 m_view;
};
