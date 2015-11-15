#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;
const double eps = 1e-8;
int n, m;
int a[111], b[111];
void solve() {
	scanf("%d%d", &n, &m);
	int suma = 0, sumb = 0;
	for (int i = 1; i <= n - 1; i++) {
		scanf("%d", &a[i]);
		suma += a[i];
	}
	double ava = suma * 1. / (n - 1);
	for (int i = 1; i <= m; i++) {
		scanf("%d", &b[i]);
		sumb += b[i];
	}
	double avb = sumb * 1. / m;
	
	int left = (int)ceil(avb + eps);
	int right = (int)floor(ava - eps);
	printf("%d %d\n", left ,right);
	
}

int main() {
	int tests;
	scanf("%d", &tests);
	for (int i = 1; i <= tests; i++) {
		solve();
	}
}
