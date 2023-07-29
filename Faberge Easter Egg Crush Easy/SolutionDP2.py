
def f(n,m):
    dp = [[x for x in range(m+1)] for y in range(n+1)]
    dp[0] = [0 for x in range(m+1)]
    for i_n in range(2,n+1):
        for i_m in range(m-1):
            

def height(n,m):
    if (n==0 or m==0):
        return 0
    