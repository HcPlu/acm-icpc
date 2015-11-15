#include <cstdio>
#include <algorithm>
#include <iostream>

const long long mod = 1e9 + 7;

const int N = 1111111;

int bit, n, k;
int a[N];
long long fact[N], inverse[N];

__inline long long sqr(const long long &x) {
    return x * x % mod;
}

__inline void update(long long &x, const long long &y) {
    (x += y % mod) %= mod;
}

__inline long long pow(const long long &x, const long long &k) {
    long long answer = 1, number = x;
    for (long long i = k; i > 0; i >>= 1) {
        if (i & 1) {
            (answer *= number) %= mod;
        }
        (number *= number) %= mod;
    }
    return answer;
}

__inline long long choose(int n, int k) {
    if (n < 0 || k < 0 || n - k < 0) {
        return 0;
    } else {
        return fact[n] * inverse[k] % mod * inverse[n - k] % mod;
    }
}

int main(void) {
    scanf("%d", &bit);
    n = 1 << bit;
    for (int i = 0; i < n; ++i) {
        scanf("%d", a + i);
    }
    
    std::reverse(a, a + n);
    
    fact[0] = inverse[0] = 1;
    for (int i = 1; i <= n; ++i) {
        fact[i] = fact[i - 1] * i % mod;
        inverse[i] = inverse[i - 1] * pow(i, mod - 2) % mod;
    }
    
    long long answer = 0;
    for (int k = 1, base = n; k < n; k <<= 1, base >>= 1) {
        long long number = 0, coefficient = 0;
        for (int i = 0; i < n; ++i) {
            update(number, coefficient * choose(i - k, k - 1) % mod * a[i] % mod);
            update(coefficient, choose(i, k - 1) * a[i] % mod);
        }
        (number *= base) %= mod;
        update(answer, number * sqr(fact[k]) % mod * fact[n - k - k] % mod);
    }
    
    std::cout << answer * inverse[n] % mod << std::endl;
}
