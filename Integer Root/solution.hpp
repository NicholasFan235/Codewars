#include <bits/stdc++.h>



std::string mul(const std::string& a, const std::string& b)
{
    int lenA = a.size(); int lenB = b.size();
    if (lenA == 0 || lenB == 0) return "0";

    std::vector<int> ans(lenA + lenB, 0);
    
    int i_a = 0;
    for (int i = lenA-1; i >= 0; i--)
    {
        int carry = 0;
        int digitA = a[i]-'0';

        int i_b = 0;
        for (int j = lenB-1; j >= 0; j--)
        {
            int digitB = b[j]-'0';

            int temp = digitA * digitB + ans[i_a+i_b] + carry;

            carry = temp/10;
            ans[i_a+i_b] = temp%10;

            i_b++;
        }

        if (carry > 0)
        {
            ans [i_a + i_b] += carry;
        }

        i_a++;
    }

    int i = ans.size() - 1;
    while (i>=0 && ans[i] == 0) i--;
    if (i==-1) return "0";

    std::string s = "";
    while (i >= 0)
        s += std::to_string(ans[i--]);
    return s;
}

std::string sum(const std::string& a, const std::string& b)
{
    int lenA = a.size(); int lenB = b.size();
    std::vector<int> ans(std::max(lenA, lenB) + 1, 0);
    int i = 0;

    auto itA = a.rbegin();
    auto itB = b.rbegin();

    int carry = 0;
    while (itA != a.rend() && itB != b.rend() && carry != 0)
    {
        if (itA != a.rend())
        {
            carry += *itA;
            itA++;
        }
        if (itB != b.rend())
        {
            carry += *itB;
            itB++;
        }

        ans[i++] = carry%10;
        carry /= 10;
    }

    i = 0;
    while (i < ans.size() && ans[i] == 0) i++;
    if (i==ans.size()) return "0";

    std::string s = "";
    while (i < ans.size())
        s += std::to_string(ans[i++]);
    return s;
}
