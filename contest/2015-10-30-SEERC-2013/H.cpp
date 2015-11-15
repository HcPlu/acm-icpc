#include <cstdio>

int main(void) {
	for (int n; ~scanf("%d", &n); ) {
		long long nn = n;
		if ((nn * nn) % 3 == 1) {
			puts("1");
		} else {
			puts("0");
		}
	}
}
