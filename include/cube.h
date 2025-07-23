#ifndef CUBE_H
#define CUBE_H

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

#endif // CUBE_H
