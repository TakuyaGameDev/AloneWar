#pragma once
#include <array>
#include "Obj.h"

enum class Wall
{
    // �E�̕�
    Right,
    // ���̕�
    Left,
    // ��
    Floor,
    // �V��
    Ceiling,
    // �w�i
    Back,
    Max
};
// �e�ǂ̒��_���̌^
using Vertexes = std::array<VERTEX_3D,6>;

class BackGround :
    public Obj
{
public:
    BackGround(Vector3F pos,Vector3F size,Wall wallType);
    ~BackGround();

    void Draw(void);
    void SetVertex(void);
private:
    // �e�ǂ̒��_�����i�[
    Vertexes vertexes_;
    Wall type_;
};

