#include <vector>

int findOdd(const std::vector<int>& numbers)
{
  int curr = 0;
  for (int i : numbers)
    {
    curr ^= i;
  }
  return curr;
}