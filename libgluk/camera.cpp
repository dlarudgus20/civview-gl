#include "./gluk/camera.h"

namespace gluk
{
    camera::camera()
        : m_position(0, 0, 10), m_distance(10), m_pitch(0.0f), m_yaw(0.0f)
    {
        calculate();
    }

    camera::~camera() = default;

    const glm::mat4 &camera::getMatrix() const
    {
        return m_matrix;
    }

    float camera::getPitch() const
    {
        return m_pitch;
    }

    float camera::getYaw() const
    {
        return m_yaw;
    }

    void camera::setPitchYaw(float pitch, float yaw)
    {
        m_pitch = pitch;
        m_yaw = yaw;

        calculate();
    }

    void camera::move(int front, int right, float unit)
    {
        m_position += front * unit * m_up;
        m_position += right * unit * m_right;
        calculate();
    }

    void camera::calculate()
    {
        float sin_pitch = std::sin(m_pitch);
        float cos_pitch = std::cos(m_pitch);
        float sin_yaw = std::sin(m_yaw - glm::pi<float>() / 2);
        float cos_yaw = std::cos(m_yaw - glm::pi<float>() / 2);

        m_front = glm::vec3(
            cos_pitch * cos_yaw,
            sin_pitch,
            cos_pitch * sin_yaw
        );

        m_right = glm::normalize(glm::cross(m_front, glm::vec3(0, 1, 0)));
        m_up = glm::cross(m_right, m_front);

        m_matrix = glm::lookAt(m_position, m_position + m_distance * m_front, m_up);
    }
}
