#include <iostream>
#include <vector>

using namespace std;
const int INF = 1 << 30;
const int N = 2222;
int isx[N], num[N], n;

void solve() {
    char text[100];
    for (int i = 0; i <= n; i++)
        isx[i] = 0;
    num[0] = INF;
    vector<int> pos;
    for (int i = 1; i <= n; i++) {
        scanf("%s", text);
        if (text[0] == 'x') {
            isx[i] = 1;
            pos.push_back(i);
        } else {
            num[i] = atoi(text);
        }
    }

    for (int i = 1; i <= n; i++) {
        if (isx[i] && isx[i - 1]) {
            puts("none");
            return;
        }
        if (isx[i])
            continue;
        if (i & 1) {
            if (!isx[i - 1]) {
                if (num[i] >= num[i - 1]) {
                    puts("none");
                    return;
                }
            }
        } else {
            if (!isx[i - 1]) {
                if (num[i] <= num[i - 1]) {
                    puts("none");
                    return;
                }
            }
        }
    }

    int minx = -INF;
    int maxx = INF;
    for (int i = 0; i < (int)pos.size(); i++) {
        int now = pos[i];
        if (now & 1) {
            if (now > 1) {
                maxx = min(maxx, num[now - 1] - 1);
            }
            if (now < n) {
                maxx = min(maxx, num[now + 1] - 1);
            }
        } else {
            if (now > 1) {
                minx = max(minx, num[now - 1] + 1);
            }
            if (now < n) {
                minx = max(minx, num[now + 1] + 1);
            }
        }
    }
    if (minx == maxx) {
        printf("%d\n", minx);
    } else {
        if (minx < maxx) {
            puts("ambiguous");
        } else {
            puts("none");
        }
    }
}

int main() {
    for (; scanf("%d", &n) && n; solve());
    return 0;
}
