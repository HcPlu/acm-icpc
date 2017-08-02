#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<set>

using namespace std;

int n, bh[277];
int rev[6];
int dx[5] = {0, -1, 0, 1, 0};
int dy[5] = {0, 0, -1, 0, 1};

pair<int, pair<int, int> > go(pair<int, int> now, int dir, int go) {
    for (int i = 1; i <= go; i++) {
        pair<int, int> temp = now;
        temp.first += dx[dir];
        temp.second += dy[dir];
        if (temp.first == 0 || temp.first > n || temp.second > n || temp.second == 0) {
            dir = rev[dir];
            i--;
            continue;
        } else {
            now = temp;
        }
    }
    return make_pair(dir, now);
}

void work() {
    int s1, t1, s2, t2;
    int dir1, dir2;
    pair<int, int> pos1 = make_pair(1, 1);
    pair<int, int> pos2 = make_pair(n, n);
    char c[11];
    scanf("%s", c + 1);
    dir1 = bh[c[1]];
    scanf("%d%d", &s1, &t1);
    scanf("%s", c + 1);
    dir2 = bh[c[1]];
    scanf("%d%d", &s2, &t2);
    int limit;
    scanf("%d", &limit);
    for (int i = 1; i <= limit; i++) {

        pair<int, pair<int, int> > t = go(pos1, dir1, s1);
        dir1 = t.first;
        pos1 = t.second;

        t = go(pos2, dir2, s2);
        dir2 = t.first;
        pos2 = t.second;

        if (pos1 == pos2) {
            swap(dir1, dir2);
        } else {
            if (i % t1 == 0) {
                dir1 = dir1 % 4 + 1;
            }
            if (i % t2 == 0) {
                dir2 = dir2 % 4 + 1;
            }
        }
    }
    printf("%d %d\n", pos1.first, pos1.second);
    printf("%d %d\n", pos2.first, pos2.second);
    return;
}

int main() {
    bh['N'] = 1;
    bh['W'] = 2;
    bh['S'] = 3;
    bh['E'] = 4;
    rev[1] = 3;
    rev[3] = 1;
    rev[2] = 4;
    rev[4] = 2;
    while (scanf("%d", &n) == 1 && n) {
        work();
    }
}
