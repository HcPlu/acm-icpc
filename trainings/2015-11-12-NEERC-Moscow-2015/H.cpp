#include <iostream>

using namespace std;
const int N = 111111;
long long f[N][333];

int n;
int a[N];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%X", &a[i]);
    }

    f[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < min(i, 260); j++) {
            if (j == 0) {
                f[i][j] = f[i - 1][j] + (a[i] ^ (i - 1));
            } else {
                f[i][j] = max(f[i - 1][j - 1], f[i - 1][j] + ((i - j - 1) ^ a[i]));
            }
        }
        f[i][i] = 0;
    }

    long long answer = 0;
    for (int i = 0; i <= 260; i++) {
        answer = max(answer, f[n][i]);
    }

    cout << answer << endl;
}
