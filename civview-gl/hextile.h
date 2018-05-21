#pragma once

class hextile
{
public:
    hextile(const hextile&) = delete;
    hextile& operator = (const hextile&) = delete;

    hextile();
    ~hextile();

    void draw() const;

private:
    GLuint m_vbo = 0;
    GLuint m_vao = 0;
};
