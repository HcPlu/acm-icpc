#include <iostream>

using namespace std;

const int change[6][24] = {{0, 1,  2,  3,  4, 5,  6,  7,  8,  9,  21, 20, 10, 11, 12, 13, 18, 16, 19, 17, 15, 14, 22, 23},
                           {0, 1,  2,  3,  4, 5,  6,  7,  8,  9,  12, 13, 14, 15, 21, 20, 17, 19, 16, 18, 11, 10, 22, 23},
                           {0, 1,  11, 5,  4, 16, 12, 6,  2,  9,  10, 17, 13, 7,  3,  15, 14, 8,  18, 19, 20, 21, 22, 23},
                           {0, 1,  8,  14, 4, 3,  7,  13, 17, 9,  10, 2,  6,  12, 16, 15, 5,  11, 18, 19, 20, 21, 22, 23},
                           {0, 7,  2,  13, 4, 5,  6,  17, 14, 8,  10, 11, 12, 19, 15, 9,  16, 21, 18, 23, 20, 1,  22, 3},
                           {0, 21, 2,  23, 4, 5,  6,  1,  9,  15, 10, 11, 12, 3,  8,  14, 16, 7,  18, 13, 20, 17, 22, 19},};

const int face[6][4] = {{0,  1,  2,  3},
                        {4,  5,  10, 11},
                        {6,  7,  12, 13},
                        {8,  9,  14, 15},
                        {16, 17, 18, 19},
                        {20, 21, 22, 23}};

int n, number[24], col[24], answer;

void check() {
    int ret = 6;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 3; j++) {
            if (col[number[face[i][j]]] != col[number[face[i][j + 1]]]) {
                ret--;
                break;
            }
        }
    }
    answer = max(ret, answer);
}

void dfs(int dep) {
    check();
    if (dep > n) {
        return;
    } else {
        int backup[24];
        for (int i = 0; i < 24; i++) {
            backup[i] = number[i];
        }
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 24; j++) {
                number[j] = backup[change[i][j]];
            }
            dfs(dep + 1);
        }
        for (int i = 0; i < 24; i++) {
            number[i] = backup[i];
        }
    }
}

void solve() {
    for (int i = 0; i < 24; i++) {
        scanf("%d", &col[i]);
    }

    for (int i = 0; i < 24; i++) {
        number[i] = i;
    }

    answer = 0;
    dfs(1);
    printf("%d\n", answer);
}

int main() {
    for (; scanf("%d", &n) == 1; solve()) {
    }
    return 0;
}
