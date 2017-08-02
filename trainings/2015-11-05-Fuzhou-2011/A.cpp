#include <iostream>


using namespace std;
const int dx[4] = {0, 0, -1, 1};
const int dy[4] = {1, -1, 0, 0};

const int hdx[8] = {-2, -2, -1, 1, 2, 2, 1, -1};
const int hdy[8] = {-1, 1, 2, 2, 1, -1, -2, -2};

int type[1111];
int n, gx, gy;

pair<int, pair<int, int> > chess[111];

int board[22][22];

int check(int a, int b, int c) {
    if (b > c) {
        return a < b && a > c;
    }
    if (b < c) {
        return a > b && a < c;
    }
}

int cango(int x, int y, int dir) {
    if (dir == 0) {
        x--;
        if (board[x][y]) {
            return 0;
        }
    }
    if (dir == 1) {
        x--;
        if (board[x][y]) {
            return 0;
        }
    }
    if (dir == 2) {
        y++;
        if (board[x][y]) {
            return 0;
        }
    }
    if (dir == 3) {
        y++;
        if (board[x][y]) {
            return 0;
        }
    }
    if (dir == 4) {
        x++;
        if (board[x][y]) {
            return 0;
        }
    }
    if (dir == 5) {
        x++;
        if (board[x][y]) {
            return 0;
        }
    }
    if (dir == 6) {
        y--;
        if (board[x][y]) {
            return 0;
        }
    }
    if (dir == 7) {
        y--;
        if (board[x][y]) {
            return 0;
        }
    }
    return 1;
}

void solve() {
    type['G'] = 1;
    type['R'] = 2;
    type['C'] = 3;
    type['H'] = 4;
    memset(board, 0, sizeof board);
    for (int i = 1; i <= n; i++) {
        static char text[5];
        int x, y;
        scanf("%s%d%d", text, &x, &y);
        chess[i] = make_pair(type[text[0]], make_pair(x, y));
        board[x][y] = type[text[0]];
    }

    for (int i = gx; i <= 10; i++) {
        if (board[i][gy] == 1) {
            puts("NO");
            return;
        } else {
            if (board[i][gy] != 0) {
                break;
            }
        }
    }

    for (int dir = 0; dir < 4; dir++) {
        int nx = gx + dx[dir];
        int ny = gy + dy[dir];
        int capture = 0;
        if (nx < 1 || nx > 3 || ny < 4 || ny > 6) {
            continue;
        }
        for (int i = 1; i <= n; i++) {
            int id = chess[i].first;
            int x = chess[i].second.first;
            int y = chess[i].second.second;
            if (x == nx && y == ny) {
                continue;
            }
            if (id == 1) {
                if (ny == y) {
                    int flg = 1;
                    for (int i = 1; i <= n; i++) {
                        if (chess[i].second.second == y && check(chess[i].second.first, x, nx)) {
                            flg = 0;
                            break;
                        }
                    }
                    if (flg) {
                        capture = 1;
                        break;
                    }
                }
            }

            if (id == 2) {
                if (ny == y) {
                    int flg = 1;
                    for (int i = 1; i <= n; i++) {
                        if (chess[i].second.second == y && check(chess[i].second.first, x, nx)) {
                            flg = 0;
                            break;
                        }
                    }
                    if (flg) {
                        capture = 1;
                        break;
                    }
                }
                if (nx == x) {
                    int flg = 1;
                    for (int i = 1; i <= n; i++) {
                        if (chess[i].second.first == x && check(chess[i].second.second, y, ny)) {
                            flg = 0;
                            break;
                        }
                    }
                    if (flg) {
                        capture = 1;
                        break;
                    }
                }
            }

            if (id == 3) {
                int flg = 1;
                if (nx == x) {
                    int number = 0;
                    for (int i = 1; i <= n; i++) {
                        if (chess[i].second.first == x && check(chess[i].second.second, y, ny)) {
                            number++;
                        }
                    }
                    if (number == 1) {
                        capture = 1;
                        break;
                    }
                }
                if (ny == y) {
                    int number = 0;
                    for (int i = 1; i <= n; i++) {
                        if (chess[i].second.second == y && check(chess[i].second.first, x, nx)) {
                            number++;
                        }
                    }
                    if (number == 1) {
                        capture = 1;
                        break;
                    }
                }
            }

            if (id == 4) {
                int flg = 0;
                for (int j = 0; j < 8; j++) {
                    int tx = x + hdx[j];
                    int ty = y + hdy[j];
                    if (cango(x, y, j) && tx == nx && ty == ny) {
                        flg = 1;
                    }
                }
                if (flg) {
                    capture = 1;
                    break;
                }
            }
        }

        if (!capture) {
            puts("NO");
            return;
        }
    }

    puts("YES");
}

int main() {
    for (; scanf("%d%d%d", &n, &gx, &gy) && (n || gx || gy); solve()) {
    }
    return 0;
}
