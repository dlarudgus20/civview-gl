#include "pch.h"
#include "./shader.h"

namespace
{
    shader *pCurrentShader = nullptr;
}

shader *shader::getCurrentShader()
{
    return pCurrentShader;
}

shader::shader()
    : m_vertexShader(0), m_fragmentShader(0)
{
}

shader::~shader()
{
    glDeleteShader(m_vertexShader);
    glDeleteShader(m_fragmentShader);
    glDeleteProgram(m_shaderProgram);

    if (pCurrentShader == this)
        pCurrentShader = nullptr;
}

void shader::compile(const char *vertex, const char *fragment)
{
    assert(m_vertexShader == 0 && m_fragmentShader == 0);

    m_vertexShader = loadFile(vertex, GL_VERTEX_SHADER, m_vsInfoString);
    m_fragmentShader = loadFile(fragment, GL_FRAGMENT_SHADER, m_fsInfoString);

    m_shaderProgram = glCreateProgram();
    glAttachShader(m_shaderProgram, m_vertexShader);
    glAttachShader(m_shaderProgram, m_fragmentShader);
    glLinkProgram(m_shaderProgram);

    GLint success;
    glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);

    GLint size;
    glGetProgramiv(m_shaderProgram, GL_INFO_LOG_LENGTH, &size);
    std::string info(size, '\0');
    glGetProgramInfoLog(m_shaderProgram, size, nullptr, &info[0]);
    boost::trim(info);

    m_linkInfoString = info;

    if (!success)
        throw LinkError("[vs: " + std::string(vertex) + " fs: " + fragment + "] : \n" + info);
}

void shader::use()
{
    glUseProgram(m_shaderProgram);
    pCurrentShader = this;
}

const std::string &shader::getVSInfoString()
{
    return m_vsInfoString;
}

const std::string &shader::getFSInfoString()
{
    return m_fsInfoString;
}

const std::string &shader::getLinkInfoString()
{
    return m_linkInfoString;
}

GLint shader::findUniform(const char *var)
{
    GLint loc = glGetUniformLocation(m_shaderProgram, var);
    if (loc == -1)
        throw UniformError("cannot find '" + std::string(var) + "' uniform variable.");
    return loc;
}

GLuint shader::loadFile(const char *filename, GLuint shaderType, std::string &infoString)
{
    try
    {
        std::ifstream file;
        file.exceptions(std::ios::badbit);
        file.open(filename);

        if (!file.is_open())
            throw CompileError("[" + std::string(filename) + "] I/O Error : file doesn't exist");

        std::string strSource;
        std::copy(std::istreambuf_iterator<char> { file }, std::istreambuf_iterator<char> { },
            std::back_inserter(strSource));

        const GLchar *src = strSource.c_str();
        GLuint shader = glCreateShader(shaderType);
        glShaderSource(shader, 1, &src, nullptr);
        glCompileShader(shader);

        GLint success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        GLint size;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &size);
        std::string info(size, '\0');
        glGetShaderInfoLog(shader, size, nullptr, &info[0]);
        boost::trim(info);

        infoString = info;

        if (success)
        {
            return shader;
        }
        else
        {
            throw CompileError("[" + std::string(filename) + "] : \n" + info);
        }
    }
    catch (std::ios::failure &e)
    {
        throw CompileError("[" + std::string(filename) + "] I/O Error : " + e.what());
    }
}
