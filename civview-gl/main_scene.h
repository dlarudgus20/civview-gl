#pragma once

#include "../libgluk/gluk/scene.h"
#include "../libgluk/gluk/camera.h"
#include "./hextile.h"

class mainwnd;

class main_scene : public gluk::scene
{
public:
    main_scene(mainwnd* wnd);
    virtual ~main_scene();

    virtual void render(const glm::mat4& projMatrix) override;

private:
    void onIdle();

    mainwnd* m_wnd;
    gluk::camera m_cam;

    hextile m_tri;
};
