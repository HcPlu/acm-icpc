#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>

const int N = 111111;

int n;
int item[N];
std::pair<int, int> tree[N << 2];
int tag[N << 2];

void modify(int x, int val) {
    tree[x].first += val;
    tag[x] += val;
}

void release(int x) {
    if (tag[x]) {
        modify(x << 1, tag[x]);
        modify(x << 1 | 1, tag[x]);
        tag[x] = 0;
    }
}

void update(int x) {
    tree[x] = std::min(tree[x << 1], tree[x << 1 | 1]);
}

void modify(int x, int l, int r, int ql, int qr, int val) {
    if (qr < l || r < ql) {
        return;
    }
    if (ql <= l && r <= qr) {
        modify(x, val);
        return;
    }
    int mid = l + r >> 1;
    release(x);
    modify(x << 1, l, mid, ql, qr, val);
    modify(x << 1 | 1, mid + 1, r, ql, qr, val);
    update(x);
}

void build(int x, int l, int r) {
    tag[x] = 0;
    if (l == r) {
        tree[x] = std::make_pair(item[l], l);
    } else {
        int mid = l + r >> 1;
        build(x << 1, l, mid);
        build(x << 1 | 1, mid + 1, r);
        update(x);
    }
}

void solve(void) {
    for (int i = 1; i <= n; ++i) {
        scanf("%d", item + i);
    }
    build(1, 1, n);

    std::queue<int> answer, pool;
    for (; (int)answer.size() + (int)pool.size() < n + n;) {
        std::pair<int, int> best = tree[1];
        if (best.first < 0 || best.first > n) {
            puts("Impossible");
            return;
        }
        if (best.first == 0) {
            int x = best.second;
            answer.push(x);
            pool.push(-x);
            modify(1, 1, n, x, x, n * 10);
            modify(1, 1, n, 1, x - 1, -1);
        } else {
            if (pool.empty()) {
                puts("Impossible");
                return;
            }
            int x = pool.front();
            pool.pop();
            answer.push(x);
            modify(1, 1, n, -x + 1, n, -1);
        }
    }

    std::vector<int> result;
    for (; !answer.empty(); result.push_back(answer.front()), answer.pop());
    for (; !pool.empty(); result.push_back(pool.front()), pool.pop());

    std::reverse(result.begin(), result.end());
    for (int i = 0; i < (int)result.size(); ++i) {
        printf("%d%s", result[i], (i == (int)result.size() - 1) ? " \n" : " ");
    }
}

int main(void) {
    for (; scanf("%d", &n) && n; solve());
}
