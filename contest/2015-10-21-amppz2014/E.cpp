#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

void solve() {
	int p, q, n;
	scanf("%d%d%d", &p, &q, &n);
	int g = __gcd(p, q);
	if (n % g) {
		puts("R");
		return;
	}
	p /= g;
	q /= g;
	n /= g;
	if (p == q) {
		puts("E");
	} else if (p > q) {
		if (n < p) {
			puts("P");
		} else {
			if (n % p < q && ((n % p) % (p - q) == 0)) {
				puts("E");
			} else {
				puts("P");
			}
		}
	} else {
		if (n >= p) {
			puts("E");
		} else {
			if (n + p < q) {
				puts("E");
			} else {
				if ((n + p) % q < p && (((n + p) % q) % (q - p) == 0)) {
					puts("P");
				} else {
					puts("E");
				}
			}
		}
	}
}
int main() {
	int tests;
	scanf("%d", &tests);
	for (int i = 1; i <= tests; i++) {
		solve();
	}
}
