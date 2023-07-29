def mprint(maze):
    for r in maze:
        print(r)
    print()

def path_finder(maze):
    maze = [list(r) for r in maze.split('\n')]
    n = len(maze)
    checkQueue = [(0,0,0)]
    while len(checkQueue) > 0:
        curr = checkQueue[0]
        #print(curr)
        checkQueue.pop(0)
        if curr[0] == n-1 and curr[1] == n-1:
            return curr[2]
        elif curr[0] >= n or curr[0] < 0 or curr[1] >= n or curr[1] < 0:
            pass
        else:
            if maze[curr[0]][curr[1]] in ['W', 'X']:
                pass
            else:
                maze[curr[0]][curr[1]] = 'X'
                checkQueue.append((curr[0]+1,curr[1],curr[2]+1))
                checkQueue.append((curr[0],curr[1]+1,curr[2]+1))
                checkQueue.append((curr[0]-1,curr[1],curr[2]+1))
                checkQueue.append((curr[0],curr[1]-1,curr[2]+1))
    return False

c = "\n".join([
  "......",
  "......",
  "......",
  "......",
  "......",
  "......"
])
print(path_finder(c))