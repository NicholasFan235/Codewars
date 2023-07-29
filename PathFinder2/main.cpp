#include <bits/stdc++.h>

void split(const std::string& str, const char c, std::vector<std::string>& out)
{
    std::string buffer = "";
    for (auto n : str)
    {
        if (n!=c) buffer += n;
        else if (n==c && buffer != "")
        {
            out.push_back(buffer);
            buffer = "";
        }
    }
    if (buffer != "") out.push_back(buffer);
}

int path_finder(std::string maze)
{
    std::vector<std::string> m;
    split(maze, '\n', m);
    int n = m.size();
    std::queue<std::pair<std::pair<int, int>, int>>  checkQueue;
    std::pair<int, int> target = std::make_pair(n-1, n-1);
    checkQueue.push({{0,0},0});
    while (!checkQueue.empty())
    {
        std::pair<std::pair<int, int>, int> curr = checkQueue.front();
        checkQueue.pop();
        if (curr.first == target) return curr.second;

        char state = m[curr.first.first][curr.first.second];
        if (state == 'W' || state == 'X') continue;
        m[curr.first.first][curr.first.second] = 'X';

        if (curr.first.first < n-1) checkQueue.push({{curr.first.first+1, curr.first.second},curr.second+1});
        if (curr.first.second < n-1) checkQueue.push({{curr.first.first, curr.first.second+1},curr.second+1});
        if (curr.first.first > 0) checkQueue.push({{curr.first.first-1, curr.first.second},curr.second+1});
        if (curr.first.second > 0) checkQueue.push({{curr.first.first, curr.first.second-1},curr.second+1});
    }
    return -1;
}

void runTest(const std::string& maze)
{
    int result = path_finder(maze);
    std::cout << result << std::endl;
}

int main()
{
    runTest(".W.\n.W.\n...");
    runTest(".W.\n.W.\nW..");
    runTest("......\n......\n......\n......\n......\n......");
    runTest("......\n......\n......\n......\n.....W\n....W.");
}