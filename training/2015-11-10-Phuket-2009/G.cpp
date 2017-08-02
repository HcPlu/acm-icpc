#include <iostream>
#include <vector>

using namespace std;

const int INF = 1 << 29;
const int dx[6] = {0, 1, 1, 0, -1, -1};
const int dy[6] = {1, 1, 0, -1, -1, 0};

vector<pair<int, int> > adj[222][6];
pair<int, int> pos[11], target[11], ntarget[11];
int bad[22][22], direction[6], order[6], px[6], py[6], dist[10][222][6];

int getpos(int x, int y) {
    return (x - 1) * 13 + y;
}

pair<int, int> calc(int x1, int y1, int x2, int y2) {
    for (int dir = 0; dir < 6; dir++) {
        if (x2 == x1 + dx[dir] && y2 == y1 + dy[dir]) {
            return make_pair(getpos(x1, y1), dir);
            break;
        }
    }
}

void add(int x, int dirx, int y, int diry) {
    adj[x][dirx].push_back(make_pair(y, diry));
}

void spfa(int number) {
    pair<int, int> source = pos[number];
    vector<pair<int, int> > queue;
    queue.push_back(source);
    dist[number][source.first][source.second] = 0;
    for (int head = 0; head < (int)queue.size(); head++) {
        pair<int, int> now = queue[head];
        int x = now.first;
        int dir = now.second;
        int nowdist = dist[number][x][dir];
        for (int i = 0; i < (int)adj[x][dir].size(); i++) {
            pair<int, int> to = adj[x][dir][i];
            if (dist[number][to.first][to.second] == -1) {
                dist[number][to.first][to.second] = dist[number][x][dir] + 1;
                queue.push_back(to);
            }
        }
    }
}

int check(int x, int y) {
    if (x >= 1 && x <= 13 && y >= 1 && y <= 13 && !bad[x][y]) {
        return 1;
    }
    return 0;
}

int n, m;

void solve() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        x1 += 7;
        x2 += 7;
        y1 += 7;
        y2 += 7;
        pos[i] = calc(x1, y1, x2, y2);
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= 13 * 13; j++) {
            for (int dir = 0; dir < 6; dir++) {
                dist[i][j][dir] = -1;
            }
        }
    }
    scanf("%d", &m);
    memset(bad, 0, sizeof bad);

    for (int i = 1; i <= m; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        x += 7;
        y += 7;
        bad[x][y] = 1;
    }
    if (n < 6) {
        puts("impossible");
        return;
    }

    for (int i = 1; i <= 13 * 13; i++) {
        for (int dir = 0; dir < 6; dir++) {
            adj[i][dir].clear();
        }
    }

    for (int i = 1; i <= 13; i++) {
        for (int j = 1; j <= 13; j++) {
            for (int dir = 0; dir < 6; dir++) {
                int x = i + dx[dir];
                int y = j + dy[dir];
                if (check(x, y)) {
                    //add(getpos(i, j), dir, getpos(i, j), (dir + 3) % 6);
                    int xx = x + dx[dir];
                    int yy = y + dy[dir];
                    if (check(xx, yy)) {
                        //	cout << i - 5 << " " << j - 5<< " " << x - 5<< " " << y -5 << " " << dir << endl;
                        add(getpos(i, j), dir, getpos(x, y), dir);
                    }
                    xx = i - dx[dir];
                    yy = j - dy[dir];
                    if (check(xx, yy)) {
                        //	cout << i - 5<< " " << j - 5<< " " << xx - 5<< " " << yy - 5 << " " << dir << endl;
                        add(getpos(i, j), dir, getpos(xx, yy), dir);
                    }
                    int next = (dir + 1) % 6;
                    xx = i + dx[next];
                    yy = j + dy[next];
                    if (check(xx, yy)) {
                        //	cout << i - 5 << " " << j - 5 << " " << i - 5<< " " << j -5 << " " << dir << " " << next << " " << endl;
                        add(getpos(i, j), dir, getpos(i, j), next);
                    }
                    next = ((dir - 1) + 6) % 6;
                    xx = i + dx[next];
                    yy = j + dy[next];
                    if (check(xx, yy)) {
                        add(getpos(i, j), dir, getpos(i, j), next);
                    }
                    int ndir = (dir + 3) % 6;
                    next = (ndir + 1) % 6;
                    xx = x + dx[next];
                    yy = y + dy[next];
                    if (check(xx, yy)) {
                        add(getpos(i, j), dir, getpos(x, y), next);
                    }
                    next = (ndir + 5) % 6;
                    xx = x + dx[next];
                    yy = y + dy[next];
                    if (check(xx, yy)) {
                        add(getpos(i, j), dir, getpos(x, y), next);
                    }
                }
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        spfa(i);
    }

    vector<int> stick;
    int answer = INF;
    for (int mask = 0; mask < (1 << n); mask++) {
        if (__builtin_popcount(mask) == 6) {
            for (int tx = 1; tx <= 13; tx++) {
                for (int ty = 1; ty <= 13; ty++) {
                    px[0] = tx;
                    py[0] = ty;
                    for (int i = 1; i < 6; i++) {
                        px[i] = px[i - 1] + dx[(1 + i) % 6];
                        py[i] = py[i - 1] + dy[(1 + i) % 6];
                        direction[i - 1] = (1 + i) % 6;
                    }
                    direction[5] = 1;

                    int ok = 1;
                    for (int i = 0; i < 6; i++) {
                        if (!check(px[i], py[i])) {
                            ok = 0;
                            break;
                        }
                    }
                    if (!ok)
                        continue;

                    stick.clear();
                    for (int i = 1; i <= n; i++) {
                        if (mask >> (i - 1) & 1) {
                            stick.push_back(i);
                        }
                    }

                    for (int i = 0; i < 6; i++) {
                        target[i] = make_pair(getpos(px[i], py[i]), direction[i]);
                        ntarget[i] = make_pair(getpos(px[i] + dx[direction[i]], py[i] + dy[direction[i]]),
                                               (direction[i] + 3) % 6);
                    }

                    for (int i = 0; i < 6; i++) {
                        order[i] = i;
                    }

                    do {
                        int now = 0;
                        for (int i = 0; i < 6; i++) {
                            int d1 = dist[stick[order[i]]][target[i].first][target[i].second];
                            int d2 = dist[stick[order[i]]][ntarget[i].first][ntarget[i].second];
                            int d = min(d1, d2);
                            if (d == -1) {
                                if (d2 != -1)
                                    d = d2;
                                if (d1 != -1)
                                    d = d1;
                            }

                            if (d == -1) {
                                now = INF;
                                break;
                            } else {
                                now += d;
                            }
                        }
                        answer = min(answer, now + n - 6);
                    } while (next_permutation(order, order + 6));
                }
            }
        }
    }

    if (answer >= INF) {
        puts("impossible");
    } else {
        printf("%d\n", answer);
    }
}

int main() {
    int tests;
    scanf("%d", &tests);
    for (int i = 1; i <= tests; i++) {
        printf("Case %d: ", i);
        solve();
    }
}
