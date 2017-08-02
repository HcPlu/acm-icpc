#include <cstdio>
#include <iostream>

long long calc(const long long &x) {
    return x / 5;
}

long long l, r;

void solve(void) {
    std::cout << calc(r) - calc(l) + 1 << std::endl;
}

int main(void) {
    for (; std::cin >> l >> r && (l || r); solve());
}
