#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

int len;
int digit[22];
int f[22][(1 << 9) * 10 + 17];

int dfs(int now, int sum, int up) {
	if (now < 0) return sum >= 0;	
	if (sum < 0) return 0;
	
	if (!up && f[now][sum] != -1) {
		return f[now][sum];
	}

	int bound = up ? digit[now] : 9;	
	
	int ret = 0;
	for (int i = 0; i <= bound; ++i) {
		ret += dfs(now - 1, sum - (1 << now) * i, up && (i == bound));
	}
	
	if (!up) {
		f[now][sum] = ret;
	}
	
	return ret;
}

int a, b;

__inline int ff(int x) {
	int answer = 0;
	for (int base = 1; x > 0; base <<= 1, x /= 10) {
		answer += (x % 10) * base;
	}
	return answer;
}

void solve() {
	scanf("%d%d", &a, &b);
	
	len = 0;
	for (; b > 0; b /= 10) {
		digit[len++] = b % 10;
	}

	printf("%d\n", dfs(len - 1, ff(a), 1));
}

int main() {
	memset(f, -1, sizeof(f));
	
	int tests;
	scanf("%d", &tests);
	for (int i = 1; i <= tests; i++) {
		printf("Case #%d: ", i);
		solve();
	}
}
