#pragma once
#include "Core/Game/Config/GameConfig.h"

class Board;
class Status;

class Serialization
{
public:
    Serialization();
    ~Serialization();

    void save(GameState *state, Board *board, Status *status);
    void load(GameState *state, Board *board, Status *status);

private:
        
};