#include <bits/stdc++.h>

typedef std::pair<int, std::pair<int, int>> item;

int N;
std::vector<std::vector<int>> maze;
std::priority_queue<item,
    std::vector<item>,
    std::greater<item>> queue;
std::set<std::pair<int, int>> explored;

void printMaze()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            std::cout << maze[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int rounds(const std::pair<int, int>& l1, const std::pair<int, int>& l2)
{
    return std::abs(maze[l1.first][l1.second] - maze[l2.first][l2.second]);
}

int bfs(std::pair<int, int> target)
{
    std::stack<std::pair<int, int>> newLocs;

    while (!queue.empty())
    {
        std::pair<int, std::pair<int, int>> curr = queue.top(); queue.pop();
        explored.insert(curr.second);
        if (curr.second == target) return curr.first;

        if (curr.second.first > 0)
            newLocs.push(std::make_pair(curr.second.first-1, curr.second.second));
        if (curr.second.second > 0)
            newLocs.push(std::make_pair(curr.second.first, curr.second.second-1));
        if (curr.second.first < N-1)
            newLocs.push(std::make_pair(curr.second.first+1, curr.second.second));
        if (curr.second.second < N-1)
            newLocs.push(std::make_pair(curr.second.first, curr.second.second+1));

        while (!newLocs.empty())
        {
            if (explored.find(newLocs.top()) == explored.end())
                queue.push(std::make_pair(curr.first + rounds(curr.second, newLocs.top()), newLocs.top()));
            newLocs.pop();
        }
    }
    return 0;
}

int path_finder(std::string m)
{
    int pos = 0;
    maze.clear();
    explored.clear();
    while (!queue.empty()) queue.pop();

    std::vector<int> curr = std::vector<int>();
    while (pos < m.length())
    {
        if (m[pos] != '\n')
        {
            curr.push_back(m[pos] - '0');
        }
        else
        {
            maze.push_back(curr);
            curr.clear();
        }
        pos++;
    }
    maze.push_back(curr);
    N = maze.size();
    queue.push(std::make_pair(0, std::make_pair(0, 0)));
    return bfs(std::make_pair(N-1, N-1));
}