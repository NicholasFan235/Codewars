#include <bits/stdc++.h>


int n, m;
std::vector<std::string> board;
std::vector<std::array<int, 4>> regionBounds;
std::vector<std::vector<std::string>> regions;
std::queue<std::pair<int, int>> checkQueue;

void reset(){
    board.clear();
    regionBounds.clear();
    regions.clear();
}

std::array<int, 4> floodFill(int y, int x, char c){
    checkQueue.push(std::make_pair(y, x));

    int ymin = y, ymax = y;
    int xmin = x, xmax = x;

    while (!checkQueue.empty()){
        auto p = checkQueue.front();
        checkQueue.pop();
        
        if (board[p.first][p.second] == ' '){
            board[p.first][p.second] = c;
            ymin = std::min(ymin, p.first);
            ymax = std::max(ymax, p.first);
            xmin = std::min(xmin, p.second);
            xmax = std::max(xmax, p.second);
            if (p.first > 0) checkQueue.push(std::make_pair(p.first-1, p.second));
            if (p.first < n-1) checkQueue.push(std::make_pair(p.first+1, p.second));
            if (p.second > 0) checkQueue.push(std::make_pair(p.first, p.second-1));
            if (p.second < m-1) checkQueue.push(std::make_pair(p.first, p.second+1));
        }
    }

    return {ymin, xmin, ymax-ymin+1, xmax-xmin+1};
}

void floodEdges(){
    for (int i = 0; i < n; i++){
        floodFill(i, 0, '0');
        floodFill(i, m-1, '0');
    }
    for (int j = 0; j < m; j++){
        floodFill(0, j, '0');
        floodFill(n-1, j, '0');
    }
}

std::pair<int, int> findEmpty(){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            if (board[i][j] == ' ') return std::make_pair(i, j);
        }
    }
    return std::make_pair(-1, -1);
}

int floodRegions(){
    int ctr = 0;
    while (1){
        auto p = findEmpty();
        if (p.first == -1) break;
        auto bounds = floodFill(p.first, p.second, 'a' + ctr);
        regionBounds.push_back(bounds);
        ctr++;
    }
    return ctr;
}

void printBoard(){
    for (int i = 0; i < n; i++){
        std::cout << board[i] << std::endl;
    }
}

void printBounds(){
    printf("X\tY\tWidth\tHeight\n");
    for (const auto b : regionBounds){
        printf("%d\t%d\t%d\t%d\n", b[1], b[0], b[3], b[2]);
    }
}

void initializeRegions(int num){
    for (int i = 0; i < num; i++){
        std::string r = "";
        for (int w = 0; w < regionBounds[i][3]+2; w++){
            r.push_back(' ');
        }
        std::vector<std::string> region(regionBounds[i][2]+2, r);
        regions.push_back(region);
    }
}

bool checkEdge(int y, int x, char c){
    for (int i = -1; i <= 1; i++){
        for (int j = -1; j <= 1; j++){
            if (i==0 && j==0) continue;
            int xi = x+i;
            int yj = y+j;
            if (yj < 0 || yj >= n || xi < 0 || xi >= m) continue;
            if (board[yj][xi] == c) return true;
        }
    }
    return false;
}

void solveRegions(int num){
    for (int i = 0; i < num; i++){
        char c = 'a' + i;
        int ni = regionBounds[i][2]+2;
        int mi = regionBounds[i][3]+2;
        printf("%dx%d region\n", ni, mi);
        for (int yi = 0; yi < ni; yi++){
            for (int xi = 0; xi < mi; xi++){
                std::pair<int, int> boardPos = std::make_pair(regionBounds[i][0]-1+yi, regionBounds[i][1]-1+xi);
                if (board[boardPos.first][boardPos.second] == c) continue;
                if (checkEdge(boardPos.first, boardPos.second, c)) regions[i][yi][xi] = '.';
            }
        }

        for (int yi = 0; yi < ni; yi++){
            for (int xi = 0; xi < mi; xi++){
                if (regions[i][yi][xi] == ' ') continue;
                int neighbours = 0;
                if (yi > 0 && regions[i][yi-1][xi] != ' ') neighbours += 1;
                if (xi < mi-1 && regions[i][yi][xi+1] != ' ') neighbours += 2;
                if (yi < ni-1 && regions[i][yi+1][xi] != ' ') neighbours += 3;
                if (xi > 0 && regions[i][yi][xi-1] != ' ') neighbours += 4;
                if (neighbours % 2 == 1) regions[i][yi][xi] = '+';
                else if (neighbours < 5) regions[i][yi][xi] = '|';
                else regions[i][yi][xi] = '-';
            }
        }
    }
}

void printRegions(){
    for (const auto r : regions){
        int nr = r.size();
        int mr = r[0].size();
        //printf("%dx%d region\n", nr, mr);
        for (const auto s : r){
            std::cout << "\"" << s << "\"" << std::endl;
        }
        std::cout << std::endl;
    }
}

void normalizeBoard(){
    for (int i = 0; i < n; i++){
        while (board[i].length() < m){
            board[i].push_back(' ');
        }
    }
}

void reduce(){
    for (int i = 0; i < regions.size(); i++){
        for (int j = 0; j < regions[i].size(); j++){
            while (regions[i][j].back() == ' ') regions[i][j].pop_back();
        }
    }
}

std::vector<std::vector<std::string>> solve(const std::vector<std::string> _b){
    reset();
    board = _b;
    n = board.size();
    m = board[0].length();
    normalizeBoard();
    printf("%dx%d board\n", n, m);
    floodEdges();
    int numRegions = floodRegions();
    printBoard();
    printf("%d Regions\n", numRegions);
    printBounds();

    initializeRegions(numRegions);
    solveRegions(numRegions);
    reduce();
    printRegions();

    return regions;
}

/*
std::string join(const std::string &sep, const std::vector<std::string> &to_join);
std::vector<std::string> split_lines(const std::string &to_split);
std::vector<std::string> break_piece(const std::string &shape){
    std::vector<std::string> q = split_lines(shape);
    std::vector<std::vector<std::string>> result = solve(q);
    std::vector<std::string> ans;
    for (const auto r : result){
        ans.push_back(join("\n", r));
    }
    return ans;
}
//*/


std::vector<std::string> query = {
    "+-----------------+",
    "|                 |",
    "|   +-------------+",
    "|   |",
    "|   |",
    "|   |",
    "|   +-------------+",
    "|                 |",
    "|                 |",
    "+-----------------+",
};

int main(){
    solve(query);
}