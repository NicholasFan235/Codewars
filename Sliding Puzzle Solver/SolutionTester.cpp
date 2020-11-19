#include <bits/stdc++.h>
#include "Solution.h"


std::vector<int> slide_puzzle(const std::vector<std::vector<int>> &_arr)
{
    board = _arr;
    return std::vector<int>();
}

std::vector<std::vector<std::vector<int>>> puzzles = {{
      	{4,1,3},
      	{2,8,0},
      	{7,6,5}},
       {{10, 3, 6, 4},
      	{ 1, 5, 8, 0},
      	{ 2,13, 7,15},
      	{14, 9,12,11}},
       {{ 3, 7,14,15,10},
      	{ 1, 0, 5, 9, 4},
      	{16, 2,11,12, 8},
      	{17, 6,13,18,20},
      	{21,22,23,19,24}}};

int main(){
	InitializeBoard(puzzles[2]);

	printf("\n");
	PrintBoard();
	auto path = SolveTo2x2();
	printf("\n");
	PrintBoard();
	
	InitializeBoard(puzzles[2]);
	ExecuteInstructions(path);
	printf("\n");
	PrintBoard();
}

