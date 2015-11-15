#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;
char text[1111111];
int main() {
	int tests;
	scanf("%d", &tests);
	for (int i = 1; i <= tests; i++) {
		int n, m;
		scanf("%d%d", &n, &m);
		scanf("%s", text + 1);
		int counter = 0;
		for (int j = 1; j <= n; j++, puts("")) {
			for (int k = 1; k <= m; k++) {
				putchar(text[++counter]);
			}
		}
	}
}
