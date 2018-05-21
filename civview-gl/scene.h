#pragma once

class scene
{
public:
    virtual ~scene() = default;

    virtual void render(const glm::mat4& projMatrix, const glm::mat4 &viewMatrix) = 0;
};
