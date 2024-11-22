#pragma once
#include <vector>

class Minimax
{
public:
    Minimax() = default;
    Minimax(int n, int b);
    ~Minimax();

    int Solve(int depth, int node, bool isMax);
    int CalDepth(int n, int b);
    void SetScore(const std::vector<int> &input_scores);

private:
    std::vector<int> scores;
    int b, h, n;
};