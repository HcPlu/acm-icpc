#include <iostream>
#include <cmath>

using namespace std;
const long double eps = 1e-9;

long double mysqrt(long double x) {
    return sqrt(max(x, (long double)0));
}

int main() {
    double x, y;
    scanf("%lf%lf", &x, &y);
    long double h1, t1;
    h1 = x, t1 = y;
    scanf("%lf%lf", &x, &y);
    long double h2, t2;
    h2 = x, t2 = y;

    long double A = (h2 - h1);
    long double B = -(2 * t1 * h2 - 2 * t2 * h1);
    long double C = h2 * t1 * t1 - h1 * t2 * t2;
    long double delta = (B * B - 4 * A * C);
    long double x1 = (-B + mysqrt(delta)) / (2 * A);
    long double x2 = (-B - mysqrt(delta)) / (2 * A);
    if (x1 > -eps && x1 < min(t1, t2) + eps) {
        printf("%.7f\n", (double)max(x1, eps));
    } else {
        printf("%.7f\n", (double)max(x2, eps));
    }
}
