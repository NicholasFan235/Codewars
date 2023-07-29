#include <bits/stdc++.h>
#include <unordered_map>


const std::map<int, std::vector<std::vector<int>>> links = 
{
    {0, {{1,2},{3,6},{4,8},{5},{7}}},
    {1, {{0},{2},{3},{4,7},{5},{6},{8}}},
    {2, {{1,0},{3},{4,6},{5,8},{7}}},
    {3, {{0},{1},{2},{4,5},{6},{7},{8}}},
    {4, {{0},{1},{2},{3},{5},{6},{7},{8}}},
    {5, {{0},{1},{2},{4,3},{6},{7},{8}}},
    {6, {{3,0},{1},{4,2},{5},{7,8}}},
    {7, {{0},{4,1},{2},{3},{5},{6},{8}}},
    {8, {{4,0},{1},{5,2},{3},{7,6}}}
};

struct pair_hash
{
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2>& pair) const
    {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};

std::unordered_map<std::pair<int, int>, unsigned int, pair_hash> solvedStates;

unsigned int solveState(std::pair<int, int> state, unsigned short length)
{
    if (length == 1) return 1;
    if (solvedStates.find(state) != solvedStates.end()) return solvedStates.at(state);
    unsigned int ans = 0;
    for (const std::vector<int>& link : links.at(state.second))
    {
        for (const int l : link)
        {
            if ((state.first & (1 << l)) == 0)
            {
                ans += solveState(std::make_pair(state.first | (1 << l), l), length-1);
                break;
            }
        }
    }
    solvedStates[state] = ans;
    return ans;
}

unsigned int countPatternsFrom(char firstDot, unsigned short length)
{
    int startLoc = firstDot - 'A';
    solvedStates = {};
    std::bitset<9> b(1<<startLoc);
    std::cout << "Solving initial state " << b << " for length " << length << std::endl;
    return solveState(std::make_pair(1 << startLoc, startLoc), length);
}

