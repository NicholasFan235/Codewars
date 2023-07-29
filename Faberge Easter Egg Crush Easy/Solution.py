
previousResults = {}

def f(n, m):
    if (n==1):
        return m
    if (m==1):
        return 1

    if (n,m) in previousResults:
        return previousResults[(n,m)]

    tmp1 = f(n-1, m-1)
    tmp2 = f(n, m-1)
    ans = tmp1 + tmp2 + 1
    previousResults[(n,m)] = ans
    return ans

"""
solve f(100000)
{
    solve f(99999)
    {
        solve f(99998)
        {

        }
    }
}
let's solve (1,1)
now let's solve (1,2) ..... (1,m)
new solve (2,1).... (2,m)

(2,5) =  (1,4) + (2,4)
         (1,4) + (1,3) + (2,3)
         (1,4) + (1,3) + (1,2) + (2,2)
         (1,4) + (1,3) + (1,2) + (1,1) + (2,1)

height 7 20 = 137979

test.assert_equals(height(7,500),1507386560013475)


"""