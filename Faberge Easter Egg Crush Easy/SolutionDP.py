
def height(n, m):
    if (n==0 or m==0):
        return 0
    
    dp = [[0 for x in range(m+1)] for x in range(2)]
    for j in range(1, m+1):
        dp[1][j] = j
    i = 1
    while (i < n):
        i += 1
        for j in range(1, m+1):
            dp[i%2][j] = 1 + dp[(i+1)%2][j-1] + dp[i%2][j-1]
    return dp[n%2][m]


