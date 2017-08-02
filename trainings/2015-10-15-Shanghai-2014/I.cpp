#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<set>


using namespace std;

const int N = 100005;

pair<int, int> troop[N], vil[N], temp[N];

multiset<int> exist;

void work() {
    exist.clear();
    int n, m;
    scanf("%d%d", &m, &n);
    for (int i = 1; i <= m; i++)
        scanf("%d%d", &troop[i].first, &troop[i].second);
    sort(troop + 1, troop + 1 + m);
    reverse(troop + 1, troop + 1 + m);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &vil[i].first, &vil[i].second);
        temp[i] = vil[i];
        swap(temp[i].first, temp[i].second);
        temp[i].first *= -1;
    }
    sort(temp + 1, temp + 1 + n);

    for (int i = 1; i <= n; i++) {
        vil[i] = temp[i];
        swap(vil[i].first, vil[i].second);
        vil[i].second *= -1;
    }

    int ans = 0;
    for (int i = 1, j = 1; i <= n; i++) {
        while (j <= m && troop[j].first >= vil[i].second) {
            exist.insert(troop[j].second);
            j++;
        }
        if (exist.size() == 0) {
            puts("-1");
            return;
        }
        multiset<int>::iterator it = exist.lower_bound(vil[i].first + 1);
        if (it == exist.end()) {
            ans++;
            exist.erase(exist.begin());
        } else {
            exist.erase(it);
        }
    }
    cout << m - ans << endl;
    return;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int i = 1; i <= T; i++) {
        printf("Case #%d: ", i);
        work();
    }
}
