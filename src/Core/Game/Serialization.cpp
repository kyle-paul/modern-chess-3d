#include "Core/Game/Serialization.h"
#include "Core/Game/Board.h"
#include <fstream>
#include <sstream>

const std::string ModeLog(const Mode &mode)
{
	switch(mode)
	{
		case Mode::Human: return "HUMAN"; break;
		case Mode::Easy: return "EASY"; break;
        case Mode::Minimax: return "MINIMAX"; break;
        case Mode::AlphaBeta: return "ALPHABETA"; break;
        case Mode::DeepLearning: return "DEEPLEARNING"; break;
	}
	ASSERT(false, "Invalid Mode");
    return "UNKNOWN MODE";
}

const Mode ModeLoad(const std::string &mode)
{
	if (mode == "HUMAN") return Mode::Human;
    else if (mode == "EASY") return Mode::Easy;
    else if (mode == "MINIMAX") return Mode::Minimax;
    else if (mode == "ALPHABETA") return Mode::AlphaBeta;
    else if (mode == "DEEPLEARNING") return Mode::DeepLearning;
    else {
        ASSERT(false, "Invalid Mode");
        return Mode::Human;
    }
}

Serialization::Serialization()
{

}

Serialization::~Serialization()
{
    
}

void Serialization::save(GameState *state, Board *board, Status *status)
{
    std::ofstream file("data/default.txt");
    if (!file.is_open())
        ERROR("Can not open file");

    // Game state
    file << "Selected: " << state->Selected << '\n';
    file << "SelectedRow: " << state->SelectedRow << '\n';
    file << "SelectedCol: " << state->SelectedCol << '\n';
    file << "SrcRow: " << state->SrcRow << '\n';
    file << "SrcCol: " << state->SrcCol << '\n';
    file << "DesRow: " << state->DesRow << '\n';
    file << "DesCol: " << state->DesCol << '\n';

    file << "CloseGame: " << state->CloseGame << '\n';
    file << "BoardRotating: " << state->BoardRotating << '\n';
    file << "Check: " << state->Check << '\n';
    file << "CheckMate: " << state->CheckMate << '\n';
    file << "NeedPromote: " << state->NeedPromote << '\n';
    file << "Verify: " << state->Verify << '\n';

    file << "Turn: " << state->Turn << '\n';
    file << "TurnColor: " << PieceColorLog(state->TurnColor) << '\n';
    file << "Mode: " << ModeLog(state->mode) << '\n';
    file << "Thinking: " << state->thinking << '\n'; 

    // Board color   
    file << "BoardColor: " << board->boardColor.x << " " << board->boardColor.y << " " << board->boardColor.z << " " << board->boardColor.w << '\n';
    for (auto &record : board->records)
    {
        file << "Piece: " << PieceTypeLog(record.first->GetType()) << " " << PieceColorLog(record.first->GetColor())  << " " << record.second.first << " " << record.second.second << '\n';
    }
    file.close();
}

void Serialization::load(GameState *state, Board *board, Status *status)
{
    std::ifstream file("data/default.txt");
    if (!file.is_open())
        ERROR("Can not open file");

    std::string line;
    while(std::getline(file, line))
    {
        std::istringstream stream(line);
        std::string label;

        if (line.find("Selected:") != std::string::npos)
            stream >> label >> state->Selected;
        else if (line.find("SelectedRow:") != std::string::npos)
            stream >> label >> state->SelectedRow;
        else if (line.find("SelectedCol:") != std::string::npos)
            stream >> label >> state->SelectedCol;
        else if (line.find("SrcRow:") != std::string::npos)
            stream >> label >> state->SrcRow;
        else if (line.find("SrcCol:") != std::string::npos)
            stream >> label >> state->SrcCol;
        else if (line.find("DesRow:") != std::string::npos)
            stream >> label >> state->DesRow;
        else if (line.find("DesCol:") != std::string::npos)
            stream >> label >> state->DesCol;
        else if (line.find("CloseGame:") != std::string::npos)
            stream >> label >> state->CloseGame;
        else if (line.find("BoardRotating:") != std::string::npos)
            stream >> label >> state->BoardRotating;
        else if (line.find("Check:") != std::string::npos)
            stream >> label >> state->Check;
        else if (line.find("CheckMate:") != std::string::npos)
            stream >> label >> state->CheckMate;
        else if (line.find("NeedPromote:") != std::string::npos)
            stream >> label >> state->NeedPromote;
        else if (line.find("Verify:") != std::string::npos)
            stream >> label >> state->Verify;
        else if (line.find("Turn:") != std::string::npos)
            stream >> label >> state->Turn;
        else if (line.find("TurnColor:") != std::string::npos)
        {
            std::string color;
            stream >> label >> color;
            state->TurnColor = PieceColorLoad(color); // Load PieceColor
        }
        else if (line.find("Mode:") != std::string::npos)
        {
            std::string mode;
            stream >> label >> mode;
            state->mode = ModeLoad(mode); // Load Mode
        }
        else if (line.find("BoardColor:") != std::string::npos)
        {
            stream >> label >> board->boardColor.x >> board->boardColor.y >> board->boardColor.z >> board->boardColor.w;
        }

        else if (line.find("Piece:") != std::string::npos)
        {
            std::string type, color; int row, col;
            stream >> label >> type >> color >> row >> col;

            board->m_Grid.GetSquare(row, col)->SetOccupied(new Piece(PieceTypeLoad(type), PieceColorLoad(color)));
            board->records[board->m_Grid.GetSquare(row, col)->GetPiece()] = {row, col};
        }
    }
    file.close();
}