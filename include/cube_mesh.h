#ifndef CUBE_MESH_H
#define CUBE_MESH_H

class CubeMesh
{
public:
    CubeMesh();
    ~CubeMesh();

    void Bind() const;

    unsigned int GetIndexCount() const;

private:
    unsigned int vbo_ = 0;
    unsigned int vao_ = 0;
    unsigned int ebo_ = 0;
    unsigned int index_count_ = 36;
};

#endif //CUBE_MESH_H
