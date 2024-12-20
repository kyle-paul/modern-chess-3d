#pragma once
#include <memory>
#include <stack>
#include <Core/Render/Shader.h>
#include "Core/Render/VertexArray.h"
#include "Core/Render/Buffer.h"
#include "Core/Window/WindowConfig.h"
#include "Core/Game/Config/GameConfig.h"
#include "Core/Game/Grid.h"
#include "Core/Game/Piece.h"
#include "Core/Game/Move.h"
#include "Core/Game/Rule.h"
#include "Core/Game/Status.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

struct Record
{
    int row, col;
    Piece *piece;

    Record(int r, int c, Piece *p) : row(r), col(c), piece(p) {}
};

class Board
{
public:
    Board();
    Board(const Board& board);
    ~Board();

    void Init();
    const glm::mat4 GetTransform() const;

    void SetInitialPieces(const PieceColor &color);
    void RenderChessBoard();
    void RenderGrid(const std::shared_ptr<Shader> &gridShader, const GameState &state);
    void RenderPieces(const std::shared_ptr<Shader> &pieceShader, const GameState &state, const Environment &env);
    void RenderValidMove(const std::shared_ptr<Shader> &gridShader, const GameState &state, Status &status);
    void RenderMoveToSquare(const std::shared_ptr<Shader> &gridShader, const GameState &state);
    bool MovePlayer(const GameState &state, Status &status);

    int GetEvaluation();
    void MakeMove(Move &move);
    void UndoMove();
    void RedoMove();

private:
    float vertices[36 * 6] = {
        // Base of the chessboard
        -5.0, -5.0, 0.0, 0.55, 0.24, 0.09,
        -5.0,  5.0, 0.0, 0.55, 0.24, 0.09,
        5.0,  5.0, 0.0, 0.55, 0.24, 0.09,
        5.0, -5.0, 0.0, 0.55, 0.24, 0.09,

        // Top of the chessboard
        -4.0, -4.0, 0.5, 0.803, 0.522, 0.247,
        -4.5, -4.5, 0.5, 0.545, 0.271, 0.075,
        -4.5,  4.5, 0.5, 0.545, 0.271, 0.075,
        -4.0,  4.0, 0.5, 0.803, 0.522, 0.247,

        -4.0,  4.0, 0.5, 0.803, 0.522, 0.247,
        -4.5,  4.5, 0.5, 0.545, 0.271, 0.075,
        4.5,  4.5, 0.5, 0.545, 0.271, 0.075,
        4.0,  4.0, 0.5, 0.803, 0.522, 0.247,

        4.0,  4.0, 0.5, 0.803, 0.522, 0.247,
        4.5,  4.5, 0.5, 0.545, 0.271, 0.075,
        4.5, -4.5, 0.5, 0.545, 0.271, 0.075,
        4.0, -4.0, 0.5, 0.803, 0.522, 0.247,

        4.0, -4.0, 0.5, 0.803, 0.522, 0.247,
        4.5, -4.5, 0.5, 0.545, 0.271, 0.075,
        -4.5, -4.5, 0.5, 0.545, 0.271, 0.075,
        -4.0, -4.0, 0.5, 0.803, 0.522, 0.247,

        // Sides of the chessboard
        -4.5, -4.5, 0.5, 0.545, 0.271, 0.075,
        -5.0, -5.0, 0.0, 0.35, 0.15, 0.06,
        -5.0,  5.0, 0.0, 0.35, 0.15, 0.06,
        -4.5,  4.5, 0.5, 0.545, 0.271, 0.075,

        -4.5,  4.5, 0.5, 0.545, 0.271, 0.075,
        -5.0,  5.0, 0.0, 0.35, 0.15, 0.06,
        5.0,  5.0, 0.0, 0.35, 0.15, 0.06,
        4.5,  4.5, 0.5, 0.545, 0.271, 0.075,

        4.5,  4.5, 0.5, 0.545, 0.271, 0.075,
        5.0,  5.0, 0.0, 0.35, 0.15, 0.06,
        5.0, -5.0, 0.0, 0.35, 0.15, 0.06,
        4.5, -4.5, 0.5, 0.545, 0.271, 0.075,

        4.5, -4.5, 0.5, 0.545, 0.271, 0.075,
        5.0, -5.0, 0.0, 0.35, 0.15, 0.06,
        -5.0, -5.0, 0.0, 0.35, 0.15, 0.06,
        -4.5, -4.5, 0.5, 0.545, 0.271, 0.075
    };

private:
    std::shared_ptr<VertexArray> boardVA;
    std::shared_ptr<VertexBuffer> boardVB;
    std::shared_ptr<IndexBuffer> boardIB;

    Grid m_Grid;
    Rule m_Rule;
    std::vector<Move> moves;
    
    int entityID = 0;
    std::stack<MoveState> moveHistory;
    std::stack<MoveState> moveFuture;
    
    friend class Game;
    friend class Rule;
    friend class Serialization;

public:
    const int MIN_COL_INDEX = 1;
    const int MIN_ROW_INDEX = 1;
    const int MAX_COL_INDEX = 8;
    const int MAX_ROW_INDEX = 8;

    glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec4 boardColor = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
    glm::vec3 firstPlayerColor = glm::vec3(0.9f, 0.9f, 0.9f);
    glm::vec3 secPlayerColor = glm::vec3(0.2f, 0.2f, 0.2f);

    std::unordered_map<Piece*, std::pair<int,int>> records;
};