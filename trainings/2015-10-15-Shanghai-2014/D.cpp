#include<cstdio>
#include<algorithm>

using namespace std;

const int N = 110005;

int n, w, h, tempx[N * 12], tempy[N * 12];
int cntx = 0, cnty = 0;

struct Node {
    int x1, x2, y1, y2;
    int value;

    Node() {
    }

    Node(int x1, int y1, int x2, int y2, int value) : x1(x1), y1(y1), x2(x2), y2(y2), value(value) {
    }
} block[N * 3];

struct Ask {
    int x;
    int l, r, value;

    Ask() {
    }

    Ask(int x, int l, int r, int value) : x(x), l(l), r(r), value(value) {
    }

    friend bool operator <(const Ask &x, const Ask &y) {
        return x.x < y.x;
    }
} event[N * 6];

struct Segtree {
    int l, r;
    long long Max;
    long long tag;
} tree[N * 24];

void build(int root, int x, int y) {
    tree[root].l = x;
    tree[root].r = y;
    tree[root].Max = tree[root].tag = 0;
    if (x == y)
        return;
    int mid = x + y >> 1;
    build(root << 1, x, mid);
    build(root << 1 | 1, mid + 1, y);
    return;
}

void update(int root, long long value) {
    tree[root].tag += value;
    tree[root].Max += value;
    return;
}

void push_down(int root) {
    if (tree[root].tag == 0) {
        return;
    }
    update(root << 1, tree[root].tag);
    update(root << 1 | 1, tree[root].tag);
    tree[root].tag = 0;
}

void add(int root, int l, int r, long long value) {
    if (tree[root].l == l && tree[root].r == r) {
        update(root, value);
        return;
    }
    push_down(root);
    int mid = tree[root].l + tree[root].r >> 1;
    if (r <= mid) {
        add(root << 1, l, r, value);
    } else if (l > mid) {
        add(root << 1 | 1, l, r, value);
    } else {
        add(root << 1, l, mid, value);
        add(root << 1 | 1, mid + 1, r, value);
    }
    tree[root].Max = max(tree[root << 1].Max, tree[root << 1 | 1].Max);
    return;
}

long long Query(int root) {
    return tree[root].Max;
}

void work() {
    scanf("%d%d%d", &n, &w, &h);
    int cnt = 0;
    int Max = 10000005;
    cntx = 0, cnty = 0;
    for (int i = 1; i <= n; i++) {
        int x, y;
        scanf("%d%d", &y, &x);
        block[++cnt] = Node(x - h + 1, y - w + 1, x, y, -0x3f3f3f3f);
        block[++cnt] = Node(-Max, y - w + 1, Max, y, 1);
        block[++cnt] = Node(x - h + 1, -Max, x, Max, 1);
    }
    int num = 0;

    if (w == 0 || h == 0) {
        puts("0");
        return;
    }

    for (int i = 1; i <= cnt; i++) {
        tempx[++cntx] = block[i].x1, tempy[++cnty] = block[i].y1;
        tempx[++cntx] = block[i].x2, tempy[++cnty] = block[i].y2;
    }

    sort(tempx + 1, tempx + 1 + cntx);
    sort(tempy + 1, tempy + 1 + cnty);

    cntx = unique(tempx + 1, tempx + 1 + cntx) - tempx + 1;
    cnty = unique(tempy + 1, tempy + 1 + cnty) - tempy + 1;

    for (int i = 1; i <= cnt; i++) {
        block[i].x1 = lower_bound(tempx + 1, tempx + 1 + cntx, block[i].x1) - tempx;
        block[i].x2 = lower_bound(tempx + 1, tempx + 1 + cntx, block[i].x2) - tempx;
        block[i].y1 = lower_bound(tempy + 1, tempy + 1 + cnty, block[i].y1) - tempy;
        block[i].y2 = lower_bound(tempy + 1, tempy + 1 + cnty, block[i].y2) - tempy;
    }

    for (int i = 1; i <= cnt; i++) {
        event[++num] = Ask(block[i].y1, block[i].x1, block[i].x2, block[i].value);
        event[++num] = Ask(block[i].y2 + 1, block[i].x1, block[i].x2, -block[i].value);
    }

    cntx++;

    build(1, 1, cntx);

    sort(event + 1, event + 1 + num);
    long long ans = 0;
    for (int i = 1, j; i <= num; i = j) {
        for (j = i; event[j].x == event[i].x && j <= num; j++);
        for (int k = i; k < j; k++) {
            add(1, event[k].l, event[k].r, event[k].value);
        }
        long long t = Query(1);
        ans = max(ans, t);
    }
    printf("%lld\n", ans);
    return;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int i = 1; i <= T; i++) {
        printf("Case #%d: ", i);
        work();
    }
    return 0;
}
