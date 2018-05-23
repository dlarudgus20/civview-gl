#pragma once

#include "./glukdef.h"
#include "./shader.h"

namespace gluk
{
    class shader_manager final
    {
    public:
        static shader_manager& getInst();

        static void init()
        {
            getInst().initialize();
        }
        static shader& get(int index)
        {
            return getInst().getShader(index);
        }

        static shader& get_shader()
        {
            return get(SHADER);
        }

    private:
        shader_manager() = default;

    public:
        enum
        {
            SHADER,

            COUNT_SHADER
        };

        void initialize();
        shader& getShader(int index);

    private:
        std::array<shader, COUNT_SHADER> m_arShader;
    };
}
