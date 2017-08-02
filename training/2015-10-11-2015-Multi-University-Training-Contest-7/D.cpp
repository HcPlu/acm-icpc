#include <iostream>
#include <map>
#include <vector>

#define right RIGHT
#define left LEFT
using namespace std;
const int N = 444444;

int left[N], right[N], counter, deleted[N], tp[N];

int lowbit(int x) {
    return x & (-x);
}

void modify_left(int x, int d) {
    for (int i = x; i <= counter; i += lowbit(i)) {
        left[i] += d;
    }
}

void modify_right(int x, int d) {
    for (int i = x; i <= counter; i += lowbit(i)) {
        right[i] += d;
    }
}

int sum_left(int x) {
    int ret = 0;
    for (int i = x; i > 0; i -= lowbit(i)) {
        ret += left[i];
    }
    return ret;
}

int sum_right(int x) {
    int ret = 0;
    for (int i = x; i > 0; i -= lowbit(i)) {
        ret += right[i];
    }
    return ret;
}

int query_left(int l, int r) {
    return sum_left(r) - sum_left(l - 1);
}

int query_right(int l, int r) {
    return sum_right(r) - sum_right(l - 1);
}

vector<int> numbers;

int find(int x) {
    return std::lower_bound(numbers.begin(), numbers.end(), x) - numbers.begin() + 1;
}

int n;

void solve() {
    numbers.clear();
    vector<int> query[2];
    for (int i = 1; i <= n; i++) {
        int type, num;
        scanf("%d%d", &type, &num);
        tp[i] = type;
        query[type].push_back(num);
        if (type == 0) {
            numbers.push_back(num);
            numbers.push_back(num + (int)query[0].size() - 1);
        }
    }

    sort(numbers.begin(), numbers.end());
    numbers.erase(unique(numbers.begin(), numbers.end()), numbers.end());

    counter = (int)numbers.size();
    for (int i = 1; i <= counter; i++) {
        left[i] = right[i] = 0;
    }
    for (int i = 1; i <= n; i++) {
        deleted[i] = 0;
    }
    int now0 = 0, now1 = 0;
    for (int i = 1; i <= n; i++) {
        int type = tp[i];
        if (type == 0) {
            int num = query[type][now0++];
            int l = find(num);
            int r = find(num + now0 - 1);
            int ans = query_left(l, counter) - query_right(r + 1, counter);
            printf("%d\n", ans);
            modify_left(l, 1);
            modify_right(r, 1);
        } else {
            int num = query[type][now1++];
            if (deleted[num])
                continue;
            deleted[num] = 1;
            int l = find(query[0][num - 1]);
            int r = find(query[0][num - 1] + num - 1);
            modify_left(l, -1);
            modify_right(r, -1);
        }
    }
}

int main() {
    for (; scanf("%d", &n) != -1;) {
        static int counter = 0;
        printf("Case #%d:\n", ++counter);
        solve();
    }
    return 0;
}
