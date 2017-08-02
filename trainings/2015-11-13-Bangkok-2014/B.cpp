#include <cstdio>

const int N = 51;

long long l, r;
int bit[N];
unsigned long long count[N];
unsigned long long comb[N][N];

unsigned long long solve(const long long &n) {
    if (n < 0) {
        return 0;
    }

    int bits = 0;
    for (long long i = n; i > 0; i >>= 1) {
        bit[bits++] = (i & 1);
    }

    for (int i = 0; i <= bits; ++i) {
        count[i] = 0;
    }

    for (int i = 0; i < bits; ++i) {
        if (~n >> i & 1) {
            continue;
        }

        int total = 0;
        for (int j = i + 1; j < bits; ++j) {
            total += bit[j];
        }

        for (int j = 0; j <= i && total + j <= bits; ++j) {
            count[total + j] += comb[i][j];
        }
    }

    unsigned long long answer = 1LL << (__builtin_popcountll(n));
    for (int i = 0; i <= bits; ++i) {
        answer += (1LL << i) * count[i];
    }

    return answer;
}

void solve(void) {
    printf("%llu\n", solve(r) - solve(l - 1));
}

int main(void) {
    comb[0][0] = 1;
    for (int i = 1; i < N; ++i) {
        comb[i][0] = comb[i][i] = 1;
        for (int j = 1; j < i; ++j) {
            comb[i][j] = comb[i - 1][j] + comb[i - 1][j - 1];
        }
    }

    for (; ~scanf("%lld%lld", &l, &r) && (l || r); solve()) {
    }
}
