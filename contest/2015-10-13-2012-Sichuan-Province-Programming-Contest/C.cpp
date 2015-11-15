#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;
void solve() {
	int n, m, query;
	scanf("%d%d", &n, &m);
	scanf("%d", &query);
	for (int i = 1; i <= query; i++) {
		int x;
		scanf("%d", &x);
		int ans = min(n, x - 1) - max(1, x - m) + 1;
		if (ans <= 0) {
			printf("0\n");
		} else {
			printf("%d\n", ans);
		}
	}
}
int main() {
	int tests;
	scanf("%d", &tests);
	for (int i = 1; i <= tests; i++) {
		printf("Case #%d:\n", i);
		solve();
	}
}
