#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>

using namespace std;

const int N = 1000005;

int a[N], n;
int temp[N], L[N], R[N];

pair<int, int> zero[N], one[N];
pair<int, int> ans = make_pair(-1, 0);

struct Eve {
    Eve() {
    }

    Eve(int type, int x, int y, int now) : type(type), x(x), y(y), now(now) {
    }

    int type, x, y, now;
} seg[N * 2];

struct Segtree {
    int l, r;
    pair<int, int> value;
} tree[N << 2];

void update(pair<int, int> &x, pair<int, int> y) {
    if (x.first == y.first) {
        x.second = min(x.second, y.second);
    } else {
        x = max(x, y);
    }
}

pair<int, int> mymax(pair<int, int> x, pair<int, int> y) {
    if (x.first == y.first) {
        x.second = min(x.second, y.second);
    } else {
        x = max(x, y);
    }
    return x;
}

void build(int root, int l, int r) {
    tree[root].l = l;
    tree[root].r = r;
    tree[root].value = make_pair(-1, 0);
    if (l == r) {
        return;
    }
    int mid = tree[root].l + tree[root].r >> 1;
    build(root << 1, l, mid);
    build(root << 1 | 1, mid + 1, r);
    return;
}

void update(int root) {
    tree[root].value = mymax(tree[root << 1].value, tree[root << 1 | 1].value);
    return;
}

void add(int root, int x, pair<int, int> k) {
    if (tree[root].l == tree[root].r) {
        tree[root].value = max(tree[root].value, k);
        return;
    }
    int mid = tree[root].l + tree[root].r >> 1;
    if (x <= mid) {
        add(root << 1, x, k);
    } else {
        add(root << 1 | 1, x, k);
    }
    update(root);
}

pair<int, int> Query(int root, int l, int r) {
    if (tree[root].l == l && tree[root].r == r) {
        return tree[root].value;
    }
    int mid = tree[root].l + tree[root].r >> 1;
    if (r <= mid) {
        return Query(root << 1, l, r);
    } else if (l > mid) {
        return Query(root << 1 | 1, l, r);
    } else {
        return mymax(Query(root << 1, l, mid), Query(root << 1 | 1, mid + 1, r));
    }
}

bool cmpx(Eve x, Eve y) {
    if (x.x == y.x) {
        if (x.type == y.type) {
            return x.y < y.y;
        } else {
            return x.type < y.type;
        }
    } else {
        return x.x < y.x;
    }
}

void get() {
    static pair<int, int> stack[N];
    int top = 0;
    stack[++top] = make_pair(0x3f3f3f3f, 0);
    for (int i = 1; i <= n; i++) {

        while (top && stack[top].first < a[i]) {
            top--;
        }

        temp[i] = stack[top].second + 1;
        stack[++top] = make_pair(a[i], i);
    }
    return;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    get();
    for (int i = 1; i <= n; i++)
        L[i] = temp[i];
    reverse(a + 1, a + 1 + n);
    get();
    for (int i = 1; i <= n; i++)
        R[i] = temp[i];
    for (int i = 1; i <= n; i++)
        zero[i] = make_pair(L[i], n - R[n - i + 1] + 1);

    reverse(a + 1, a + 1 + n);
    for (int i = 1; i <= n; i++)
        a[i] *= -1;
    get();

    for (int i = 1; i <= n; i++)
        L[i] = temp[i];
    reverse(a + 1, a + 1 + n);
    get();
    for (int i = 1; i <= n; i++)
        R[i] = temp[i];
    for (int i = 1; i <= n; i++)
        one[i] = make_pair(L[i], n - R[n - i + 1] + 1);

    int cnt = 0;

    for (int i = 1; i <= n; i++) {
        seg[++cnt] = Eve(0, zero[i].first, zero[i].second, i);
    }
    for (int i = 1; i <= n; i++) {
        seg[++cnt] = Eve(1, one[i].first, one[i].second, i);
    }

    sort(seg + 1, seg + 1 + cnt, cmpx);

    int Maxr = 0;

    n *= 2;

    build(1, 1, n);

    for (int i = 1; i <= n; i++) {
        if (seg[i].type == 0) {
            add(1, seg[i].now, make_pair(seg[i].y, seg[i].x));
        } else {
            pair<int, int> t = Query(1, seg[i].x, seg[i].y);
            t.first = min(t.first, seg[i].y);
            if (t.first >= seg[i].now) {
                update(ans, make_pair(t.first - seg[i].x + 1, seg[i].x));
            }
        }
    }

    for (int i = 1; i <= n; i++)
        seg[i].type ^= 1;
    sort(seg + 1, seg + 1 + cnt, cmpx);

    build(1, 1, n);

    for (int i = 1; i <= n; i++) {
        if (seg[i].type == 0) {
            add(1, seg[i].now, make_pair(seg[i].y, seg[i].x));
        } else {
            pair<int, int> t = Query(1, seg[i].x, seg[i].y);
            t.first = min(t.first, seg[i].y);
            if (t.first >= seg[i].now) {
                update(ans, make_pair(t.first - seg[i].x + 1, seg[i].x));
            }
        }
    }

    printf("%d %d\n", ans.first, ans.second);
    return 0;
}
