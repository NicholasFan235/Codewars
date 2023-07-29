#include <math.h>

using namespace std;

double solve(double m)
{
    return 1 + (1/(2*m)) - std::sqrt(1/(4*m*m) + (1/m));
}