#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;
const double eps = 1e-8;
int n, m;
int main() {
    scanf("%d%d", &n, &m);
    if (n < m) {
        swap(n, m);
    }
    double x1 = n * 1. / 2.;
    double x2 = m * 1. / 2.;
    double answer = min(x1, x2);
    
    double t1 = n * 1. / 3;
    if (t1 < m + eps) {
        answer = max(answer, t1);
    } else {
        answer = max(m * 1., answer);
    }
    
    printf("%.3f\n", answer);
}
