#pragma once

inline void shader::setUniform1f(const char *var, GLfloat f)
{
    glUniform1f(findUniform(var), f);
}
inline void shader::setUniform1f(const std::string &var, GLfloat f)
{
    setUniform1f(var.c_str(), f);
}

inline void shader::setUniform3f(const char *var, const glm::vec3 &vec3)
{
    glUniform3fv(findUniform(var), 1, glm::value_ptr(vec3));
}
inline void shader::setUniform3f(const std::string &var, const glm::vec3 &vec3)
{
    setUniform3f(var.c_str(), vec3);
}

inline void shader::setUniform4f(const char *var, const glm::vec4 &vec4)
{
    glUniform4fv(findUniform(var), 1, glm::value_ptr(vec4));
}
inline void shader::setUniform4f(const std::string &var, const glm::vec4 &vec4)
{
    setUniform4f(var.c_str(), vec4);
}

inline void shader::setUniform1i(const char *var, GLint i)
{
    glUniform1i(findUniform(var), i);
}
inline void shader::setUniform1i(const std::string &var, GLint i)
{
    setUniform1i(var.c_str(), i);
}

inline void shader::setUniformMatrix3f(const char *var, const glm::mat3 &mat)
{
    glUniformMatrix3fv(findUniform(var), 1, GL_FALSE, glm::value_ptr(mat));
}
inline void shader::setUniformMatrix3f(const std::string &var, const glm::mat3 &mat)
{
    setUniformMatrix3f(var.c_str(), mat);
}

inline void shader::setUniformMatrix4f(const char *var, const glm::mat4 &mat)
{
    glUniformMatrix4fv(findUniform(var), 1, GL_FALSE, glm::value_ptr(mat));
}
inline void shader::setUniformMatrix4f(const std::string &var, const glm::mat4 &mat)
{
    setUniformMatrix4f(var.c_str(), mat);
}
