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

bool path_finder(std::string maze)
{
    std::vector<std::string> m;
    split(maze, '\n', m);
    int n = m.size();
    std::queue<std::pair<int, int>>  checkQueue;
    std::pair<int, int> target = std::make_pair(n-1, n-1);
    checkQueue.push({0,0});
    while (!checkQueue.empty())
    {
        std::pair<int, int> curr = checkQueue.front();
        checkQueue.pop();
        if (curr == target) return true;

        char state = m[curr.first][curr.second];
        if (state == 'W' || state == 'X') continue;
        m[curr.first][curr.second] = 'X';

        if (curr.first < n-1) checkQueue.push({curr.first+1, curr.second});
        if (curr.second < n-1) checkQueue.push({curr.first, curr.second+1});
        if (curr.first > 0) checkQueue.push({curr.first-1, curr.second});
        if (curr.second > 0) checkQueue.push({curr.first, curr.second-1});
    }
    return false;
}

void runTest(const std::string& maze)
{
    bool result = path_finder(maze);
    std::cout << (result ? "True" : "False") << std::endl;
}

int main()
{
    runTest(".W.\n.W.\n...");
    runTest(".W.\n.W.\nW..");
    runTest("......\n......\n......\n......\n......\n......");
    runTest("......\n......\n......\n......\n.....W\n....W.");
}