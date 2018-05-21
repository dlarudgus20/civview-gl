#pragma once

#include "window.h"

class scene;

class mainwnd : public window
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
    std::unique_ptr<scene> m_pScene;

    glm::mat4 m_projection;
    glm::mat4 m_view;
};
