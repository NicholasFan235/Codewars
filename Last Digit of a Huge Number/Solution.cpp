#include <bits/stdc++.h>

using namespace std;


// returns pair, first = 1 for cycle, 0 for terminate, second = length of cycle or till terminate
std::pair<int, int> cycleLength(int n, int m)
{
	//std::cout << "Cycle length of " << n << " mod " << m << std::endl;
	int i = 0;
	n = n % m;
	if (n == 0)
		n = m;
	int x = n;
	while (1)
	{
		i++;
		x = (x * n) % m;
		if (x == 0){
			//std::cout << i << std::endl;
			return std::make_pair(0, i+1);
		}
		//std::cout << x << " x " << n << std::endl;
		if (x == n)
		{
			//std:cout << i << std::endl;
			return std::make_pair(1, i);
		}
	}
}


int powModM(int a, int p, int m, std::pair<int, int> cycleInfo)
{
	if (p==0) return 1;
	if (a==0) return 0;

    if (cycleInfo.first == 0 && p >= cycleInfo.second) return m;
    p %= cycleInfo.second;
    if (p==0) p = cycleInfo.second;

	int ans = 1;
	a = a % m;
	for (int i = 0; i < p; i++)
	{
		ans = (ans * a) % m;
	}
	return ans;
}

int solve(list<int> array, int mod)
{
	if (array.empty())
		return 1;

	int a = array.front();
    array.pop_front();
	if (array.size()==0) {
        //printf("%d, return\n", a);
        return a;
    }
	int p = array.front();
	std::pair<int, int> cycleInfo = cycleLength(a, mod);
    printf("%d mod %d: cycle info = %d, %d.\n", a, mod, cycleInfo.first, cycleInfo.second);
    //printf("Cycle info: %d, %d, p = %d, mod = %d\n", cycleInfo.first, cycleInfo.second, p, mod);
    printf("Calling solve on array size %d, mod = %d\n", (int)array.size(), cycleInfo.second);
    int power = solve(array, cycleInfo.second);
    printf("Calling solve on array size %d, mod = %d. Result = %d\n", (int)array.size(), cycleInfo.second, power);

    printf("Calling PowModM %d^%d mod %d, cycle info: %d, %d\n", a, power, mod, cycleInfo.first, cycleInfo.second);
    int ans = powModM(a, power, mod, cycleInfo);
    /*std::cout << a << " ";
    for (const int i : array){
		std::cout << i << " ";
	}
	std::cout << "mod " << mod << std::endl;//*/
    
    printf("%d\n", ans);
    return ans;
}

int last_digit(list<int> array)
{
	// Write your code here
	/*for (const auto i : array){
		std::cout << i << " ";
	}*/
	int ans = solve(array, 10) % 10;
	//std::cout << "-> " << ans << std::endl;
	return ans;
}


std::vector<std::list<int>> queries = {{2, 2, 101, 2}};
/*{
	{},
	{0, 0},
	{0, 0, 0},
	{1, 2},
	{3, 4, 5},
	{4, 3, 6},
	{7, 6, 21},
	{12, 30, 21},
	{2, 2, 2, 0},
	{937640, 767456, 981242},
	{123232, 694022, 140249},
	{499942, 898102, 846073},
};//*/

int main()
{
	for (const auto q : queries)
	{
		int ans = last_digit(q);
        printf("\t%d\n", ans);
	}
}


