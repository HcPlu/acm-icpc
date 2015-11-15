#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <map>

#define hash HASH
using namespace std;
const int N = 1111;
pair<int, int> a[N];
int counter;
int n, b[N], tree[2][N][N], f[N][N];
map<int, int> hash;


int lowbit(int x) {
	return x & -x;
}
void update(int &x, int y) {
	x = max(x, y);
}
void insert(int id, int num, int pos, int x) {
	for (int i = pos; i <= counter; i += lowbit(i)) {
		update(tree[id][num][i], x);
	}
}
int query(int id, int num, int pos) {
	int ret = 0;
	for (int i = pos; i > 0; i -= lowbit(i)) {
		ret = max(ret, tree[id][num][i]);
	}
	return ret;
}

void solve() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d%d", &a[i].first, &a[i].second);
		b[i] = a[i].second;
		a[i].first *= -1;
	}
	hash.clear();
	sort(a + 1, a + n + 1);
	sort(b + 1, b + n + 1);
	
	counter = 2;
	hash[b[1]] = 2;
	for (int i = 2; i <= n; i++) {	
		if (hash.count(b[i]) == 0) hash[b[i]] = ++counter;
	}
	
	for (int i = 1; i <= n; i++) {
		a[i].second = hash[a[i].second];
	}
	
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= n; j++) {
			f[i][j] = 0;
		}
	}
	
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= counter; j++) 
			for (int k = 0; k < 2; k++) {
				tree[k][i][j] = 0;
			}
	
	a[0].second = 1;
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < i; j++) {
			f[i][j] = query(1, j, a[i].second) + 1;
			insert(1, j, a[i].second, f[i][j]);
			insert(0, i, a[j].second, f[i][j]);
			ans = max(ans, f[i][j]);
		}
		for (int j = 0; j < i; j++) {
			f[j][i] = query(0, j, a[i].second) + 1;
			insert(0, j, a[i].second, f[j][i]);
			insert(1, i, a[j].second, f[j][i]);
			ans = max(ans, f[j][i]);
		}
	}
	
	printf("%d\n", ans);
	
}
int main() {
	int tests;
	scanf("%d", &tests);
	for (int i = 1; i <= tests; i++) {
		solve();
	}
	return 0;
}
