#include <iostream>
#include <cmath>

using namespace std;
const int N = 555;
const double eps = 1e-8;
const double PI = acos(-1.);
const double g = 9.8;

int n;
double height, l1, r1, l2, r2, v[N];

__inline double calc(const double &x, const double &A, const double &B, const double &C) {
    return A * x + B * x * x + C;
}

void solve() {
    scanf("%lf%lf%lf%lf%lf", &height, &l1, &r1, &l2, &r2);
    for (int i = 1; i <= n; i++) {
        scanf("%lf", &v[i]);
    }
    double step = 3e-4;
    double angle = PI / 2 - step;
    int answer = 0;
    for (; angle > -PI / 2; angle -= step) {
        double cosa = cos(angle);
        double sina = sin(angle);
        int flg = 1;
        int counter = 0;
        for (int i = 1; i <= n; i++) {
            double A = sina / cosa;
            double B = -.5 * g / v[i] / v[i] / cosa / cosa;
            double C = height;
            if (calc(l2, A, B, C) > -eps && calc(r2, A, B, C) < eps) {
                flg = 0;
                break;
            }

            if (calc(l1, A, B, C) > -eps && calc(r1, A, B, C) < eps) {
                counter++;
            }
        }
        if (counter == n) {
            answer = n;
            break;
        }
        if (flg) {
            answer = max(answer, counter);
        }
    }
    printf("%d\n", answer);
}

int main() {
    for (; scanf("%d", &n) && n; solve());
    return 0;
}
