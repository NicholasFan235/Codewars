#include <bits/stdc++.h>

class Magnets
{
public:
    static double v(int k, int n)
    {
        return 1/(k*std::pow(n+1, 2*k));
    }
    static double u(int k, int n)
    {
        double ans = 0;
        for (int i = 1; i <= n; i++)
        {
            ans += Magnets::v(k,i);
        }
        return ans;
    }
    static double doubles(int maxk, int maxn)
    {
        double ans = 0;
        for (int i = 1; i <= maxk; i++)
        {
            ans += Magnets::u(i, maxn);
        }
        return ans;
    }
};

void test(double a, double b)
{
    printf("%.10f ~= %.10f\n", a, b);
}

int main()
{
    test(Magnets::doubles(1, 10), 0.5580321939764581);
    test(Magnets::doubles(10, 1000), 0.6921486500921933);
    test(Magnets::doubles(10, 10000), 0.6930471674194457);
    test(Magnets::doubles(20, 10000), 0.6930471955575918);
}