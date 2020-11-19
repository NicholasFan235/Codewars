#include <bits/stdc++.h>

std::string pig_it(std::string str)
{
    std::istringstream iss(str);
    std::string s;
    std::ostringstream oss;
    while (iss){
        if (iss){
            iss >> s;
            oss << s.substr(1) << s[0] << "ay ";
        }
    }
    std::string ans = oss.str();
    return ans.substr(1, ans.length()-1);
}