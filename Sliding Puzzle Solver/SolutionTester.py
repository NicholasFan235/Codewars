from PythonSolution import slide_puzzle as nic_slide_puzzle
from Alan import slide_puzzle as alan_slide_puzzle
import time
import os

def TimeSolution(func, puzzle):
    tic = time.perf_counter()
    moves = func(puzzle)
    toc = time.perf_counter()
    print(f"Completed in {(toc-tic)*1000000}u")
    if moves != None:
        print(f"Solved with {len(moves)} moves")
    else:
        print("Unsolveable")

def CompareSolutions(puzzle):
    print("Nicholas:")
    TimeSolution(nic_slide_puzzle, puzzle)
    print("\nAlan:")
    TimeSolution(alan_slide_puzzle, puzzle)

with open("test.txt", 'r') as f:
    f.readline()
    puzzle = [row.split(' ') for row in f.read().split('\n')]
    puzzle = [[int(i) for i in row] for row in puzzle]
    CompareSolutions(puzzle)

    
