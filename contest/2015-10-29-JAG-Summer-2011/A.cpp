#include <cstdio>
#include <algorithm>

const int N = 1111;

int n, m;
double x[N], y[N], z[N];

double sqr(const double &x) {
	return x * x;
}

int main(void) {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++i) {
		scanf("%lf%lf%lf", x + i, y + i, z + i);
	}
	
	double answer = 0;
	for (int mask = 0; mask < (1 << n); ++mask) {
		if (__builtin_popcount(mask) != m) {
			continue;
		}
		double number = 0;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if ((mask >> i & 1) && (mask >> j & 1)) {
					number += sqr(x[i] - x[j]) + sqr(y[i] - y[j]) + sqr(z[i] - z[j]);
				}
			}
		}
		answer = std::max(answer, number);
	}
	printf("%.10f\n", answer / 2);
}
