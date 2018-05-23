#pragma once

#include "./glukdef.h"

namespace gluk
{
    class camera final
    {
    public:
        camera(const camera&) = delete;
        camera& operator = (const camera&) = delete;

    private:
        glm::vec3 m_position;
        float m_distance;

        float m_pitch, m_yaw;
        glm::vec3 m_front, m_right, m_up;

        glm::mat4 m_matrix;

    public:
        camera();
        ~camera();

        const glm::mat4 &getMatrix() const;

        float getPitch() const;
        float getYaw() const;
        void setPitchYaw(float pitch, float yaw);

        void move(int front, int right, float unit);

    private:
        void calculate();
    };
}
