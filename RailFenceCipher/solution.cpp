#include <bits/stdc++.h>

std::string encode_rail_fence_cipher(const std::string &str, int n)
{
    std::string result = "";
    int period = 2 * n - 2;
    for (long i = 0; i < n; i++)
    {
        for (long j = 0; j < (long)str.length(); j += period)
        {
            if (i < n - 1 && j + i < (long)str.length())
            {
                result += str[j + i];
                std::cout << j + i << ", ";
            }
            if (i > 0 && j + period - i < (long)str.length())
            {
                result += str[j + period - i];
                std::cout << j + period - i << ", ";
            }
        }
    }
    std::cout << str << std::endl
              << result << std::endl;
    return result;
}

std::string decode_rail_fence_cipher(const std::string &str, int n)
{
    std::string result(str.length(), ' ');
    int period = 2 * n - 2;
    int ctr = 0;
    for (long i = 0; i < n; i++)
    {
        for (long j = 0; j < (long)str.length(); j += period)
        {
            if (i < n - 1 && j + i < (long)str.length())
            {
                result[j + i] = str[ctr++];
                std::cout << j + i << ", ";
            }
            if (i > 0 && j + period - i < (long)str.length())
            {
                result[j + period - i] = str[ctr++];
                std::cout << j + period - i << ", ";
            }
        }
    }
    std::cout << str << std::endl
              << result << std::endl;
    return result;
}


int main()
{
}