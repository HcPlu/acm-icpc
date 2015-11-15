#include <cstdio>

const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};

const int N = 555;

int n, m;
int item[N][N];

int main(void) {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf("%d", item[i] + j);
        }
    }
    int answer = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int k = 0; k < 4; ++k) {
                bool win = true;
                
                int x = i + dx[k], y = j + dy[k];
                while (x >= 0 && x < n && y >= 0 && y < m) {
                    if (item[x][y] >= item[i][j]) {
                        win = false;
                        break;
                    }
                    x += dx[k];
                    y += dy[k];
                }
                
                answer += win;
            }
        }
    }
    printf("%d\n", answer);
}
