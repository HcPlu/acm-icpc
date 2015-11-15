#include <cstdio>
#include <algorithm>

const long long mod = 1e9 + 7;

const int N = 1e5 + 100;
const int M = 12;
const int K = 111;

long long fact[N + 1], inverse[N + 1];

int n, m, k;
int c[M], sum[M];
long long ways[M][K];

long long pow(const long long &x, const long long &k) {
	long long answer = 1, number = x;
	for (long long i = k; i > 0; i >>= 1) {
		if (i & 1) {
			(answer *= number) %= mod;
		}
		(number *= number) %= mod;
	}
	return answer;
}

long long comb(int n, int k) {
	if (n < 0 || k < 0 || k > n) {
		return 0;
	}
	return fact[n] * inverse[k] % mod * inverse[n - k] % mod;
}

void solve(void) {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= m; ++i) {
		scanf("%d", c + i);
	}

	sum[m + 1] = 0;
	for (int i = m; i >= 1; --i) {
		sum[i] = sum[i + 1] + c[i];
	}

	for (int i = 0; i <= m; ++i) {
		for (int j = 0; j <= k; ++j) {
			ways[i][j] = 0;
		}
	}
	ways[0][k] = 1;

	for (int i = 0; i < m; ++i) {
		for (int j = 0; j <= k; ++j) {
			for (int a = 0; a <= j; ++a) {
				for (int b = 0; a + b <= j; ++b) {
					long long number = 1;
					number = number * comb(j, a) % mod;
					number = number * comb(j - a, b) % mod;
					number = number * comb(sum[i + 1] - j * 2, c[i + 1] - a - b * 2) % mod;
					(ways[i + 1][j - a - b] += ways[i][j] * number % mod) %= mod;
				}
			}
		}
	}
	
	printf("%d\n", (int)ways[m][0]);
}

int main(void) {
	fact[0] = 1;
	for (int i = 1; i <= N; ++i) {
		fact[i] = fact[i - 1] * i % mod;
	}
	for (int i = 0; i <= N; ++i) {
		inverse[i] = pow(fact[i], mod - 2);
	}
	
	int tests;
	scanf("%d", &tests);
	for (int i = 1; i <= tests; ++i) {
		printf("Case #%d: ", i);
		solve();
	}
}
