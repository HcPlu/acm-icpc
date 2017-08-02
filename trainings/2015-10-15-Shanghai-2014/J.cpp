#include <cstdio>
#include <algorithm>

long long n, m, a, b, c;

long long solve(const long long &n, const long long &m, const long long &a, const long long &b, const long long &c) {
    long long answer = 0;
    answer += (n - m - 1) * std::max(a, b);
    answer += (m / 2) * std::max(a + c, b * 2);
    if (m & 1) {
        answer += std::max(b, c);
    }
    return answer;
}

void solve(void) {
    scanf("%lld%lld%lld%lld%lld", &n, &m, &a, &b, &c);
    printf("%lld %lld\n", solve(n, m, a, b, c), -solve(n, n - m, -c, -b, -a));
}

int main(void) {
    int tests;
    scanf("%d", &tests);
    for (int i = 1; i <= tests; ++i) {
        printf("Case #%d: ", i);
        solve();
    }
}
