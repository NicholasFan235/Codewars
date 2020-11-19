#include <bits/stdc++.h>

std::vector<long long> startIndices = {
    0,
    45,
    9045,
    1395495,
    189414495,
    23939649495,
    2893942449495,
    339393974949495,
    38939394344949495
};

std::vector<long long> a = {
    0,
    9,
    189,
    2889,
    38889,
    488889,
    5888889,
    68888889,
    788888889,
    8888888889
};

int nDigits(long long num){
    // num digits in the block number we end up in
    for (int i = startIndices.size()-1; i >= 0; i--){
        if (num > startIndices[i]){
            return i+1;
        }
    }
}

long long getN(long long num, int digits){
    // N is block number we end up in, returns i, answer is 'i'th digit in block
    long long i = 0;
    long long prevC = 0;
    while (1){
        i++;
        long long curr = i*a[digits-1] + (digits) * i * (i+1) / 2;
        if (curr >= num){
            //std::cout << "i: " << i-1 << std::endl;
            return num - prevC;
        }
        prevC = curr;
    }
}

int getAns(long long num){
    int numDigits = 0;
    while (1){
        numDigits++;
        long long sub = numDigits * 9*pow(10, numDigits-1);
        if (num - sub <= 0){
            break;
        }
        num -= sub;
    }
    int finalN = pow(10, numDigits-1) + (num-1)/numDigits;
    int digit = (num-1)%numDigits;
    //std::cout << numDigits << " digits, " << num << " Digit #" << digit << " of " << finalN << std::endl;
    return finalN/(int)pow(10, numDigits-digit-1) % 10;
}

int solve(long long num){
    int digits = nDigits(num);
    //std::cout << digits << " digits\n";
    num -= startIndices[digits-1];
    long long digitIndex = getN(num, digits);
    //std::cout << "Digit index: " << digitIndex << std::endl;
    return getAns(digitIndex);
}

std::vector<long long> queries = //{999999999999999999};//{9234, 9235, 9426, 9427, 9621, 9622};
{1, 2, 3, 100, 2100, 31000, 55, 123456, 123456789, 999999999999999999, 1000000000000000000, 999999999999999993};

int main(){
    
    for (const auto q : queries){
        std::cout << q << " -> " << solve(q) << std::endl;
    }
    //*/
    //long long i;
    //std::cin >> i;
    //std::cout << solve(i) << std::endl;
}