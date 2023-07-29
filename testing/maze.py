def search_exit(n,x,y,p,M):

    #pos search queue
    p.append([x,y])
    solved = False

    #search history/wall check
    if n==x or n==y:
        pass
    #exit check
    elif M[y][x] == 'X' or M[y][x] == 'W':
        pass
    elif n-1 == x and n-1 == y:
        #set ans to T
        solved = True
    #next coordinate
    else:
        #add mark of searched position to matrix
        M[y][x] = 'X'
        #add to queue
        solved = solved or search_exit(n,x+1,y,p,M)
        solved = solved or search_exit(n,x,y+1,p,M)
        
    #remove from search queue
    p.pop(0)
    return solved

def path_finder(maze):

    #convert maze to 1D list
    l = maze.split('\n')
    #convert 1D list into 2D list
    matrix = []
    for s in l:
        matrix.append(list(s))
    print(matrix)
    #assign other values
    pos = []
    
    #search exit
    A = search_exit(len(matrix),0,0,pos,matrix)

    #return ans value (def F)
    return A

a = "\n".join([
  ".W.",
  ".W.",
  "..."
])

b = "\n".join([
  ".W.",
  ".W.",
  "W.."
])

c = "\n".join([
  "......",
  "......",
  "......",
  "......",
  "......",
  "......"
])

d = "\n".join([
  "......",
  "......",
  "......",
  "......",
  ".....W",
  "....W."
])

print(path_finder(a))
print(path_finder(b))
print(path_finder(c))
print(path_finder(d))