#include <bits/stdc++.h>

class DoubleLinear{
public:
    static int dblLinear(int n);
public:
    static std::vector<int> solved;
    static int nextCheck2;
    static int nextCheck3;
    
    static void addNextInSequence(){
        int poss2 = 2*solved[nextCheck2]+1;
        int poss3 = 3*solved[nextCheck3]+1;
        if (poss3>poss2){
            nextCheck2++;
            if (solved.back() != poss2) solved.push_back(poss2);
        }
        else{
            nextCheck3++;
            if (solved.back() != poss3) solved.push_back(poss3);
        }
    }
};

std::vector<int> DoubleLinear::solved = {1};
int DoubleLinear::nextCheck2 = 0;
int DoubleLinear::nextCheck3 = 0;

int DoubleLinear::dblLinear(int n){
    while (DoubleLinear::solved.size() <= n){
        DoubleLinear::addNextInSequence();
    }
    return DoubleLinear::solved[n];
}

int main(){
    std::cout << DoubleLinear::dblLinear(20) << std::endl;
    for (const auto i : DoubleLinear::solved){
        std::cout << i << " ";
    }
    std::cout << std::endl;
}