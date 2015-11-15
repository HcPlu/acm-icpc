#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
using namespace std;

string ans[99];

void solve() {
	int n, m;
	scanf("%d%d", &m, &n);
	if (m == 1) {
		for (int i = 0; i < n; i++) {
			putchar('a');
		}
		puts("");
		return;
	}
	
	if (m >= 3) {
		for (int i = 0; i < n; i++) {
			putchar('a' + i % 3);
		}
		puts("");
		return;
	}
	ans[1] = "a";
	ans[2] = "ab";
	ans[3] = "aab";
	ans[4] = "aabb";
	ans[5] = "aaaba";
	ans[6] = "aaabab";
	ans[7] = "aaababb";
	ans[8] = "aaababbb";
	ans[9] = "aaaababba";
	ans[10] = "aaaababbaa";
	if (n <= 10) {
		puts(ans[n].c_str());
		return;
	}
	printf("aa");
	int rest = n - 2;
	for (int i = 1; i <= rest / 6; i++) {
		printf("aababb");
	}
	rest = rest % 6;
	if (rest <= 4) {
		for (int i = 1; i <= rest; i++) {
			putchar('a');
		}
		puts("");
	} else {
		if (rest == 5) {
			printf("aabab");
		}
		puts("");
	}
}
int main() {
	int tests;
	scanf("%d", &tests);
	for (int i = 1; i <= tests; i++) {
		printf("Case #%d: ", i);
		solve();
	}
	return 0;
}
