#include <cstdio>

double x, y, p, q;

void solve(void) {
    scanf("%lf%lf%lf%lf", &x, &y, &p, &q);

    double result1 = q * (p * x + p * y) + (1 - q) * x;
    double result2 = q * y + (1 - q) * (p * x + p * y);

    if (result1 > result2) {
        printf("tiger %.4f\n", result1);
    } else {
        printf("wolf %.4f\n", result2);
    }
}

int main(void) {
    int tests;
    for (scanf("%d", &tests); tests--; solve());
}
