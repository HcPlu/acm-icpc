#include <cstring>
#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
int a[514][514], b[514][514];
void print(int n) {
	if (n == 1) {
		puts("1");
		return;
	}
	if (n == 2) {
		puts("1 2");
		puts("4 3");
		return;
	}
	if (n & 1) {
		a[1][1] = 1;
		a[1][2] = 2;
		a[1][3] = 3;
		a[2][3] = 4;
		a[3][3] = 5;
		a[3][2] = 6;
		a[2][2] = 7;
		a[2][1] = 8;
		a[3][1] = 9;
		for (int i = 5; i <= n; i += 2) {
			for (int j = 1; j <= i - 2; j++) {
				for (int k = 1; k <= i - 2; k++) {
					b[j][k] = a[k][i - 1 - j];
				}
			}
			for (int j = 1; j <= i - 2; j++) {
				for (int k = 3; k <= i; k++) {	
					a[j][k] = b[j][k - 2] + (i - 2) * 2;
				}
			}
			int now = 0;
			for (int j = 1; j <= i - 2; j++) {
				if (j & 1) {
					a[j][1] = ++now;
					a[j][2] = ++now;
				} else {
					a[j][2] = ++now;
					a[j][1] = ++now;
				}
			}
			now += (i - 2) * (i - 2);
			for (int j = i; j >= 1; j--) {
				if (j & 1) {
					a[i - 1][j] = ++now;
					a[i][j] = ++now;
				} else {
					a[i][j] = ++now;
					a[i - 1][j] = ++now;
				}
			}
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				printf("%d%s", a[i][j], j == n ? "\n" : " ");
			}
		}
		return;
	}
	
	int now = 0;
	for (int j = 1; j <= n; j += 4) {
		for (int i = 1; i <= n - 2; i++) {
			if (i & 1) {
				a[i][j] = ++now;				
				a[i][j + 1] = ++now;
			} else {
				a[i][j + 1] = ++now;
				a[i][j] = ++now;
			}
		}
		a[n - 1][j] = ++now;
		a[n][j] = ++now;
		a[n][j + 1] = ++now;
		a[n - 1][j + 1] = ++now;
		a[n - 1][j + 2] = ++now;
		a[n][j + 2] = ++now;
		a[n][j + 3] = ++now;
		a[n - 1][j + 3] = ++now;
		for (int i = n - 2; i >= 1; i--){
			if (i & 1) {
				a[i][j + 2] = ++now;
				a[i][j + 3] = ++now;
			} else {
				a[i][j + 3] = ++now;
				a[i][j + 2] = ++now;
			}
		}
	}
	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			printf("%d%s", a[i][j], j == n ? "\n" : " ");
		}
	}
}
void solve() {
	int n;
	scanf("%d", &n);
	print(n);
}

int main() {
	int n;
	int tests;
	scanf("%d", &tests);
	for (int i = 1; i <= tests; i++) {
		solve();
	}
}
