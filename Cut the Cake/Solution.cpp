#include <bits/stdc++.h>

std::vector<std::string> cake;

int numRasins;
int sliceArea;
int n, m;

bool subDivide(int area, int y1, int x1, int y2, int x2){
    // Check if valid
    int thisArea = (y1-y1+1) * (x2-x1+1);
    if (thisArea == area) return true;
    
    bool foundSolution = false;
    
    for (int i = y1; i < y2; i++){
        bool poss1 = subDivide(area, y1, x1, i, x2);
        bool poss2 = subDivide(area, i+1, x1, y2, x2);
        if (poss1 && poss2){
            foundSolution = true;
            break;
        }
    }

}

std::vector<std::string> split(std::string s, std::string delimiter){
    std::vector<std::string> result;
    long long pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos){
        token = s.substr(0, pos);
        result.push_back(token);
        s.erase(0, pos+delimiter.length());
    }
    result.push_back(s);
    return result;
}

std::vector<std::string> cut(const std::string &s){
    numRasins = std::count(s.begin(), s.end(), 'o');
    cake = split(s, "\n");

    for (const auto s : cake){
        std::cout << s << std::endl;
    }
    printf("%d rasins\n", numRasins);

    n = cake.size(); m = cake[0].size();
    sliceArea = n*m/numRasins;
    printf("Each slice must have area %d\n", sliceArea);

    return {};
}

std::string q = "........\n"
				"..o.....\n"
				"...o....\n"
				"........";
int main(){
    cut(q);
}
