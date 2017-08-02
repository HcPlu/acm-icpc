#include <cstdio>
#include <cstring>

const int N = 1e6 + 10;

char a[N], b[N];

void solve(void) {
    scanf("%s%s", a + 1, b + 1);

    int lena = (int)strlen(a + 1);
    int lenb = (int)strlen(b + 1);

    if (lena == lenb) {
        for (int i = 1; i <= lena; ++i) {
            if (a[i] != b[i]) {
                puts("No");
                return;
            }
        }
        puts("Yes");
        return;
    }

    int pos = 1;
    for (int i = 1; i <= lenb; ++i) {
        if (b[i] == b[1]) {
            pos = i;
        } else {
            break;
        }
    }

    for (int i = 1; i <= pos; ++i) {
        if (a[i] != b[1]) {
            puts("No");
            return;
        }
    }

    for (int i = 1, j = 0; i <= lena; ++i) {
        for (j++; j <= lenb && a[i] != b[j]; ++j) {
        }
        if (j > lenb) {
            puts("No");
            return;
        }
    }
    puts("Yes");
}

int main(void) {
    int tests;
    for (scanf("%d", &tests); tests--; solve()) {
    }
}
