
links = [[[1,2],[3,6],[4,8],[5],[7]],
    [[0],[2],[3],[4,7],[5],[6],[8]],
    [[1,0],[3],[4,6],[5,8],[7]],
    [[0],[1],[2],[4,5],[6],[7],[8]],
    [[0],[1],[2],[3],[5],[6],[7],[8]],
    [[0],[1],[2],[4,3],[6],[7],[8]],
    [[3,0],[1],[4,2],[5],[7,8]],
    [[0],[4,1],[2],[3],[5],[6],[8]],
    [[4,0],[1],[5,2],[3],[7,6]]]

solvedStates = {}

def solveState(state, current, length):
    if length == 1:
        return 1
    if (state, current) in solvedStates:
        return solvedStates[(state, current)]
    ans = 0
    for possible in links[current]:
        for l in possible:
            if (state & (1 << l)) == 0:
                ans += solveState(state | (1<<l), l, length-1)
                break
    solvedStates[(state, current)] = ans
    return ans

charMap = { 'A':0, 'B':1, 'C':2, 'D':3, 'E':4, 'F':5, 'G':6, 'H':7, 'I':8 }
def count_patterns_from(firstPoint, length):
    solvedStates.clear()
    print("Solving first point {}, length {}".format(firstPoint, length))
    start = charMap[firstPoint]
    ans = solveState(1<<start, start, length)
    print(ans)
    return ans

count_patterns_from('E', 2)
