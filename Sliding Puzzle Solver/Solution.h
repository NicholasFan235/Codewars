#include "PathFinder.h"
#include "SequenceExecuter.h"
#include "BoardPrinter.h"

std::vector<int> MoveZeroTo(std::pair<int, int> target);
std::vector<int> MovePiece(std::pair<int, int> from, std::pair<int, int> to);
std::vector<int> SolveRow(int row);
std::vector<int> SolveColumn(int row);
std::vector<int> SolveTo2x2();
std::vector<int> SolveFinal2x2();
std::vector<int> Solve();

bool CheckSolution(){
    // just do check on final 2x2
    for (int i = N-3; i < N; i++){
        for (int j = M-3; j < M; j++){
            int target = i*M + j + 1;
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

    if (CheckSolution()){
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
    std::vector<int> ret;
    ret = MoveZeroTo(std::make_pair(N-1, M-1));

    return ret;
}

std::vector<int> SolveRow(int row){
    std::vector<int> ret;
    for (int j = 0; j < board[row].size()-1; j++){
        int targetPiece = row*M + j + 1;
        auto moves = MovePiece(pieceMap[targetPiece], std::make_pair(row, j));
        ret.insert(ret.end(), moves.begin(), moves.end());
        locked[row][j] = 1;
    }

    // move zero to far right corner
    auto moves = MoveZeroTo(std::make_pair(row, M-1));
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

    // move zero to far bottom corner
    auto moves = MoveZeroTo(std::make_pair(N-1, column));
    ret.insert(ret.end(), moves.begin(), moves.end());

    // move 2nd from corner to bottom
    locked[N-2][column] = 0;
    ret.push_back(board[N-2][column]);
    SlidePiece(std::make_pair(N-2, column));
    locked[N-1][column] = 1;

    // move corner piece below corner
    moves = MovePiece(pieceMap[(N-1)*M + column + 1], std::make_pair(N-1, column+1));
    ret.insert(ret.end(), moves.begin(), moves.end());
    locked[N-1][column] = 1;

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

    std::vector<std::pair<int, int>> path;
    GeneratePath(from, to, path);

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
    std::vector<std::pair<int, int>> path;
    GeneratePath(pieceMap[0], target, path);
    std::vector<int> instructions = ConvertToInstructions(path);
    ExecuteSequence(path);
    return instructions;
}