#include "Core/Machine/Minimax.h"
#include "Core/Debug/Assert.h"
#include <algorithm>

Minimax::Minimax(int n, int b)
    :n(n), b(b)
{

}

Minimax::~Minimax()
{
    
}

void Minimax::SetScore(const std::vector<int> &input_scores)
{
    scores = input_scores;
}

int Minimax::CalDepth(int n, int b)
{
    ASSERT(n >= 0 && b >= 1, "Base must be greater than 1 and n must be positive");
    h = std::log(n) / std::log(b);
    return h;
}

int Minimax::Solve(int depth, int node, bool isMax)
{
    if (depth == h)
        return scores[node];

    if (isMax)
    {
        int res = 0;
        for (int i=0; i<=b-1; i++)
        {
            res = std::max(res, Solve(depth+1, b*node+i, false));
        }
        return res;
    }

    else 
    {
        int res = 1e9;
        for (int i=0; i<=b-1; i++)
        {
            res = std::min(res, Solve(depth+1, b*node+i, true));
        }
        return res;
    }
}