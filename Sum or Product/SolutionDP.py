


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

test_cases = [
    ([1, 2, 3],  9),
    ([1, 1, 2],  4),
    ([1, 1, 1],  3),
    ([1],  1),
    ([9],  9),
    ([1, 1],  2),
    ([1, 5],  6),
    ([1, 5, 7],  42),
    ([1, 5, 6],  36),
    ([1, 1, 5, 7],  70),
    ([1, 1, 1, 1],  4),
    ([1, 1, 1, 1, 1],  6),
    ([1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],  1458),
    ([1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],  972),
    ([1, 1, 2, 4, 5],  80),
    ([10, 20, 30],  6000)
]

for case in test_cases:
    ans = sum_or_product(case[0])
    if ans != case[1]:
        print(case)
        print(ans)