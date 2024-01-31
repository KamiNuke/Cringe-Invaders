#include "Globals.h"

bool CollisionCheck(const SDL_Rect a, const SDL_Rect b)
{  
    int rightA, rightB;
    int leftA, leftB;
    int topA, topB;
    int bottomA, bottomB;

    rightA = a.x + a.w;
    leftA = a.x;
    topA = a.y;
    bottomA = a.y + a.h;

    rightB = b.x + b.w;
    leftB = b.x;
    topB = b.y;
    bottomB = b.y + b.h;

    if (rightA < leftB)
    {
        return false;
    }
    if (leftA > rightB)
    {
        return false;
    }
    if (topA > bottomB)
    {
        return false;
    }
    if (bottomA < topB)
    {
        return false;
    }

    return true;
}

SDL_Renderer* renderer{ nullptr };

IGameState* nextState{ nullptr };
IGameState* m_currentState{ nullptr };

File saveFile{ "savedata.bin" };

bool isHitboxes{ false };