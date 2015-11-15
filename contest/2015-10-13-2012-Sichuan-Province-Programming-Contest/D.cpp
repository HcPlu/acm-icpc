#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>

using namespace std;
const int N = 111111;

int num[N], ans[N], n, maxn;
long long sum[N], backup[N];
int a[N], x[N];

void print(int pos) {
	for (int i = pos; i >= 0; i--) {
		num[i] = 0;
	}
	for (int i = 0; i <= pos - 1; i++) {
		backup[i + 1] += backup[i] / 2;
		backup[i] %= 2;
	}
	for (int i = 0; i <= pos - 1; i++) {
		num[i] = backup[i];
	}
	ans[pos] = 1;
	for (int i = 0; i <= pos - 1; i++) {
		ans[i] = 0;
	}
	
	for (int i = 0; i <= pos - 1; i++) {
		ans[i] -= num[i];
		if (ans[i] < 0) {
			ans[i + 1]--;
			ans[i] += 2;
		}
	}
	
	for (int i = pos; i >= 0; i--) {
		if (ans[i] != 0) {
			for (int j = i; j >= 0; j--) {
				putchar(ans[j] + '0');
			}
			puts("");
			break;
		}
	}
}
void solve() {
	scanf("%d", &n);
	memset(sum, 0, sizeof (sum));
	
	long long tot = 0;
	maxn = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%d%d", &a[i], &x[i]);
		sum[a[i]] += x[i];
		if (a[i] > maxn) maxn = a[i];
		tot += x[i]; 
	}
	
	for (int i = 0; i <= maxn; i++) {
		backup[i] = sum[i];
	}
	
	for (int i = maxn; i >= 0; i--) {
		if (sum[i] % 2 == 0) {
			continue;
		}
		
		long long need = 1;
		for (int j = i - 1; j >= 0; j--) {
			need *= 2;
			if (need > tot) {
				print(i);
				return;
			}
			if (need >= sum[j]) {
				need -= sum[j];
				sum[j] = 0;
			} else {
				sum[j] -= need;
				need = 0;
			}
			if (!need) break;
		}
		if (need) {
			print(i);
			return;
		}
	}
	puts("0");
}

int main() {
	int tests;
	scanf("%d", &tests);
	for (int i = 1; i <= tests; i++) {
		printf("Case #%d: ", i);
		solve();
	}
}
