class SlidingPuzzle:
    
    def __init__(self, init_state, size):
        self.size = size
        self.state = init_state
        self.moves = []
    
    def pos(self, val):
        x = next(i for i,row in enumerate(self.state) if val in row)
        return (x,self.state[x].index(val))
    
    def goal_pos(self, val):
        return ((val - 1) // self.size, (val - 1) % self.size)
    
    def in_pos(self, val):
        return self.pos(val) == self.goal_pos(val)
    
    def swap(self, position):
        (x,y),(x0,y0) = position,self.pos(0)
        self.moves.append(self.state[x][y])
        self.state[x0][y0], self.state[x][y] = self.state[x][y], 0
    
    def zero_step(self, dir):
        x0,y0 = self.pos(0)
        opt = {'up'    : (x0-1,y0), 'down'  : (x0+1,y0),
               'left'  : (x0,y0-1), 'right' : (x0,y0+1)}
        self.swap(opt[dir]) 
        
    def zero_steps(self, *dirs):    
        for dir in dirs: self.zero_step(dir)
    
    def zero_set(self, dir, rc):
        opt = {'up' : 0, 'down' : 0, 'left' : 1, 'right' : 1}      
        while self.pos(0)[opt[dir]] != rc:
            self.zero_step(dir)    
            
    def zero_edge(self, dir):
        opt = {'up'   : 0, 'down'  : self.size - 1,
               'left' : 0, 'right' : self.size - 1}
        self.zero_set(dir, opt[dir])
    
    def reset(self):
        self.zero_edge('down')
        self.zero_edge('right')
        
    def zero_path(self, *args):
        for dir,how in args:
            if how == 's':
                self.zero_step(dir)
            elif how == 'e':
                self.zero_edge(dir)
            else:
                self.zero_set(dir,how)
    
    def put_val(self, val, to_set):
        (x,y), (v,w) = self.pos(val), to_set
        if y == self.size - 1:                      # check if on the right
            self.zero_path(('left','s'),('up',x),('right','s'),('down','e'))
        x,y = self.pos(val)   
        if x == self.size - 1:                   # check if on the bottom
            self.zero_path(('up','s'),('left', y),('down','s'),('right','e'))
        x,y = self.pos(val)                
        if y < w:           # move right to correct column
            self.zero_path(('up', x),('left', y+1))   #position zero to right of one
            x,y = self.pos(val)
            while y < w:
                self.zero_steps('left','down','right','right','up')
                x,y = self.pos(val) 
        self.reset()
        if x > v:                         # move up to correct row
            self.zero_path(('left', y),('up', x+1))  # position zero below val         
            x,y = self.pos(val)              
            while x > v:
                self.zero_steps('right','up','up','left','down')
                x,y = self.pos(val)            
        self.reset()             
        if y > w:                        # move left to correct column   
            self.zero_path(('up', x),('left', y+1))    # position zero to right of val
            x,y = self.pos(val)                
            while y > w:
                self.zero_steps('down','left','left','up','right')
                x,y = self.pos(val)
        self.reset() 
        
    def set_val(self, val):
        return self.put_val(val, self.goal_pos(val))
    
    def first_size_minus_two_rows(self):
        def row_end(self, val):
            if self.in_pos(val):
                return None
            x,y = self.goal_pos(val)
            self.put_val(val, self.goal_pos(val + self.size - 2))
            self.zero_set('up',x)
            self.zero_steps('left','down','left','down','right','right','up','left','up','right')
            self.reset()
        for i in range(self.size - 2):
            for j in range(1, self.size):
                self.set_val( i * self.size + j )
            row_end(self, (i + 1) * self.size)    

    def last_two_rows(self):     
        def bottom_pairs(self, col):
            valA, valB = self.size*(self.size-2)+col+1, self.size*(self.size-1)+col+1
            self.set_val(valA)
            if self.in_pos(valB):
                return None
            self.put_val(valB, (self.size-2,col+1))
            self.zero_set('left',col+1)
            self.zero_steps('up','right','down','left','left','up','right','down','right','up','left','left')
            self.reset()     
        for i in range(self.size-2): bottom_pairs(self, i)
    
    def last_three_tiles(self):
        valA,valB,i = self.size*self.size - 1, self.size*(self.size - 1) - 1, 0
        while i < 3 and not ( self.in_pos(valA) and self.in_pos(valB) ):
            self.zero_steps('left','up','right','down')
            i += 1
        return False if i == 3 else True    
    
    def solve(self):
        self.reset()
        self.first_size_minus_two_rows()
        self.last_two_rows()
        return self.moves if self.last_three_tiles() else None

def slide_puzzle(init_state):
    return SlidingPuzzle(init_state,len(init_state)).solve()