#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <fstream>

using namespace std;

const int N = 10001;

int n, m;
int item[N][N];

int main(void) {
    fread(&n, sizeof(n), 1, stdin);
    fread(&m, sizeof(m), 1, stdin);
    for (int i = 0; i < n; ++i) {
        fread(item[i], sizeof(int), m, stdin);
    }
    for (int l, r; fread(&l, sizeof(l), 1, stdin) && fread(&r, sizeof(r), 1, stdin);) {
        int answer = 0;
        for (int i = 0, j = m, a, b; i < n && item[i][0] <= r; ++i, j = b) {
            a = std::lower_bound(item[i], item[i] + j, l) - item[i];
            b = std::upper_bound(item[i], item[i] + j, r) - item[i];
            answer += b - a;
        }
        printf("%d\n", answer);
    }
}
