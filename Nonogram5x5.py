class Nonogram:
    def solveRowFirst(self, clues, row):
        total = sum(clues)
        threshold = len(row)-total
        ctr = 0
        for i in range(len(clues)):
            ctr += clues[i]
            if clues[i] > threshold:
                ctr -= threshold
                for j in range(threshold):
                    row[ctr] = 1
                    ctr += 1
            ctr += 1
        print(row)
        pass

    def __init__(self, clues):
        self.clues = clues
        pass

    def solve(self):
        
        pass
        # TODO: Finish this!


clues = (((1, 1), (4,), (1, 1, 1), (3,), (1,)),
          ((1,), (2,), (3,), (2, 1), (4,)))

n = Nonogram(clues)
r = [0,0,0,0,0]
n.solveRowFirst([4], r)
n.solve()