def solve(grid):
    solution = []
    N = len(grid)
    for i in range(2):
        for x in range(N):
            for y in range(N):
                if grid[y][x] % 2 == 0:
                    solution.append((x,y))
        for move in solution:
            grid[move[1]][move[0]] -= 1
            for x in range(N):
                grid[move[1]][x] += 1
                grid[x][move[0]] += 1
    return solution