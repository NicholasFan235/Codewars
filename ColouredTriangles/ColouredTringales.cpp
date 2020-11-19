#include <bits/stdc++.h>

std::map<std::pair<char, char>, char> mix({
{{'G', 'G'}, 'G'},
{{'R', 'R'}, 'R'},
{{'B', 'B'}, 'B'},
{{'G', 'B'}, 'R'},
{{'B', 'G'}, 'R'},
{{'B', 'R'}, 'G'},
{{'R', 'B'}, 'G'},
{{'R', 'G'}, 'B'},
{{'G', 'R'}, 'B'},
});

std::string nextRow(const std::string &row){
    std::string result = "";
    char prev = row[0];
    for (int i = 1; i < row.length(); i++){
        char curr = row[i];
        std::pair<char, char> key = std::make_pair(prev, curr);
        result += mix[key];
        prev = curr;
    }
    return result;
}

char triangle(const std::string &r){
    std::string row = r;
    while (row.length() > 1){
        row = nextRow(row);
    }
    return row[0];
}


std::vector<std::string> queries = {
    "B",
    "GB",
    "RRR",
    "RGBG",
    "RBRGBRB",
    "RBRGBRBGGRRRBGBBBGG",
};

int main(){
    for (const auto q : queries){
        std::cout << triangle(q) << std::endl;
    }
}
