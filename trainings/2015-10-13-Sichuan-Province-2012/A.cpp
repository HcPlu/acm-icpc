#include <iostream>

using namespace std;
int a[10], used[22][22][22];

void solve() {
    for (int i = 1; i <= 3; i++) {
        scanf("%d", &a[i]);
    }
    sort(a + 1, a + 4);
    memset(used, 0, sizeof(used));
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            for (int k = 1; k <= 3; k++) {
                if (i != j && j != k && i != k) {
                    if (!used[a[i]][a[j]][a[k]]) {
                        printf("%d %d %d\n", a[i], a[j], a[k]);
                        used[a[i]][a[j]][a[k]] = 1;
                    }
                }
            }
        }
    }
}

int main() {
    int tests;
    scanf("%d", &tests);
    for (int i = 1; i <= tests; i++) {
        printf("Case #%d:\n", i);
        solve();
    }
}
