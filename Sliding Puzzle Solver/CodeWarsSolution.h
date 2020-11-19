#include <bits/stdc++.h>

static int N, M;

static std::vector<std::vector<int>> board;
static std::vector<std::vector<int>> locked;
static std::vector<std::pair<int, int>> pieceMap;

#pragma region PRINT_UTILS

void PrintArray2(std::vector<std::vector<int>> &arr){
    for (const auto r : arr){
        for (const auto p : r){
            printf("%d\t", p);
        }
        std::cout << std::endl;
    }
}

void PrintBoard(){
    PrintArray2(board);
}

void PrintLocked(){
    PrintArray2(locked);
}

#pragma endregion

#pragma region PATHFIND_UTILS
std::vector<std::pair<int, int>> GetNeighbours(std::pair<int, int>);
std::vector<std::pair<int, int>> GeneratePath(std::pair<int, int> start, std::pair<int, int> target);
std::vector<int> ConvertToInstructions(std::vector<std::pair<int, int>>);

std::vector<int> ConvertToInstructions(std::vector<std::pair<int, int>> path){
    std::vector<int> ret;
    for (const auto p : path){
        ret.push_back(board[p.first][p.second]);
    }
    return ret;
}

std::vector<std::pair<int, int>> GeneratePath(std::pair<int, int> start, std::pair<int, int> target){
    /*PrintLocked();
    printf("\n"); PrintBoard();*/
    //printf("(%d, %d) -> (%d, %d):\t", start.second, start.first, target.second, target.first); //*/

    std::queue<std::pair<int, int>> checkQueue;
    std::vector<std::vector<int>> explored(N, std::vector<int>(M));
    std::map<std::pair<int, int>, std::pair<int, int>> links;
    checkQueue.push(target);
    std::pair<int, int> current;

    while (!checkQueue.empty()){
        current = checkQueue.front();
        explored[current.first][current.second] = 1;
        checkQueue.pop();

        if (current == start) break;

        auto neighbours = GetNeighbours(current);

        for (const auto n : neighbours){
            if (explored[n.first][n.second] == 0 && locked[n.first][n.second] != 1){
                explored[n.first][n.second] = 1;
                links[n] = current;
                checkQueue.push(n);
            }
        }
    }

    std::vector<std::pair<int, int>> ret;
    if (current != start) return {};

    //std::cout << "Num links: " << links.size() << std::endl;

    while (current != target){
        ret.push_back(links[current]);
        //printf("Current = (%d, %d), linked to: (%d, %d)\n", current.second, current.first, links[current].second, links[current].first);
        current = links[current];
    }
    /*
    for (const auto p : ret){
        printf("(%d, %d), ", p.second, p.first);
    }
    std::cout << std::endl;//*/

    return ret;
}

std::vector<std::pair<int, int>> GetNeighbours(std::pair<int, int> p){
    std::vector<std::pair<int, int>> ret;
    int x = p.second; int y = p.first;
    if (y > 0) ret.push_back(std::make_pair(y-1, x));
    if (x > 0) ret.push_back(std::make_pair(y, x-1));
    if (y < N-1) ret.push_back(std::make_pair(y+1, x));
    if (x < M-1) ret.push_back(std::make_pair(y, x+1));
    return ret;
}
#pragma endregion

#pragma region SEQUENCE_EXECUTION_UTILS
bool isNeighbour(std::pair<int, int> &a, std::pair<int, int> &b);
void SlidePiece(std::pair<int, int> p);

bool isNeighbour(std::pair<int, int> &a, std::pair<int, int> &b){
    return ( abs(a.first-b.first) + abs(a.second-b.second) ) <= 1;
}

void InitializeBoard(std::vector<std::vector<int>> _b){
    board = _b;
    N = board.size();
    M = board[0].size();

    locked = std::vector<std::vector<int>>(N, std::vector<int>(M));
    pieceMap = std::vector<std::pair<int, int>>(N*M);
    for (int i = 0; i < board.size(); i++){
        for (int j = 0; j < board[0].size(); j++){
            int piece = board[i][j];
            pieceMap[piece] = std::make_pair(i, j);
        }
    }
}

void ExecuteSequence(std::vector<std::pair<int, int>> sequence){
    for (auto p : sequence){
        SlidePiece(p);
    }
}

void ExecuteInstructions(std::vector<int> instructions){
    for (auto i : instructions){
        //PrintBoard();
        //std::cout << i << std::endl;
        SlidePiece(pieceMap[i]);
    }
}

void SlidePiece(std::pair<int, int> p){
    if (!isNeighbour(p, pieceMap[0])) throw "Invalid slide attempt";
    
    int piece = board[p.first][p.second];
    board[pieceMap[0].first][pieceMap[0].second] = piece;
    board[p.first][p.second] = 0;

    pieceMap[piece] = pieceMap[0];
    pieceMap[0] = p;
}
#pragma endregion

#pragma region SOLUTION_UTILS
std::vector<int> MoveZeroTo(std::pair<int, int> target);
std::vector<int> MovePiece(std::pair<int, int> from, std::pair<int, int> to);
std::vector<int> SolveRow(int row);
std::vector<int> SolveColumn(int row);
std::vector<int> SolveTo2x2();
std::vector<int> SolveFinal2x2();
std::vector<int> Solve();

bool CheckSolution(){
    // just do check on final 2x2
    for (int i = N-2; i < N; i++){
        for (int j = M-2; j < M; j++){
            int target = i*M + j + 1;
            if (target == M*N) target = 0;
            //printf("Checking cell (%d, %d), should be %d and is actually %d\n", i, j, target, board[i][j]);
            if (board[i][j] != target) return false;
        }
    }
    return true;
}

std::vector<int> Solve(){
    std::vector<int> ret;
    std::vector<int> moves;

    moves = SolveTo2x2();
    ret.insert(ret.end(), moves.begin(), moves.end());

    moves = SolveFinal2x2();
    ret.insert(ret.end(), moves.begin(), moves.end());

    /*
    for (const auto m : ret){
        std::cout << m << " ";
    }
    std::cout << std::endl;*/

    if (CheckSolution()){
        std::cout << "Solveable" << std::endl;
        return ret;
    }
    else{
        return {0};
    }
}

std::vector<int> SolveTo2x2(){
    std::vector<int> ret;
    std::vector<int> moves;
    for (int i = 0; i < N-2; i++){
        moves = SolveRow(i);
        ret.insert(ret.end(), moves.begin(), moves.end());

        moves = SolveColumn(i);
        ret.insert(ret.end(), moves.begin(), moves.end());
    }

    return ret;
}

std::vector<int> SolveFinal2x2(){
    int target = (N-2)*M + M-2 + 1;
    std::vector<int> ret;
    ret = MovePiece(pieceMap[target], std::make_pair(N-2, M-2));
    locked[N-2][M-2] = 1;

    auto move = MovePiece(pieceMap[N*M-1], std::make_pair(N-1, M-2));
    ret.insert(ret.end(), move.begin(), move.end());

    move = MoveZeroTo(std::make_pair(N-1, M-1));
    ret.insert(ret.end(), move.begin(), move.end());

    return ret;
}

std::vector<int> SolveRow(int row){
    std::vector<int> ret;
    for (int j = 0; j < board[row].size()-1; j++){
        //printf("Solving row and column #%d\n", j);
        int targetPiece = row*M + j + 1;
        auto moves = MovePiece(pieceMap[targetPiece], std::make_pair(row, j));
        ret.insert(ret.end(), moves.begin(), moves.end());
        locked[row][j] = 1;
    }
    // Move end target to bottom right
    auto moves = MovePiece(pieceMap[row*M + M-1 + 1], std::make_pair(N-1, M-1));
    ret.insert(ret.end(), moves.begin(), moves.end());

    // move zero to far right corner
    moves = MoveZeroTo(std::make_pair(row, M-1));
    ret.insert(ret.end(), moves.begin(), moves.end());

    // move 2nd from corner to end
    locked[row][M-2] = 0;
    ret.push_back(board[row][M-2]);
    SlidePiece(std::make_pair(row, M-2));
    locked[row][M-1] = 1;

    // move corner piece below corner
    moves = MovePiece(pieceMap[row*M + M-1 + 1], std::make_pair(row+1, M-1));
    ret.insert(ret.end(), moves.begin(), moves.end());
    locked[row+1][M-1] = 1;

    // move zero to 2nd from corner
    moves = MoveZeroTo(std::make_pair(row, M-2));
    ret.insert(ret.end(), moves.begin(), moves.end());

    // unlock and slide final into place
    locked[row][M-1] = 0;
    locked[row+1][M-1] = 0;
    ret.push_back(board[row][M-1]);
    ret.push_back(board[row+1][M-1]);
    SlidePiece(std::make_pair(row, M-1));
    SlidePiece(std::make_pair(row+1, M-1));
    locked[row][M-2] = 1;
    locked[row][M-1] = 1;

    //PrintBoard(); printf("\n");
    return ret;
}

std::vector<int> SolveColumn(int column){
    std::vector<int> ret;
    for (int i = 0; i < board.size()-1; i++){
        int targetPiece = i*M + column + 1;
        auto moves = MovePiece(pieceMap[targetPiece], std::make_pair(i, column));
        ret.insert(ret.end(), moves.begin(), moves.end());
        locked[i][column] = 1;
    }

    // Move end target to bottom right
    auto moves = MovePiece(pieceMap[(N-1)*M + column + 1], std::make_pair(N-1, M-1));
    ret.insert(ret.end(), moves.begin(), moves.end());

    // move zero to far bottom corner
    moves = MoveZeroTo(std::make_pair(N-1, column));
    ret.insert(ret.end(), moves.begin(), moves.end());

    // move 2nd from corner to bottom
    locked[N-2][column] = 0;
    ret.push_back(board[N-2][column]);
    SlidePiece(std::make_pair(N-2, column));
    locked[N-1][column] = 1;

    // move corner piece below corner
    moves = MovePiece(pieceMap[(N-1)*M + column + 1], std::make_pair(N-1, column+1));
    ret.insert(ret.end(), moves.begin(), moves.end());
    locked[N-1][column+1] = 1;

    // move zero to 2nd from corner
    moves = MoveZeroTo(std::make_pair(N-2, column));
    ret.insert(ret.end(), moves.begin(), moves.end());

    // unlock and slide final into place
    locked[N-1][column] = 0;
    locked[N-1][column+1] = 0;
    ret.push_back(board[N-1][column]);
    ret.push_back(board[N-1][column+1]);
    SlidePiece(std::make_pair(N-1, column));
    SlidePiece(std::make_pair(N-1, column+1));
    locked[N-2][column] = 1;
    locked[N-1][column] = 1;

    return ret;
}

std::vector<int> MovePiece(std::pair<int, int> from, std::pair<int, int> to){
    std::vector<int> totalInstructions;

    std::vector<std::pair<int, int>> path = GeneratePath(from, to);
    /*
    for (const auto p : path){
        printf("(%d, %d) ", p.second, p.first);
    }
    printf("\n");*/

    std::pair<int, int> currentLocation = from;
    for (const auto p : path){
        locked[currentLocation.first][currentLocation.second] = 1;
        std::vector<int> zeroInstructions = MoveZeroTo(p);
        totalInstructions.insert(totalInstructions.end(), zeroInstructions.begin(), zeroInstructions.end());
        totalInstructions.push_back(board[currentLocation.first][currentLocation.second]);
        SlidePiece(currentLocation);
        locked[currentLocation.first][currentLocation.second] = 0;
        currentLocation = p;
    }

    return totalInstructions;
}

std::vector<int> MoveZeroTo(std::pair<int, int> target){
    std::vector<std::pair<int, int>> path = GeneratePath(pieceMap[0], target);
    std::vector<int> instructions = ConvertToInstructions(path);
    ExecuteSequence(path);
    return instructions;
}
#pragma endregion

std::vector<int> slide_puzzle(const std::vector<std::vector<int>> &arr){
    InitializeBoard(arr);
    //PrintBoard();
    //printf("\n");
    auto path = Solve();
    //PrintBoard();
    //printf("\n");
    return path;
}

