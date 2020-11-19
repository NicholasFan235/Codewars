

class Board:
    def __init__(self, _b):
        self.b = _b.copy()
        self.N = len(_b)
        self.M = len(_b[0])

    def __str__(self):
        # Convert to string to print
        return '\n'.join( ', '.join(str(p) for p in row ) for row in self.b) + '\n'
    
    def ApplyMoves(self, moves):
        moveDecoder = { 'U': self.RotateUp, 'D': self.RotateDown, 'L': self.RotateLeft, 'R': self.RotateRight }
        for move in moves:
            i = int(move[1:])
            moveDecoder[move[0]](i)

    def RotateUp(self, column):
        tmp = self.b[0][column]
        for i in range(self.N-1):
            self.b[i][column] = self.b[i+1][column]
        self.b[-1][column] = tmp

    def RotateDown(self, column):
        tmp = self.b[-1][column]
        for i in reversed(range(self.N-1)):
            self.b[i+1][column] = self.b[i][column]
        self.b[0][column] = tmp

    def RotateLeft(self, row):
        tmp = self.b[row][0]
        for i in range(self.M-1):
            self.b[row][i] = self.b[row][i+1]
        self.b[row][-1] = tmp
    
    def RotateRight(self, row):
        tmp = self.b[row][-1]
        for i in reversed(range(self.M-1)):
            self.b[row][i+1] = self.b[row][i]
        self.b[row][0] = tmp
    
    def FindPiece(self, piece):
        # Return location of piece
        for i in reversed(range(len(self.b))):
            for j in reversed(range(len(self.b[i]))):
                if (self.b[i][j] == piece):
                    return [i, j]
        return None


def rotatePieceUp(origin, target, N, M):
    # Works for any row apart from bottom
    # Move origin to target, target must be above origin
    # target row and above are not affected
    # Returns move sequence
    #print("Move piece from " + str(origin) + " to " + str(target))
    moves = []
    ##### if origin and target are in same column, move out of way
    if (origin[1] == target[1]):
        moves.append('R'+str(origin[0]))
        origin[1] = (origin[1]+1) % M
    ##### move target down to same row as origin
    downCtr = 0
    while target[0] != origin[0]:
        moves.append('D'+str(target[1]))
        target[0] = (target[0] + 1) % N
        downCtr += 1
    ##### move origin into target column
    while target[1] != origin[1]:
        moves.append('R'+str(origin[0]))
        origin[1] = (origin[1] + 1) % M
    ##### move target (with origin in place) back up
    while downCtr > 0:
        downCtr -= 1
        moves.append('U'+str(origin[1]))
    return moves
    

def rotatePieceDown(target):
    # Move piece down 1 square without effecting anything in target row and abover
    # Returns move sequence
    moves = []
    moves.append('D'+str(target[1]))
    moves.append('R'+str(target[0]+1))
    moves.append('U'+str(target[1]))
    moves.append('L'+str(target[0]+1))
    return moves

def movePiece(origin, target, N, M):
    moves = []
    if (origin[0] == target[0] and origin[1] == target[1]): return []
    if (origin[0] == target[0]):
        moves += rotatePieceDown(origin)
        origin[0] = (origin[0] + 1) % N
    #print(origin)
    moves += rotatePieceUp(origin, target, N, M)
    return moves

def cyclicPermuteRight(left, right, N, M):
    ### Perform right cyclic permutation on last row
    # In last row, left, left+1 and right are right cyclic permuted
    # right must be at least 2 greater than left
    moves = []
    moves.append('D'+str((left+1) % M))
    moves += ['L'+str(N-1)] * (right-left-1 % M)
    moves.append('U'+str((left+1) %M))
    moves += ['R'+str(N-1)] * (right-left % M)
    moves.append('D'+str((left+1)%M))
    moves.append('L'+str(N-1))
    moves.append('U'+str((left+1)%M))
    return moves



def cyclicPermuteLeft(left, N, M):
    ### Perform left cyclic permutation on last row
    # In last row, left, left+1 and left+2 are left cyclic permuted
    moves = []
    moves.append('D'+str((left+1)%M))
    moves.append('R'+str(N-1))
    moves.append('U'+str((left+1)%M))
    moves += ['L'+str(N-1)] * 2
    moves.append('D'+str((left+1)%M))
    moves.append('R'+str(N-1))
    moves.append('U'+str((left+1)%M))
    return moves

def cyclicParity(board, solvedBoard):
    cycles = []
    explored = []
    cycle = 0
    for i in range(board.M):
        currentPiece = board.b[-1][i]
        if currentPiece in explored: continue
        explored.append(currentPiece)
        while True:
            targetLocation = solvedBoard.FindPiece(currentPiece)
            currentPiece = board.b[-1][targetLocation[1]]
            cycle += 1
            if (currentPiece in explored): break
            explored.append(currentPiece)
        cycles.append(cycle)
        cycle = 0
    parity = sum( [(cycle-1)%2 for cycle in cycles] ) % 2
    #print("Parity = " + str(parity))
    return parity
        
        

def SolveBoard(board, solvedBoard):
    ##### Solve all rows but last
    moves = []
    for i in range(board.N-1):
        for j in range(board.M):
            targetPiece = solvedBoard.b[i][j]
            originLocation = board.FindPiece(targetPiece)
            #print(str(board))
            #print("Move piece " + targetPiece + " from (" + str(originLocation[0]) + ", " + str(originLocation[1]) + ") to (" + str(i) + ", " + str(j) + ")\n")
            newMoves = movePiece(originLocation, [i, j], board.N, board.M)
            #print(newMoves)
            board.ApplyMoves(newMoves)
            moves += newMoves
    ##### For last row perform cyclic permutations
    print(str(board))
    #### Cyclic permutations preserve distance parity therefore make sure distance parity is even otherwise is unsolveable
    if board.M%2 == 1:
        ### If odd row, then if cyclic parity is odd, then unsolveable, otherwise definitely solveable
        if cyclicParity(board, solvedBoard) == 1:
            ## Unsolveable
            return None
    else:
        ### If even row, then rotate bottom row till cyclic parity is even, then is solveable
        while cyclicParity(board, solvedBoard) == 1:
            ## Rotate row
            moves.append('L'+str(board.N-1))
            board.ApplyMoves(['L'+str(board.N-1)])
    for j in range(board.M-2):
        targetPiece = solvedBoard.b[board.N-1][j]
        originLocation = board.FindPiece(targetPiece)
        print(str(board))
        print("Move piece " + targetPiece + " from (" + str(originLocation[0]) + ", " + str(originLocation[1]) + ") to (" + str(board.N-1) + ", " + str(j) + ")\n")
        if originLocation[1] == j: continue ## If already in place
        if (originLocation[1]-j) % board.M > 1:
            ### If at least 2 units away, right cyclic permute into position
            newMoves = cyclicPermuteRight(j, originLocation[1], board.N, board.M)
            print("Right cyclic permute")
            print(newMoves)
        else:
            ### If one unit away, left cyclic permute into position
            newMoves = cyclicPermuteLeft(j, board.N, board.M)
            print("Left cyclic permute")
            print(newMoves)
        ### Execute new moves
        board.ApplyMoves(newMoves)
        moves+=newMoves
        
    return moves

def transposeBoard(board):
    N = len(board)
    M = len(board[0])
    ret = [ [0]*N for i in range(M) ]
    for i in range(N):
        for j in range(M):
            ret[j][i] = board[i][j]
    return ret

def transposeMoves(moves):
    ret = []
    transposeMap = { 'U': 'L', 'D': 'R', 'L': 'U', 'R': 'D' }
    for move in moves:
        ret.append( transposeMap[move[0]] + move[1:] )
    return ret

def loopover(mixed_up_board, solved_board):
    n = len(mixed_up_board)
    m = len(mixed_up_board[0])
    ## if N*M is even, always solveable
    ## if N*M is odd, solve odd row or column last, and check cyclic parity. Cyclic parity is preserved through cyclic permutations
    ##     if row is even, can change cyclic parity by rotating row, but if odd then cannot
    flip = False
    if (m%2==1 and n%2==0):
        flip = True
        mixed_up_board = transposeBoard(mixed_up_board)
        solved_board = transposeBoard(solved_board)
    board = Board(mixed_up_board)
    solvedBoard = Board(solved_board)
    moves = SolveBoard(board, solvedBoard)
    ## If original board was flipped, flip moves back
    if flip:
        moves = transposeMoves(moves)
    return moves

test = 'WCMDJ0\nORFBA1\nKNGLY2\nPHVSE3\nTXQUI4\nZ56789'
test = [list(row) for row in test.split('\n')]

solution = 'ABCDEF\nGHIJKL\nMNOPQR\nSTUVWX\nYZ0123\n456789'
solution = [list(row) for row in solution.split('\n')]

loopover(test, solution)

