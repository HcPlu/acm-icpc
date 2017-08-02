#include <iostream>

using namespace std;
const int mod = 2015;
int n, m, g[55][55], origin[55], answer[55];

class Matrix {
public:
    int a[55][55];

    Matrix() {
        memset(a, 0, sizeof(a));
    }

    Matrix operator *(const Matrix &b) {
        Matrix c;
        for (int k = 1; k <= n + 1; k++)
            for (int i = 1; i <= n + 1; i++)
                for (int j = 1; j <= n + 1; j++) {
                    c.a[i][j] += a[i][k] * b.a[k][j];
                    c.a[i][j] %= mod;
                }
        return c;
    }

    void print() {
        for (int i = 1; i <= n + 1; i++, puts(""))
            for (int j = 1; j <= n + 1; j++) {
                printf("%d ", a[i][j]);
            }
    }

};

void solve() {
    scanf("%d%d", &n, &m);

    memset(g, 0, sizeof g);

    for (int i = 1; i <= n; i++) {
        int num;
        scanf("%d", &num);
        for (int j = 1; j <= num; j++) {
            int x;
            scanf("%d", &x);
            g[i][x] = 1;
        }
    }

    if (m == 1) {
        printf("%d\n", n + 1);
        return;
    }

    for (int i = 1; i <= n; i++) {
        origin[i] = 1;
    }

    origin[n + 1] = 1;

    Matrix matrix;
    for (int i = 1; i <= n + 1; i++) {
        for (int j = 1; j <= n; j++) {
            matrix.a[i][j] = g[i][j];
        }
        matrix.a[i][n + 1] = 1;
    }

    Matrix target = matrix;
    for (long long i = m - 1; i > 0; i >>= 1) {
        if (i & 1) {
            target = target * matrix;
        }
        matrix = matrix * matrix;
    }

    for (int i = 1; i <= n + 1; i++)
        answer[i] = 0;

    for (int i = 1; i <= n + 1; i++) {
        for (int j = 1; j <= n + 1; j++) {
            answer[j] += target.a[i][j] * origin[i];
            answer[j] %= mod;
        }
    }

    printf("%d\n", answer[n + 1]);
}

int main() {
    int tests = 0;
    scanf("%d", &tests);
    for (int i = 1; i <= tests; i++) {
        solve();
    }
}
