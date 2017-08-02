#include <cstdio>
#include <algorithm>
#include <iostream>

using namespace std;

const long long INF = 1111111111111111111LL;

const int N = 5005;

pair<long long, long long> bel[N];
long long n, a[N], ed[N];
long long CC = INF, minid, begin[N];
long long T[N], b[N], st[N], m[N], pos[10];
bool added[N];

long long extend_gcd(long long aa, long long bb, long long &x, long long &y) {
    if (aa == 0 && bb == 0)
        return -1;
    if (bb == 0) {
        x = 1;
        y = 0;
        return aa;
    }
    long long d = extend_gcd(bb, aa % bb, y, x);
    y -= aa / bb * x;
    return d;
}

bool solve(long long &M, long long &B, long long mm, long long bb) {
    long long y, x;
    long long g = extend_gcd(M, mm, x, y);
    if (abs(bb - B) % g)
        return false;
    x *= (bb - B) / g;
    x %= mm / g;
    B = (x * M + B);
    M *= mm / g;
    B %= M;
    if (B < 0)
        B += M;
    return true;
}

bool china(long long &M, long long &B, long long n) {
    bool flag = true;
    M = 1;
    B = 0;
    for (long long i = 1; i <= n; i++) {
        if (!solve(M, B, m[i], b[i])) {
            flag = false;
            break;
        }
    }
    return flag;
}

void get_ans() {
    for (long long i = 1; i <= n; i++) {
        if (i != 1)
            for (long long j = 1; j <= 5; j++)
                ed[j] += 5;
        for (long long j = 1; j <= 5; j++)
            if (bel[ed[j]].first != bel[st[j]].first)
                goto syf;
        for (long long j = 1; j <= 5; j++)
            m[j] = T[bel[ed[j]].first], b[j] = (bel[ed[j]].second - bel[st[j]].second + m[j]) % m[j];
        long long M, B;
        if (!china(M, B, 5))
            continue;
        if (B < CC)
            CC = B, minid = i;
        syf:;
    }
}

long long go(long long x, long long Max) {
    long long num = 0, tmp;
    while (x > 2 * n)
        x -= 2 * n, num++;
    tmp = x;
    if (num <= 1) {
        x += (x & 1);
        return (x / 2 - 1) * 5 + 2 * num + 1 + (tmp + 1) % 2;
    } else
        return x * 5;
}

void work() {
    long long tmp[N];
    CC = INF, minid = 0;
    for (long long i = 1; i <= 5 * n; i++)
        cin >> begin[i];
    for (long long i = 1; i <= 5 * n; i++)
        a[go(i, n)] = begin[i];
    for (long long i = 1; i <= 5 * n; i++)
        added[i] = false;
    long long block = 0;
    for (long long i = 1; i <= 5 * n; i++) {
        if (added[i])
            continue;
        block++;
        long long now = i, cnt = 1;
        while (!added[now]) {
            added[now] = true;
            bel[now] = make_pair(block, cnt);
            ++cnt;
            now = go(now, n);
        }
        T[block] = cnt - 1;
    }
    for (long long i = 1; i <= 5 * n; i++)
        if (a[i] <= 5)
            st[a[i]] = i;
    for (pos[1] = 1; pos[1] <= 5; pos[1]++)
        for (pos[2] = 1; pos[2] <= 5; pos[2]++)
            for (pos[3] = 1; pos[3] <= 5; pos[3]++)
                for (pos[4] = 1; pos[4] <= 5; pos[4]++)
                    for (pos[5] = 1; pos[5] <= 5; pos[5]++) {
                        for (long long k = 1; k <= 5; k++)
                            tmp[k] = pos[k];
                        sort(tmp + 1, tmp + 6);
                        if (unique(tmp + 1, tmp + 6) - tmp - 1 != 5)
                            continue;
                        for (long long k = 1; k <= 5; k++)
                            ed[k] = pos[k];
                        get_ans();
                    }
    if (CC == INF)
        puts("Neverending game.");
    else {
        printf("Player %lld wins game number ", minid);
        cout << CC + 1 << "." << endl;
    }
}

int main() {
    cin >> n;
    while (n) {
        work();
        cin >> n;
    }
    return 0;
}