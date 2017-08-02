#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

const int N = 22;
const int LEN = 22;
const int M = 130;

char type[M][LEN];
int length[M];

vector<pair<int, int> > f[2];

int r, c;

int get_num(int x) {
    return __builtin_popcount(x);
}

int next(int x) {
    return (x << 1) & ((1 << c) - 1);
}

int main() {
    scanf("%d%d", &r, &c);
    for (int i = 1; i <= r; i++) {
        scanf("%s", type[i] + 1);
        length[i] = strlen(type[i] + 1);
    }
    int now = 0;
    f[now].push_back(make_pair(0, 0));
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            vector<pair<int, int> > &previous = f[now];
            vector<pair<int, int> > &current = f[now ^ 1];
            current.clear();
            std::sort(previous.begin(), previous.end());

            int size = 0;
            for (int k = 0; k < (int)previous.size(); ++k) {
                if (k == (int)previous.size() - 1 || previous[k + 1].first != previous[k].first) {
                    previous[size++] = previous[k];
                }
            }
            previous.resize(size);
            for (int k = 0; k < (int)previous.size(); ++k) {
                pair<int, int> t = previous[k];
                int mask = t.first;
                int t2 = mask - (mask >> j - 1 << j - 1), t1 = mask >> j - 1;
                int num1 = get_num(t1), num2 = get_num(t2);
                if (num2 + c - j >= length[i]) {
                    current.push_back(make_pair(next(t.first), t.second));
                }
                if (num2 + 1 <= length[i]) {
                    int exist = (t.first >> (c - 1) & 1);
                    if (exist != 0)
                        exist = length[i - 1] - num1 + 1;
                    char up = type[i - 1][exist];
                    exist = (t.first & 1);
                    if (exist != 0)
                        exist = num2;
                    char left = type[i][exist];
                    t.second = t.second + (up == type[i][num2 + 1]) + (left == type[i][num2 + 1]);
                    current.push_back(make_pair(next(t.first) | 1, t.second));
                }
            }
            now ^= 1;
        }
    }
    int ans = 0;
    for (int i = 0; i < f[now].size(); i++)
        ans = max(ans, f[now][i].second);
    printf("%d\n", ans * 2);
    return 0;
}
