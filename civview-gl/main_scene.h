#pragma once

#include "./scene.h"
#include "./hextile.h"

class main_scene : public scene
{
public:
    main_scene();
    virtual ~main_scene();

    virtual void render(const glm::mat4& projMatrix, const glm::mat4 &viewMatrix) override;

private:
    hextile m_tri;
};
