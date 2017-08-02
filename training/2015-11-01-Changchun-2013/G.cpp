#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>

using namespace std;

const int N = 808;

int a[N][N], n, m;
int tot = 0;
struct Segtree {
    int l, r, lson, rson;
    int id;
    int Max, Min;
} tree[N * N * 4];

void update(int root) {
    tree[root].Max = max(tree[tree[root].lson].Max, tree[tree[root].rson].Max);
    tree[root].Min = min(tree[tree[root].lson].Min, tree[tree[root].rson].Min);
    return;
}

void build2(int root, int l, int r) {
    tree[root].l = l;
    tree[root].r = r;
    tree[root].Max = -0x3f3f3f3f;
    tree[root].Min = 0x3f3f3f3f;
    if (l == r) {
        return;
    }
    int mid = l + r >> 1;
    tree[root].lson = ++tot;
    tree[root].rson = ++tot;
    build2(tree[root].lson, l, mid);
    build2(tree[root].rson, mid + 1, r);
    update(root);
}

void build1(int root, int l, int r) {
    tree[root].l = l;
    tree[root].r = r;
    tree[root].id = ++tot;
    build2(tot, 1, m);
    if (l == r) {
        return;
    }
    int mid = l + r >> 1;
    tree[root].lson = ++tot;
    tree[root].rson = ++tot;
    build1(tree[root].lson, l, mid);
    build1(tree[root].rson, mid + 1, r);
}

pair<int, int> uni(pair<int, int> x, pair<int, int> y) {
    return make_pair(max(x.first, y.first), min(x.second, y.second));
}

pair<int, int> Query2(int root, int l, int r) {
    if (tree[root].l == l && tree[root].r == r) {
        return make_pair(tree[root].Max, tree[root].Min);
    }
    int mid = tree[root].l + tree[root].r >> 1;
    if (r <= mid) {
        return Query2(tree[root].lson, l, r);
    } else if (l > mid) {
        return Query2(tree[root].rson, l, r);
    } else {
        return uni(Query2(tree[root].lson, l, mid), Query2(tree[root].rson, mid + 1, r));
    }
}

pair<int, int> Query1(int root, int l1, int r1, int l2, int r2) {
    if (tree[root].l == l1 && tree[root].r == r1) {
        return Query2(tree[root].id, l2, r2);
    }
    int mid = tree[root].l + tree[root].r >> 1;
    if (r1 <= mid) {
        return Query1(tree[root].lson, l1, r1, l2, r2);
    } else if (l1 > mid) {
        return Query1(tree[root].rson, l1, r1, l2, r2);
    } else {
        return uni(Query1(tree[root].lson, l1, mid, l2, r2), Query1(tree[root].rson, mid + 1, r1, l2, r2));
    }
}

void update2(int root, int y, int key) {
    if (tree[root].l == tree[root].r) {
        tree[root].Max = key;
        tree[root].Min = key;
        return;
    }
    int mid = tree[root].l + tree[root].r >> 1;
    if (y <= mid) {
        update2(tree[root].lson, y, key);
    } else {
        update2(tree[root].rson, y, key);
    }
    update(root);
}

void update_uni(int root, int l, int r, int y) {
    tree[root].Max = max(tree[l].Max, tree[r].Max);
    tree[root].Min = min(tree[l].Min, tree[r].Min);
    if (tree[root].l == tree[root].r) {
        return;
    }
    int mid = tree[root].l + tree[root].r >> 1;
    if (y <= mid) {
        update_uni(tree[root].lson, tree[l].lson, tree[r].lson, y);
    } else {
        update_uni(tree[root].rson, tree[l].rson, tree[r].rson, y);
    }
}

void update1(int root, int x, int y, int key) {
    if (tree[root].l == tree[root].r) {
        update2(tree[root].id, y, key);
        return;
    }
    int mid = tree[root].l + tree[root].r >> 1;
    if (x <= mid) {
        update1(tree[root].lson, x, y, key);
    } else {
        update1(tree[root].rson, x, y, key);
    }

    update_uni(tree[root].id, tree[tree[root].lson].id, tree[tree[root].rson].id, y);
}

void work() {
    scanf("%d", &n);
    m = n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &a[i][j]);
    tot = 1;
    build1(1, 1, n);
    int Q;
    scanf("%d", &Q);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            update1(1, i, j, a[i][j]);

    for (int i = 1; i <= Q; i++) {
        int x, y, l;
        scanf("%d%d%d", &x, &y, &l);
        int delta = (l >> 1);
        int l1 = x - delta;
        int r1 = x + delta;
        int l2 = y - delta;
        int r2 = y + delta;
        r1 = min(r1, n);
        r2 = min(r2, n);
        l1 = max(l1, 1);
        l2 = max(l2, 1);
        pair<int, int> t = Query1(1, l1, r1, l2, r2);
        int now = floor(1. * (t.first + t.second) / 2);
        printf("%d\n", now);
        update1(1, x, y, now);
    }
}

int main() {
    int T;
    scanf("%d", &T);
    for (int i = 1; i <= T; i++) {
        printf("Case #%d:\n", i);
        work();
    }
    return 0;
}
