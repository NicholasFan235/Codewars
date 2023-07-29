struct Decoder {
  static bool initialized;
  static std::map<char, char> charMap;
  static void initialize()
  {
    if (Decoder::initialized) return;
    initialized = true;
    std::string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()[]{}_+- .,1234567890<>=:;?";
    std::string response = "";
    for (unsigned long i = 0; i < alphabet.length(); i++)
    {
      response += Encoder::encode(std::string("") + alphabet[i])[0];
      Decoder::charMap[response[i]] = alphabet[i];
    }
  }
  
  static std::string decode (const std::string& p_what) {  
    Decoder::initialize();
    
    for (const std::pair<char, char> entry : Decoder::charMap)
    {
      std::cout << entry.first << " -> " << entry.second << std::endl;
    }
    
    std::string result = "";
    
    for (unsigned long i = 0; i < p_what.length(); i++)
    {
      char c = p_what[i];
      for (unsigned long j = 0; j <= i; j++)
      {
        if (Decoder::charMap.find(c) != Decoder::charMap.end())
        {
          c = Decoder::charMap[c];
        }
        else
        {
          std::cout << "Cannot Decode Char: " << c << std::endl;
        }
      }
      result += c;
    }
    
    return result;
  }
};

bool Decoder::initialized = false;
std::map<char, char> Decoder::charMap = std::map<char, char>();