import queue
from copy import copy, deepcopy

class Board:
    def __init__(self, _board):
        self.board = deepcopy(_board)
        self.N = len(self.board)
        self.M = len(self.board[0])
        ##### locked is 2d array storing whether piece should be allowed to move
        self.locked = [ [0]*self.M for i in range(self.N)]
        self.MakePieceMap()
    
    def Solve(self):
        ##### Perform and return moves for complete solve
        ret = []
        ret += self.SolveTo2x2()
        ret += self.SolveFinal2x2()
        if self.CheckSolution():
            #print("Solved")
            return ret
        else:
            #print("Unsolveable")
            return None
        
    
    def SolveTo2x2(self):
        ##### Solve board to 2x2 form
        ### returns instructions (list of moves)
        ret = []
        for i in range(self.N-2): # Assumed square
            ret += self.SolveRow(i)
            ret += self.SolveColumn(i)
        return ret
    
    def SolveFinal2x2(self):
        ##### Solve final 2x2 section
        #### Solve top left
        target = (self.N-2)*self.M + self.M-2 + 1
        ret = []
        ret = self.MovePiece(self.pieceMap[target], (self.N-2, self.M-2))
        self.locked[self.N-2][self.M-2] = 1
        #### Solve Bottom Left
        ret += self.MovePiece(self.pieceMap[self.N*self.M-1], (self.N-1, self.M-2))
        #### Move zero to bottom left
        ret += self.MoveZeroTo((self.N-1, self.M-1))
        return ret
    
    def MakePieceMap(self):
        ##### Map piece to its location on board
        self.pieceMap = {}
        for i in range(self.N):
            for j in range(self.M):
                piece = self.board[i][j]
                self.pieceMap[piece] = (i, j)

    def ExecuteInstructions(self, instructions):
        ##### Slide pieces according to instructions
        ### instructions is list of pieces to slide
        for cmd in instructions:
            #print(cmd)
            self.SlidePiece(self.pieceMap[cmd])
    
    def ExecuteSequence(self, sequence):
        ##### Slide pieces according to sequence
        ### Sequence is list of coordinates that should be slid
        for cmd in sequence:
            self.SlidePiece(cmd)
    
    def SlidePiece(self, location):
        ##### Slide single piece in given location
        ### checks whether piece is next to empty slot, and slides if it is
        if not isNeighbour(location, self.pieceMap[0]):
            raise Exception("Tried to slide invalid piece")
        piece = self.board[location[0]][location[1]] # piece we are sliding
        self.board[self.pieceMap[0][0]][self.pieceMap[0][1]] = piece # move piece on board
        self.board[location[0]][location[1]] = 0; # move 0 on board
        self.pieceMap[piece] = self.pieceMap[0] # move piece on pieceMap
        self.pieceMap[0] = location # move 0 on pieceMap
    
    def GeneratePath(self, start, target):
        ##### iterative bfs to path find between two spots
        checkQueue = queue.Queue() # queue to do bfs
        explored = [ [0]*self.M for i in range(self.N) ] # explored nodes to prevent back pathing
        links = {} # links so that we can backtrack to find path
        checkQueue.put(target)

        ### BFS to explore graph
        while not checkQueue.empty():
            current = checkQueue.get()
            explored[current[0]][current[1]] = 1

            if current == start: break

            neighbours = self.GetNeighbours(current)
            # Explore neighbours
            for n in neighbours:
                if explored[n[0]][n[1]] == 0 and self.locked[n[0]][n[1]] != 1:
                    # If neighbour hasn't been visited and can be moved
                    explored[n[0]][n[1]] = 1
                    links[n] = current
                    checkQueue.put(n)
        
        ### Back track using links to find path taken
        ret = []
        if current != start: return [] # If didn't find a path
        while current != target:
            ret.append(links[current])
            current = links[current]
        #print("Created path length: " + str(len(ret)))
        return ret

    def GetNeighbours(self, location):
        ##### Get all possible neighbours for a location
        ### returns as a list of tuple coords
        ret = []
        x = location[1]
        y = location[0]
        if y>0: ret.append((y-1, x))
        if x>0: ret.append((y, x-1))
        if y<self.N-1: ret.append((y+1, x))
        if x<self.M-1: ret.append((y, x+1))
        return ret
    
    def ConvertToInstructions(self, sequence):
        ##### Converts a sequence to instructions
        ### Sequence is list of tuple coords to slide
        ### Instructions is list of pieces that sholud move
        ### For efficiency pieces are not moved as this is done
        ###     this must be done externally between converting each path segment
        ret = []
        for loc in sequence:
            ret.append(self.board[loc[0]][loc[1]])
        return ret

    def MovePiece(self, start, end):
        ##### Returns set of moves to move a piece from start to end
        ### Also executes this set of moves on the board
        totalInstructions = [] # concatenated instructions from all steps
        path = self.GeneratePath(start, end) # path we will move piece along
        currentLocation = start
        for p in path: # for each point in path, move zero so that piece can be slid along path
            self.locked[currentLocation[0]][currentLocation[1]] = 1
            totalInstructions += self.MoveZeroTo(p) # instructions to move zero
            totalInstructions.append(self.board[currentLocation[0]][currentLocation[1]])
            self.SlidePiece(currentLocation) # Slide piece along path
            self.locked[currentLocation[0]][currentLocation[1]] = 0
            currentLocation = p
        return totalInstructions
    
    def SolveRow(self, row):
        ##### Returns set of moves to solve row #row
        ### Also executes this set of moves on the board
        #### Solve row till 1 from end
        ret = [] # instructions to return
        for j in range(self.M-1):
            targetPiece = row*self.M + j + 1
            ret += self.MovePiece(self.pieceMap[targetPiece], (row, j))
            self.locked[row][j] = 1
        #### Move final piece in row to bottom right
        ret += self.MovePiece(self.pieceMap[ row*self.M + self.M-1 + 1 ], (self.N-1, self.M-1))
        #### Move zero to end of row
        ret += self.MoveZeroTo( (row, self.M-1) )
        #### Move 2nd from final piece in row, to end of the row
        self.locked[row][self.M-2] = 0
        ret.append(self.board[row][self.M-2])
        self.SlidePiece((row, self.M-2))
        self.locked[row][self.M-1] = 1
        #### move final piece in row next to its final location
        ret += self.MovePiece(self.pieceMap[ row*self.M + self.M-1 + 1 ], (row+1, self.M-1))
        self.locked[row+1][self.M-1] = 1
        #### move zero to 2 from row end
        ret += self.MoveZeroTo( (row, self.M-2) )
        #### unlock and perform final slides
        self.locked[row][self.M-1] = 0
        self.locked[row+1][self.M-1] = 0
        ret.append(self.board[row][self.M-1])
        ret.append(self.board[row+1][self.M-1])
        self.SlidePiece( (row, self.M-1) )
        self.SlidePiece( (row+1, self.M-1) )
        self.locked[row][self.M-2] = 1
        self.locked[row][self.M-1] = 1
        return ret
    
    def SolveColumn(self, col):
        ##### Returns set of moves to solve column #col
        ### Also executes this set of moves on the board
        #### Solve column till 1 from end
        ret = [] # instructions to return
        for i in range(self.N-1):
            targetPiece = i*self.M + col + 1
            ret += self.MovePiece(self.pieceMap[targetPiece], (i, col))
            self.locked[i][col] = 1
        #### Move final piece in column to bottom right
        ret += self.MovePiece(self.pieceMap[ (self.N-1)*self.M + col + 1 ], (self.N-1, self.M-1))
        #### Move zero to end of column
        ret += self.MoveZeroTo( (self.N-1, col) )
        #### Move 2nd to final piece in column to end of column
        self.locked[self.N-2][col] = 0
        ret.append(self.board[self.N-2][col])
        self.SlidePiece((self.N-2, col))
        self.locked[self.N-1][col] = 1
        #### final piece next to its target final place
        ret += self.MovePiece(self.pieceMap[ (self.N-1)*self.M + col + 1 ], (self.N-1, col+1))
        self.locked[self.N-1][col+1] = 1
        #### move zero to 2nd from end of column
        ret += self.MoveZeroTo( (self.N-2, col) )
        #### unlock and perform final slides
        self.locked[self.N-1][col] = 0
        self.locked[self.N-1][col+1] = 0
        ret.append(self.board[self.N-1][col])
        ret.append(self.board[self.N-1][col+1])
        self.SlidePiece( (self.N-1, col) )
        self.SlidePiece( (self.N-1, col+1) )
        self.locked[self.N-2][col] = 1
        self.locked[self.N-1][col] = 1
        return ret

            
    def MoveZeroTo(self, loc):
        ##### Returns set of moves to move zero a position
        ### Also executes this set of moves on the board
        #self.PrintLocked()
        path = self.GeneratePath(self.pieceMap[0], loc)
        instructions = self.ConvertToInstructions(path)
        self.ExecuteSequence(path)
        return instructions
    
    def CheckSolution(self):
        ##### Checks final 2x2 section to see if was solved
        for i in range(self.N-2, self.N):
            for j in range(self.M-2, self.M):
                target = i*self.M + j + 1
                if target == self.M*self.N: target = 0 # bottom right should have zero
                if self.board[i][j] != target: return False
        return True

    def __str__(self):
        result = "[\n"
        result += '\n'.join( '\t'.join(str(i) for i in row) for row in self.board)
        result += "\n]"
        return result
    
    def PrintBoard(self):
        print(str(self))
    
    def PrintLocked(self):
        result = "[\n"
        result += '\n'.join( '\t'.join(str(i) for i in row) for row in self.locked)
        result += "\n]"
        print(result)


def isNeighbour(p1, p2):
    ##### returns whether p1 and p2 are neighbours
    return ( abs(p1[0]-p2[0]) + abs(p1[1]-p2[1]) ) <= 1

def slide_puzzle(ar):
    board = Board(ar)
    #print(str(board))
    moves = board.Solve()
    #print(str(board))
    return moves
