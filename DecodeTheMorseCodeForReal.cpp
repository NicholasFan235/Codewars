#include "MORSE_CODE.h"
#define morse_code MORSE_CODE

std::string bits;
std::map<int, int> pulse1Freq;
std::map<int, int> pulse0Freq;
double dt;
std::vector<std::pair<int, int>> pulses;
std::unordered_map<std::string, int> options1({ {".", 1}, {"-", 3} });
std::unordered_map<std::string, int> options0({ {"", 1}, {" ", 3}, {"   ", 7} });
double delta = 1e-10;

void reset(){
    pulse1Freq.clear();
    pulse0Freq.clear();
    pulses.clear();
}

void printPulseFreqs(){
    printf("0 pulses:\n");
    for (const auto p : pulse0Freq){
        printf("\t%d:\t%d\n", p.first, p.second);
    }
    printf("1 pulses:\n");
    for (const auto p : pulse1Freq){
        printf("\t%d:\t%d\n", p.first, p.second);
    }
}

void printPulses(){
    for (const auto p : pulses){
        printf("\t\t%d:\t%d\n", p.first, p.second);
    }
}

void conv2pulses(){
    int prev = bits[0] == '1';
    int ctr = 0;
    for (unsigned long i= 0; i < bits.size(); i++){
        int curr = bits[i] == '1';
        if (curr == prev){
            ctr++;
            continue;
        }
        if (prev) pulse1Freq[ctr]++;
        else pulse0Freq[ctr]++;
        pulses.push_back(std::make_pair(prev, ctr));
        ctr = 1;
        prev = curr;
    }
    if (prev) pulse1Freq[ctr]++;
    else pulse0Freq[ctr]++;
    pulses.push_back(std::make_pair(prev, ctr));
}

double calcTotalCost(double _dt){
    double totalCost = 0;
    for (const auto p : pulse0Freq){
        double cost = std::min(fabs((double)p.first - _dt), fabs((double)p.second - 3*_dt));
        cost = std::min(cost, fabs((double)p.first - 7 * _dt));
        totalCost += cost * p.second;
    }
    for (const auto p : pulse1Freq){
        double cost = std::min(fabs((double)p.first - _dt), fabs((double)p.first - 3*_dt));
        totalCost += cost * p.second;
    }
    return totalCost;
}

void findBestDt(){
    double bestCost = INFINITY;
    double totalCost;
    for (int i = 10; i > 0; i--){
        totalCost = calcTotalCost((double)i);
        if (totalCost < bestCost){
            bestCost = totalCost;
            dt = (double)i;
        }
    }
}

void refineDt(){
    double fx1, fx2, df;
    for (int i= 0; i < 10000; i++){
        fx1 = calcTotalCost(dt);
        fx2 = calcTotalCost(dt+delta);
        df = (fx2-fx1)/delta;
        
        dt -= df * 1e-5;
    }
}

void trim0s(std::string b){
    long start = -1;
    long end = b.size();
    while (b[++start]=='0');
    while (b[--end] == '0');
    bits = b.substr(start, end-start+1);
}

std::string decodePulses(){
    std::string decoded = "";
    for (const auto p : pulses){
        int cost = INT_MAX;
        std::string s;
        if (p.first == 1){
            for (const auto o : options1){
                int cCost = abs(p.second - dt * o.second);
                if (cCost < cost){
                    cost = cCost;
                    s = o.first;
                }
            }
        }
        else{
            for (const auto o : options0){
                int cCost = abs(p.second - dt * o.second);
                if (cCost < cost){
                    cost = cCost;
                    s = o.first;
                }
            }
        }
        decoded += s;
    }
    std::cout << decoded << std::endl;
    return decoded;
}

std::string decodeBitsAdvanced (std::string b) {
    // ToDo: Accept 0's and 1's, return dots, dashes and spaces
    reset();
    trim0s(b);
    std::cout << bits << std::endl;
    conv2pulses();
    //printPulseFreqs();
    findBestDt();
    //refineDt();
    printf("dt = %f\n", dt);

    return decodePulses();
}

std::string decodeMorse(std::string morseCode) {
    // ToDo: Accept dots, dashes and spaces, return human-readable message
    std::string decoded;
    std::string word = "";
    long start = -1;
    while (morseCode[++start] == ' ');
    long end = morseCode.length();
    while (morseCode[--end] == ' ');

    for (long i = start; i <= end; i++){
      char c = morseCode[i];
      if (c == ' '){
        if (word == ""){
          decoded += ' ';
          i++;
          continue;
        }
        else{
          // decode word
          decoded += morse_code[word];
          // reset word
          word = "";
        }
      }
      else{
          word += c;
      }
    }
    decoded += morse_code[word];
    return decoded;
}

std::vector<std::string> queries = {
    "0000000011011010011100000110000001111110100111110011111100000000000111011111111011111011111000000101100011111100000111110011101100000100000",
    "111111100000011010001110111000000001110000000000000000001111111011111100001101111100000111100111100011111100000001011100000011111110010001111100110000011111100101111100000000000000111111100001111010110000011000111110010000011111110001111110011111110000010001111110001111111100000001111111101110000000000000010110000111111110111100000111110111110011111110000000011111001011011111000000000000111011111011111011111000000010001001111100000111110111111110000001110011111100011111010000001100001001000000000000000000111111110011111011111100000010001001000011111000000100000000101111101000000000000011111100000011110100001001100000000001110000000000000001101111101111000100000100001111111110000000001111110011111100011101100000111111000011011111000111111000000000000000001111110000100110000011111101111111011111111100000001111110001111100001",
    "110110100111000001100000011111101001111100111111000000000001110111111110111110111110000001011000111111000001111100111011000001",
};

std::vector<std::string> answers = {
    "HEY JUDE",
    "THE QUICK BROWN FOX JUMPED OVER THE LAZY DOG",
};

int main(){
    std::string data = queries[0];
    std::string result = decodeBitsAdvanced(data);
    std::cout << decodeMorse(result) << std::endl;
    /*
    for (int i = -10; i < 10; i++){
        printf("%f, %f\n", (double)i, calcTotalCost((double)i));
    }*/
}

