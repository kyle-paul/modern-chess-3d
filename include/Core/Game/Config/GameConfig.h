#pragma once
#include "Core/Game/Config/PieceConfig.h"

struct GameState
{
    bool Selected; int SelectedRow, SelectedCol;
    int SrcRow, SrcCol, DesRow, DesCol;
    
    bool CloseGame, BoardRotating;
    bool Check, CheckMate, NeedPromote, Verify;
    
    int Turn;
    PieceColor TurnColor;
};