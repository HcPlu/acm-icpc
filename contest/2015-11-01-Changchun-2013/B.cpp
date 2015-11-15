#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
int answer[222];
int n;
void solve() {
	int pos = 100;
	for (int i = 0; i <= 200; i++) {
		answer[i] = 0;
	}
	
	answer[pos] = n;
	for (; ;) {
		int flg = 0;
		for (int i = 1; i <= 198; i++) {
			if (answer[i] >= 2) {
				int add = answer[i] / 2;
				answer[i] %= 2;
				answer[i - 1] += add;
				answer[i + 2] += add;
				flg = 1;
			}
		}
		for (int i = 1; i <= 199; i++) {
			if (answer[i] >= 1 && answer[i + 1] >= 1) {
				int minx = min(answer[i], answer[i + 1]);
				answer[i - 1] += minx;
				answer[i] -= minx;
				answer[i + 1] -= minx;
				flg = 1;
			}
		}
		if (!flg) {
			break;
		}
	}
	
	int first = -1, last = -1;
	for (int i = 0; i <= 200; i++) {
		if (answer[i] != 0) {
			if (first == -1) {
				first = i;
			}
			last = i;
		}
	}
	for (int i = first; i <= last; i++) {
		if (i == pos + 1) {
			putchar('.');
		}
		printf("%d", answer[i]);
		
	}
	puts("");
}


int main() {
	for (; scanf("%d", &n) == 1; solve());
}
