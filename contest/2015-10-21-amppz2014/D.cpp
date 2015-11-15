#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>

const int N = 2222222;

int n;
int a[N], count[N];
std::vector<int> value;

int main(void) {
	scanf("%d", &n);
	
	int maximum = 1;
	for (int i = 1; i <= n; ++i) {
		scanf("%d", a + i);

		count[a[i]]++;
		value.push_back(a[i]);
		maximum = std::max(maximum, a[i]);
	}
	
	std::sort(value.begin(), value.end());
	value.erase(std::unique(value.begin(), value.end()), value.end());
	
	long long answer = 0;
	for (int i = 0; i < (int)value.size(); ++i) {
		long long number = 0;
		for (int j = value[i]; j <= maximum; j += value[i]) {
			number += count[j];
		}
		answer += count[value[i]] * (number - 1);
	}
	
	std::cout << answer << std::endl;
}
