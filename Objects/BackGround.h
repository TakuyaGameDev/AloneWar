#pragma once
#include <array>
#include "Obj.h"

enum class Wall
{
    // ‰E‚Ì•Ç
    Right,
    // ¶‚Ì•Ç
    Left,
    // °
    Floor,
    // “Vˆä
    Ceiling,
    // ”wŒi
    Back,
    Max
};
// Še•Ç‚Ì’¸“_î•ñ‚ÌŒ^
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
    // Še•Ç‚Ì’¸“_î•ñ‚ğŠi”[
    Vertexes vertexes_;
    Wall type_;
};

