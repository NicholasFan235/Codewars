#include "MORSE_CODE.h"

std::string decodeMorse(std::string morseCode) {
    // ToDo: Accept dots, dashes and spaces, return human-readable message
    std::string decoded;
    std::string word = "";
    int start = -1;
    while (morseCode[++start] == ' ');
    int end = morseCode.length();
    while (morseCode[--end] == ' ');

    for (int i = start; i <= end; i++){
      char c = morseCode[i];
      if (c == ' '){
        if (word == ""){
          decoded += ' ';
          i++;
          continue;
        }
        else{
          // decode word
          decoded += MORSE_CODE[word];
          // reset word
          word = "";
        }
      }
      else{
          word += c;
      }
    }
    decoded += MORSE_CODE[word];
    return decoded;
}

int main(){
    std::cout << decodeMorse(".... . -.--   .--- ..- -.. .") << std::endl;
    return 0;
}

