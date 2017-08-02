#include <iostream>

using namespace std;

char bh[150];

int main() {
    int n;
    int test = 0;
    while (scanf("%d", &n) == 1) {
        test++;
        if (test != 1) {
            puts("");
        }
        printf("2 %d %d\n", n, n);
        for (int i = 1; i <= 26; i++) {
            bh[i] = i + 'a' - 1;
        }
        for (int i = 27; i <= 52; i++) {
            bh[i] = i - 27 + 'A';
        }
        for (int i = 1; i <= n; i++, puts("")) {
            for (int j = 1; j <= n; j++) {
                printf("%c", bh[i]);
            }
        }
        puts("");
        for (int i = 1; i <= n; i++, puts("")) {
            for (int j = 1; j <= n; j++) {
                printf("%c", bh[j]);
            }
        }
    }
    return 0;
}
