#include <iostream>
#include <cstdio>
#include <algorithm>
#include <climits>

using namespace std;
const int N = 111111;
int n, m;
int s[N], p[N];
pair<int, int> query[N];
long long answer[N], best[N];

void solve() {
	scanf("%d%d", &n, &m);	
	for (int i = 1; i <= n; i++) {
		scanf("%d%d", &s[i], &p[i]);
	}
	best[n + 1] = LONG_LONG_MAX;
	for (int i = n; i >= 1; i--) {
		best[i] = min(best[i + 1], 1LL * s[i] * p[i]);
	}
	
	for (int i = 1; i <= m; i++) {
		int x;
		scanf("%d", &x);
		query[i] = make_pair(x, i);
		answer[i] = LONG_LONG_MAX;
	}
	
	sort(query + 1, query + 1 + m);
	
	int now = 1;
	for (int i = 1; i <= m; i++) {
		for (; s[now] <= query[i].first && now <= n; now++);
		answer[query[i].second] = min(1LL * query[i].first * p[now - 1], best[now]);
	}
	
	for (int i = 1; i <= m; i++) {
		printf("%lld\n", answer[i]);
	}
	
}

int main() {
	int tests;
	scanf("%d", &tests);
	for (int i = 1; i <= tests; i++) {
		solve();
	}
	return 0;
}
