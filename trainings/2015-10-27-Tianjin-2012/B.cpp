#include <iostream>
#include <vector>

using namespace std;
int n, m;

int calc(int x, int y) {
    int ret = 0;
    while (x > 0) {
        ret += (x % y) * (x % y);
        x /= y;
    }
    return ret;
}

void solve() {
    long long ans = 0;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            ans += calc(i, m);
            if (i * i != n) {
                ans += calc(n / i, m);
            }
        }
    }
    char digit[111];
    for (int i = 0; i < 10; i++) {
        digit[i] = i + '0';
    }
    for (int i = 10; i < 16; i++) {
        digit[i] = i - 10 + 'A';
    }
    vector<int> vec;
    while (ans) {
        vec.push_back(ans % m);
        ans /= m;
    }

    for (int i = (int)vec.size() - 1; i >= 0; i--) {
        putchar(digit[vec[i]]);
    }
    puts("");
}

int main() {
    for (; scanf("%d%d", &n, &m) == 2; solve()) {
    }
    return 0;
}
