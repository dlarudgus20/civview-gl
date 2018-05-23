#pragma once

#include "./glukdef.h"

namespace gluk
{
    class shader
    {
    public:
        static shader *getCurrentShader();

        shader(const shader&) = delete;
        shader& operator =(const shader&) = delete;

    private:
        GLuint m_vertexShader = 0, m_fragmentShader = 0;
        GLuint m_shaderProgram = 0;

        std::string m_vsInfoString, m_fsInfoString, m_linkInfoString;

    public:
        shader();
        ~shader();

        void compile(const char *vertex, const char *fragment);
        void use();

        const std::string &getVSInfoString();
        const std::string &getFSInfoString();
        const std::string &getLinkInfoString();

        void setUniform1f(const char *var, GLfloat f);
        void setUniform1f(const std::string &var, GLfloat f);

        void setUniform3f(const char *var, const glm::vec3 &vec3);
        void setUniform3f(const std::string &var, const glm::vec3 &vec3);

        void setUniform4f(const char *var, const glm::vec4 &vec4);
        void setUniform4f(const std::string &var, const glm::vec4 &vec4);

        void setUniform1i(const char *var, GLint i);
        void setUniform1i(const std::string &var, GLint i);

        void setUniformMatrix3f(const char *var, const glm::mat3 &mat);
        void setUniformMatrix3f(const std::string &var, const glm::mat3 &mat);

        void setUniformMatrix4f(const char *var, const glm::mat4 &mat);
        void setUniformMatrix4f(const std::string &var, const glm::mat4 &mat);

        class CompileError : public std::runtime_error
        {
        public:
            explicit CompileError(const std::string &msg)
                : std::runtime_error(msg)
            {
            }
        };
        class LinkError : public std::runtime_error
        {
        public:
            explicit LinkError(const std::string &msg)
                : std::runtime_error(msg)
            {
            }
        };
        class UniformError : public std::runtime_error
        {
        public:
            explicit UniformError(const std::string &msg)
                : std::runtime_error(msg)
            {
            }
        };

    private:
        GLint findUniform(const char *var);

        static GLuint loadFile(const char *filename, GLuint kind, std::string &infoString);
    };
}

#include "./detail/shader_impl.h"
