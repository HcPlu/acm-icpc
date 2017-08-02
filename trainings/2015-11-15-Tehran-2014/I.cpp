#include <cstdio>
#include <cmath>
#include <iostream>

using namespace std;

const int N = 10005;

int n;
int x[N], y[N];

void work() {
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &x[i], &y[i]);
    }
    bool flag = true;
    for (int i = n; i >= 2; i--) {
        int nowx = x[i] - x[i - 1];
        int nowy = y[i] - y[i - 1];
        swap(nowx, nowy);
        nowx *= -1;
        for (int j = n; j > i; j--) {
            int ux = x[j] - x[i];
            int uy = y[j] - y[i];
            if (1LL * ux * nowy - uy * nowx < 0) {
                flag = false;
                break;
            }
        }
        if (!flag) {
            break;
        }
    }
    if (!flag) {
        puts("Unfair");
    } else {
        puts("Fair");
    }
}

int main() {
    while (scanf("%d", &n) == 1 && n) {
        work();
    }
    return 0;
}
