#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <set>

using namespace std;

const int N = 100005;

int father[N], value[N], tot = 0, gxx = 0;
int l[N], r[N], cnt = 0;
int digit[N], ans[N], start[N];

multiset<int> ac[N << 2];

struct Segtree {
    int l, r;
    int id;
} tree[N << 2];

struct Node {
    int x, y, next;
} road[N << 1];

void build(int x, int y) {
    tot++;
    road[tot].x = x, road[tot].y = y, road[tot].next = start[x], start[x] = tot;
}

void get(int x, int fa) {
    l[x] = ++gxx;
    for (int i = start[x]; i; i = road[i].next) {
        int to = road[i].y;
        if (to == fa)
            continue;
        get(to, x);
    }
    r[x] = gxx;
}

void build(int root, int l, int r) {
    tree[root].id = ++cnt;
    ac[cnt].clear();
    tree[root].l = l, tree[root].r = r;
    if (tree[root].l == tree[root].r)
        return;
    int mid = l + r >> 1;
    build(root << 1, l, mid), build(root << 1 | 1, mid + 1, r);
    return;
}

void add(int root, int t, int delta) {
    if (delta == 1)
        ac[root].insert(t);
    else
        ac[root].erase(t);
    return;
}

void update(int root, int l, int r, int k, int delta) {
    if (tree[root].l == l && tree[root].r == r) {
        add(tree[root].id, k, delta);
        return;
    }
    int mid = tree[root].l + tree[root].r >> 1;
    if (r <= mid)
        update(root << 1, l, r, k, delta);
    else if (l > mid)
        update(root << 1 | 1, l, r, k, delta);
    else
        update(root << 1, l, mid, k, delta), update(root << 1 | 1, mid + 1, r, k, delta);
}

int get_Max(int root, int x) {
    for (int i = 1; i <= 30; i++)
        digit[i] = (x >> i - 1) & 1;
    int ans = 0;
    int now = 0;
    for (int i = 30; i >= 1; i--) {
        ans *= 2;
        int need = digit[i] ^1;
        int L = now + need * (1 << i - 1);
        int R = now + (need + 1) * (1 << i - 1);
        if (ac[root].lower_bound(L) != ac[root].lower_bound(R)) {
            ans++;
            now += need * (1 << i - 1);
        } else
            now += (need ^ 1) * (1 << i - 1);
    }
    return ans;
}

int Query(int root, int x, int value) {
    int t = get_Max(tree[root].id, value);
    if (tree[root].l == tree[root].r)
        return t;
    int mid = tree[root].l + tree[root].r >> 1;
    if (x <= mid)
        return max(t, Query(root << 1, x, value));
    else
        return max(t, Query(root << 1 | 1, x, value));
}

void work() {
    int n, q;
    scanf("%d%d", &n, &q);
    for (int i = 2; i <= n; i++)
        scanf("%d", &father[i]);
    for (int i = 1; i <= n; i++)
        scanf("%d", &value[i]);
    for (int i = 1; i <= n; i++)
        start[i] = 0;
    tot = gxx = cnt = 0;
    for (int i = 2; i <= n; i++)
        build(father[i], i), build(i, father[i]);
    get(1, 0);
    build(1, 1, n);
    for (int i = 1; i <= n; i++) {
        update(1, l[i], r[i], value[i], 1);
    }
    int p, v;
    for (int i = 1; i <= q; i++) {
        int type;
        scanf("%d", &type);
        if (type == 0) {
            scanf("%d%d", &p, &v);
            update(1, l[p], r[p], value[p], -1);
            update(1, l[p], r[p], v, 1);
            value[p] = v;
        } else {
            scanf("%d", &v);
            printf("%d\n", Query(1, l[v], value[v]));
        }
    }
    return;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int i = 1; i <= T; i++)
        work();
    return 0;
}
