def converge(g, u1, u2, u3):
    sets = [{u1}, {u2}, {u3}]
    
    ctr = 0
    while ctr < len(g):
        if len(sets[0].intersection(sets[1], sets[2])) > 0:
            return ctr
        
        ctr += 1
        for i in range(len(sets)):
            ns = set()
            for n in sets[i]:
                ns.update(g[n])
            sets[i] = ns

    return None