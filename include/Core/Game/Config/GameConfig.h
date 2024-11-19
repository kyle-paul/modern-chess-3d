#pragma once
#include "Core/Game/Config/PieceConfig.h"

struct GameState
{
    bool Selected = false; 
    int SelectedRow = 1, SelectedCol = 1;
    int SrcRow = 0, SrcCol = 0, DesRow = 0, DesCol = 0;
    
    bool CloseGame = false, BoardRotating = true;
    bool Check = false, CheckMate = false, NeedPromote = false, Verify = false;
    
    int Turn = 1;
    PieceColor TurnColor = PieceColor::WHITE;

    GameState() = default;
};