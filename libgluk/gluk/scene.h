#pragma once

#include "./glukdef.h"

namespace gluk
{
    class scene
    {
    public:
        virtual ~scene() = default;

        virtual void render(const glm::mat4& projMatrix) = 0;
    };
}
