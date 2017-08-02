#include <iostream>

using namespace std;

const int mod = 1e9 + 7;

const int N = 1e6 + 11;

int prime[N + 10];
long long f[N + 10], ok[N + 10];

void init() {
    for (int i = 2; i <= N; i++) {
        prime[i] = 1;
        ok[i] = 0;
    }
    for (int i = 2; i <= N; i++) {
        if (prime[i]) {
            for (int j = i + i; j <= N; j += i) {
                prime[j] = 0;
            }
            for (long long j = i; j <= N; j *= i) {
                ok[j] = i;
            }
        }
    }

    f[1] = 1;
    for (int i = 2; i <= N; i++) {
        f[i] = f[i - 1];
        if (ok[i]) {
            f[i] = f[i] * ok[i] % mod;
        }
    }
}

long long power(const long long &x, const long long &k) {
    long long answer = 1, number = x;
    for (long long i = k; i > 0; i >>= 1) {
        if (i & 1) {
            (answer *= number) %= mod;
        }
        (number *= number) %= mod;
    }
    return answer;
}

int n;

void solve() {
    scanf("%d", &n);
    int ans = 1LL * f[n + 1] * power(n + 1, mod - 2) % mod;
    printf("%d\n", ans);
}

int main() {
    int tests;
    scanf("%d", &tests);
    init();
    for (int i = 1; i <= tests; i++) {
        solve();
    }
    return 0;
}
