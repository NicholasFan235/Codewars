def sum_or_product(arr):
    arr.sort(reverse=True)

    dp = [[0 for i in range(j+1)] for j in range(len(arr))]
    for i in range(len(arr)):
        for j in range(len(arr)):
            dp[j][0] = dp[j][0] + arr[i]
            dp[j].sort()

    m = 0
    for d in dp:
        c = 1
        for i in d:
            c *= i
        m = max(m,c)
    return m