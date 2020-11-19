#include <bits/stdc++.h>
std::pair<long, long> countWaysWithFinal(const std::vector<bool> &b, const std::string &ops, int start, int end, int final);

std::map<std::pair<long, long>, std::pair<long, long>> dynamic;

std::pair<long, long> operator+(const std::pair<long, long> &a, const std::pair<long, long> &b){
    return std::make_pair(a.first + b.first, a.second + b.second);
}

std::pair<long, long> countWays(const std::vector<bool> &b, const std::string &ops, int start, int end){
    if (start==end){
        return b[start]==true ? std::make_pair(1, 0) : std::make_pair(0, 1);
    }

    std::pair<long, long> key = std::make_pair(start, end);
    if (dynamic.count(key) > 0){
        return dynamic[key];
    }

    std::pair<long, long> ways = std::make_pair(0, 0);
    //printf("%d - %d\n", start, end);
    for (int i = start; i < end; i++){
        std::pair<long, long> count = countWaysWithFinal(b, ops, start, end, i);
        //printf("Final = %d, ways: %d, %d\n", i, count.first, count.second);
        ways = ways + count;
    }
    dynamic[key] = ways;
    return ways;
}

std::pair<long, long> countWaysWithFinal(const std::vector<bool> &b, const std::string &ops, int start, int end, int final){
    std::pair<long, long> c1, c2;
    c1 = countWays(b, ops, start, final);
    c2 = countWays(b, ops, final+1, end);
    switch (ops[final]){
        case '&':
            return std::make_pair(c1.first * c2.first, c1.first * c2.second + c1.second * c2.first + c1.second * c2.second);
        case '|':
            return std::make_pair(c1.first * c2.first + c1.first * c2.second + c1.second * c2.first, c1.second * c2.second);
        case '^':
            return std::make_pair(c1.first * c2.second + c1.second * c2.first, c1.first * c2.first + c1.second * c2.second);
    }
}

int64_t solve(const std::string &s, const std::string &ops)
{
    dynamic.clear();
    std::vector<bool> b;
    for (const auto c : s){
        b.push_back(c=='t');
    }
    std::pair<long, long> ways = countWays(b, ops, 0, b.size()-1);
    return ways.first;
}

int main(){
    std::string s = "ttftfftftffttfftftftfftft";
    std::string ops = "|&^&&||^&&^^|&&||^&&||&^";

    printf("%ld\n", solve(s, ops));
}


