#include <bits/stdc++.h>

using namespace std;

// returns pair, first = 1 for cycle, 0 for terminate, second = length of cycle or till terminate
std::pair<int, int> cycleLength(int n, int m)
{
	std::cout << "Cycle length of " << n << " mod " << m << std::endl;
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

int powModM(int a, int p, int m)
{
	if (p==0) return 1;
	if (a==0) return 0;

	int ans = 1;
	a = a % m;
	for (int i = 0; i < p; i++)
	{
		ans = (ans * a) % m;
		if (ans == 0)
			return m;
	}
	return ans;
}

int solve(list<int> array, int mod)
{
	if (array.empty())
		return 1;

	for (const int i : array){
		std::cout << i << " ";
	}
	std::cout << "mod " << mod << std::endl;

	int a = array.front();
	if (array.size()==1) return a%mod;
	array.pop_front();
	int p;
	if (array.size() >= 1)
	{
		std::pair<int, int> cycleInfo = cycleLength(a, mod);
		std::cout << cycleInfo.first << ", " << cycleInfo.second << std::endl;
		if (cycleInfo.first == 1){
			p = solve(array, cycleInfo.second);
		}
		else{
			if (cycleInfo.second < array.front()){
				p = mod;
			}
			else{
				p = solve(array, cycleInfo.second);
			}
		}
	}
	else
	{
		p = array.front();
		if (p == 0)
		{
			return 1;
		}
	}
	printf("%d^%d%%%d\n", a, p, mod);
	int ans = powModM(a, p, mod);
	std::cout << a << "^" << p << "%" << mod << " = " << ans << std::endl;
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

std::vector<std::list<int>> queries = //{{2147483647, 2147483647, 2147483647, 2147483647}};
{
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
		std::cout << last_digit(q) << std::endl;
	}
}