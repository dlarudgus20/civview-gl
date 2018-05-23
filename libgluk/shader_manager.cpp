#include "./gluk/shader_manager.h"

namespace gluk
{
    shader_manager &shader_manager::getInst()
    {
        static shader_manager obj;
        return obj;
    }

    shader& shader_manager::getShader(int index)
    {
        return m_arShader.at(index);
    }

    void shader_manager::initialize()
    {
        auto doCompile = [](shader &shader, const char* vs, const char* fs, const char* name) {
            std::cout << "->compile shader (" << name << ")" << std::endl;
            shader.compile(vs, fs);
            std::cout << ">vertex shader info:\n" << shader.getVSInfoString() << std::endl;
            std::cout << ">fragment shader info:\n" << shader.getFSInfoString() << std::endl;
        };
        auto doCompile2 = [doCompile](shader& shader, const char* name) {
            using namespace std::literals;
            doCompile(shader,
                ("shaders/"s + name + ".vert").c_str(),
                ("shaders/"s + name + ".frag").c_str(), name);
        };

        try
        {
            doCompile2(m_arShader[SHADER], "shader");
        }
        catch (shader::CompileError& e)
        {
            std::cerr << "##compile error##\n" << e.what() << std::endl;
            throw;
        }
        catch (shader::LinkError& e)
        {
            std::cerr << "##link error##\n" << e.what() << std::endl;
            throw;
        }
    }
}
