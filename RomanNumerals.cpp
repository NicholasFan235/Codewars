#include <iostream>
#include <string>
#include <bits/stdc++.h>

std::map<char, int> M = {
    {'I', 1},
    {'V', 5},
    {'X', 10},
    {'L', 50},
    {'C', 100},
    {'D', 500},
    {'M', 1000}
};

int solution(std::string roman) {
    int highestSeen = 0;
    int ans = 0;
    for (int i = roman.length()-1; i >= 0; i--){
        int curr = M[roman[i]];
        if (curr >= highestSeen){
            highestSeen = curr;
            ans += curr;
        }
        else{
            ans -= curr;
        }
    }
    return ans;
}