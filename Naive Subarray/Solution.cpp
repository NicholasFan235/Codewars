#include <bits/stdc++.h>

std::array<std::set<int>, 524287> segment;



void reset(){

}

template<std::size_t S>
long long solve(std::array<int, S> input){
    std::array<int, S+1> xOr;
    xOr[0] = 0;
    for (int i = 0; i < S; i++){
        xOr[i+1] = xOr[i] ^ input[i];
    }
    return 0;
}


int main(){
    std::array<int, 27> q = {6,1,7,4,6,7,1,4,7,1,4,6,6,7,4,1,6,4,7,1,4,5,3,2,1,6,9};
    std::cout << solve(q) << std::endl;
}

