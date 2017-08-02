#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <algorithm>
#include <iostream>

unsigned long long mod;

class Matrix {
public:
    unsigned long long item[2][2];

    Matrix() {
        memset(item, 0, sizeof(item));
    }

    Matrix(const Matrix &other) {
        *this = other;
    }

    Matrix &operator =(const Matrix &other) {
        if (this == &other) {
            return *this;
        }
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                item[i][j] = other.item[i][j];
            }
        }
        return *this;
    }

    friend bool operator ==(const Matrix &a, const Matrix &b) {
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                if (a.item[i][j] != b.item[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

    friend Matrix operator *(const Matrix &a, const Matrix &b) {
        Matrix c;
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                for (int k = 0; k < 2; ++k) {
                    (c.item[i][j] += a.item[i][k] * b.item[k][j] % mod) %= mod;
                }
            }
        }
        return c;
    }
};

Matrix tran, unit;

Matrix pow(const Matrix &x, const unsigned long long &k) {
    Matrix answer = unit, number = x;
    for (unsigned long long i = k; i > 0; i >>= 1) {
        if (i & 1) {
            answer = answer * number;
        }
        number = number * number;
    }
    return answer;
}

bool test(const unsigned long long &n, const unsigned long long &p) {
    if (n == 0) {
        return false;
    }
    mod = p;
    Matrix answer = pow(tran, n);
    return answer == unit;
}

unsigned long long n;

unsigned long long update(const unsigned long long &bound, const unsigned long long &p) {
    if (!test(bound, p)) {
        return LONG_LONG_MAX;
    }
    unsigned long long answer = bound;
    for (unsigned long long i = 2; i * i <= bound; ++i) {
        if (bound % i == 0) {
            if (test(i, p)) {
                answer = std::min(answer, i);
            }
            if (test(bound / i, p)) {
                answer = std::min(answer, bound / i);
            }
        }
    }
    return answer;
}

unsigned long long period(const unsigned long long &p) {
    if (p < 1000) {
        for (int i = 2;; ++i) {
            if (test(i, p)) {
                return i;
            }
        }
    } else {
        unsigned long long answer = LONG_LONG_MAX;
        answer = std::min(answer, update(p, p));
        answer = std::min(answer, update(p - 1, p));
        answer = std::min(answer, update(p + 1, p));
        answer = std::min(answer, update(p * 2, p));
        answer = std::min(answer, update(p * 2 - 2, p));
        answer = std::min(answer, update(p * 2 + 2, p));
        answer = std::min(answer, update(p * 2 - 1, p));
        answer = std::min(answer, update(p * 2 + 1, p));
        return answer;
    }
}

unsigned long long lcm(const unsigned long long &a, const unsigned long long &b) {
    return a / std::__gcd(a, b) * b;
}

void solve(void) {
    unsigned long long answer = 1;
    for (unsigned long long i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            unsigned long long number = 1;
            for (; n % i == 0; n /= i) {
                number *= i;
            }
            number /= i;
            number *= period(i);
            answer = lcm(answer, number);
        }
    }
    if (n > 1) {
        answer = lcm(answer, period(n));
    }
    if (answer % 2 == 0) {
        answer /= 2;
    }
    std::cout << answer << std::endl;
    //	printf("%lld\n", answer);
}

int main(void) {
    std::ios::sync_with_stdio(false);

    unit.item[0][0] = 1, unit.item[0][1] = 0;
    unit.item[1][0] = 0, unit.item[1][1] = 1;

    tran.item[0][0] = 1, tran.item[0][1] = 1;
    tran.item[1][0] = 1, tran.item[1][1] = 0;

    for (; std::cin >> n; solve());
}
