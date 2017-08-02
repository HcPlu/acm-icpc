#include <iostream>

using namespace std;
const double eps = 1e-9;
double f[44][41111];
int score[44];

void solve() {
    int n;
    double p;
    scanf("%d%lf", &n, &p);

    int sum = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &score[i]);
        sum += score[i];
    }
    f[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= sum; j++) {
            f[i][j] = 0;
        }
        for (int j = 0; j < score[i]; j++) {
            f[i][j] += f[i - 1][j] * 0.5;
        }
        for (int j = score[i]; j <= sum; j++) {
            f[i][j] += f[i - 1][j] * 0.5;
            f[i][j] += f[i - 1][j - score[i]] * 0.5;
        }
    }

    double prob = 0;
    for (int j = 0; j <= sum; j++) {
        prob += f[n][j];
        if (prob > p - eps) {
            printf("%d\n", j);
            return;
        }
    }
}

int main() {
    int tests;
    scanf("%d", &tests);
    for (int i = 1; i <= tests; i++) {
        solve();
    }
    return 0;
}
