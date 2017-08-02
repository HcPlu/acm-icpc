#include <cstdio>
#include <cmath>

using namespace std;
int n;
char text[111];

void solve(void) {
    scanf("%d%s", &n, text);
    double base;
    if (text[0] == 'b') {
        base = 2;
    }
    if (text[0] == 'n') {
        base = -1;
    }
    if (text[0] == 'd') {
        base = 10;
    }
    double answer = 0;
    for (int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);
        if (x == 0)
            continue;
        if (x > 0) {
            if (base > 0) {
                answer -= x * 1. / 100 * log(x * 1. / 100) / log(base);
            } else {
                answer -= x * 1. / 100 * log(x * 1. / 100);
            }
        }
    }
    printf("%.10f\n", answer);
}

int main(void) {
    int tests;
    for (scanf("%d\n", &tests); tests--; solve());
}
