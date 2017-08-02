#include <cstring>
#include <cstdio>
#include <iostream>

using namespace std;
const int N(111111);
int fac[N], inv[N], invFac[N];

long long getLL() {
    long long x(0);
    char c;
    c = getchar();
    while (c < '0' || c > '9') {
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - 48);
        c = getchar();
    }
    return x;
}

int main() {
    int tests;
    tests = getLL();
    for (int qq(1); qq <= tests; qq++) {
        long long n, m, k;
        n = getLL();
        m = getLL();
        k = getLL();
        long long ans(0), mul(1);
        for (int i(0); i < k; i++) {
            int p;
            p = getLL();

            fac[0] = fac[1] = 1;
            inv[0] = inv[1] = 1;
            invFac[0] = invFac[1] = 1;
            for (int i(2); i < p; i++) {
                fac[i] = (long long)fac[i - 1] * i % p;
                inv[i] = (long long)inv[i - p % i] * ((p + i - 1) / i) % p;
                invFac[i] = (long long)invFac[i - 1] * inv[i] % p;
            }
            int tmp(1), x(n), y(m);
            while (y) {
                int xx(x % p), yy(y % p);
                if (xx < yy) {
                    tmp = 0;
                    break;
                } else {
                    tmp = (long long)tmp * fac[xx] % p * invFac[yy] % p * invFac[xx - yy] % p;
                }
                x /= p;
                y /= p;
            }
            while (ans % p != tmp) {
                ans = ans + mul;
            }
            mul *= p;
        }
        cout << ans << endl;
    }
}
