from copy import copy, deepcopy

class Puzzle:
    def __init__(self, _b):
        self.walls = _b.deepcopy()
        self.N = len(_b)-1
        self.M = len(_b[0])-1
    
    
    
    
    

