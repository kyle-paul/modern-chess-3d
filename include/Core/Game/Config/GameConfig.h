#pragma once
#include "Core/Game/Config/PieceConfig.h"

enum class Mode
{
    Human = 0,
    Minimax = 1,
    AlphaBeta = 2,
    DeepLearning = 3,
};

struct GameState
{
    bool Selected = false; 
    int SelectedRow = 1, SelectedCol = 1;
    int SrcRow = 0, SrcCol = 0, DesRow = 0, DesCol = 0;
    
    bool CloseGame = false, BoardRotating = true;
    bool Check = false, CheckMate = false, NeedPromote = false, Verify = false;
    
    int Turn = 1;
    PieceColor TurnColor = PieceColor::WHITE;
    Mode mode = Mode::Human;

    bool thinking = false;
    GameState() = default;
};