

factorial = [1 for x in range(20001)]
for i in range(1, 20001):
    factorial[i] = i*factorial[i-1]

prevCalcs = {}

def nCr(n, r):
    if (n==0):
        return 0
    if (n,r) in prevCalcs:
        return prevCalcs[(n,r)]
    prevCalcs[(n,r)] = (factorial[n]//factorial[n-r])//factorial[r]
    return prevCalcs[(n,r)]


def height(n, m):
    if (n==0 or m==0):
        return 0
    ans = 0
    if (n > m):
        n = m
    
    # sum ( copies * height(1, m-i) ) where i from (n-1) to (m-1) 
    for i in range((n-1), m):
        copies = nCr(i,n-1) - nCr(i-1, n-1)
        ans += (m-i+1)*copies
    
    # sum ( height(n-i, 1) ) where i from 0 to (n-2)
    for i in range(0, n-1):
        copies = nCr(m-1, i)
        ans += 2*copies
    return ans-1
        
