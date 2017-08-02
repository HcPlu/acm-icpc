#include <iostream>

using namespace std;
const int mod = 258280327;
const int N = 1e6 + 11;
const int N = 1e6;
long long F[N], G[N], T[N], S[N];
int prime[N];

void solve() {
    int n;
    scanf("%d", &n);
    printf("%d\n", (int)S[n]);
}

void init() {
    for (int i = 1; i <= N; i++) {
        prime[i] = 1;
        T[i] = 1;
    }
    for (int i = 2; i <= N; i++) {
        if (prime[i]) {
            T[i] *= 2;
            T[i] %= mod;
            for (int j = i + i; j <= N; j += i) {
                prime[j] = 0;
                T[j] *= 2;
                T[j] %= mod;
            }
        }
    }
    for (int g = 1; g <= N; g++) {
        for (int i = g; i <= N; i += g) {
            G[i] += T[i / g - 1];

        }
    }
    F[1] = S[1] = 1;
    for (int i = 2; i <= N; i++) {
        F[i] = F[i - 1] + 2 * i - 1 - G[i - 1];
        F[i] %= mod;
        S[i] = S[i - 1] + F[i];
        S[i] %= mod;
    }
}

int main() {
    init();
    int tests;
    scanf("%d", &tests);
    for (int i = 1; i <= tests; i++) {
        solve();
    }
}
