#pragma once

class Cube
{
public:
    Cube();

    void Draw() const;
private:
    unsigned int vao_;
    unsigned int vbo_;
    unsigned int ebo_;
};