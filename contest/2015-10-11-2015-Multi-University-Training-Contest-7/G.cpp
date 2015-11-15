#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <climits>
using namespace std;
const int INF = INT_MAX;
const int N = 2222222;
int n, f[N][2], point[N];
char text[N];
void solve() {
	scanf("%s", text + 1);
	n = strlen(text + 1);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &point[i]);	
	}
	f[0][0] = 0;
	f[0][1] = -INF;
	for (int i = 1; i <= n; i++) {
		if (text[i] == '?') {
			f[i][0] = max(f[i - 1][0], f[i - 1][1] + point[i]);
			f[i][1] = max(f[i - 1][0] + point[i], f[i - 1][1]);
		} else {
			int digit = text[i] - '0';
			if (digit == 1) {
				f[i][digit] = max(f[i - 1][0] + point[i], f[i - 1][1]);
				f[i][digit ^ 1] = -INF;
			} else {
				f[i][digit] = max(f[i - 1][0], f[i - 1][1] + point[i]);
				f[i][digit ^ 1] = -INF;
			}
		}
	}
	
	int ans;
	if (text[n] == '?') {
		ans = max(f[n][0], f[n][1]);
	} else {
		ans = f[n][text[n] - '0'];
	}
	
	printf("%d\n", ans);
}
int main() {
	int tests;
	scanf("%d", &tests);
	for (int i = 1; i <= tests; i++) {
		printf("Case #%d: ", i);
		solve();
	}
}
