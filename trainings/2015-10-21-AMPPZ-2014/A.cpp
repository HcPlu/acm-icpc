#include <iostream>
#include <vector>

using namespace std;

int n, m;

int main() {
    vector<pair<int, int> > begins[99];
    vector<pair<int, int> > ends[99];

    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        int l, r, d;
        scanf("%d%d%d", &l, &r, &d);
        begins[d].push_back(make_pair(l, i));
        ends[d].push_back(make_pair(r, i));
    }
    for (int i = 1; i <= m; i++) {
        if (begins[i].size() == 0) {
            puts("NIE");
            continue;
        }
        sort(begins[i].begin(), begins[i].end());
        sort(ends[i].begin(), ends[i].end());
        if (ends[i][0].first < begins[i].back().first) {
            printf("TAK %d %d\n", ends[i][0].second, begins[i].back().second);
        } else {
            puts("NIE");
        }
    }

    return 0;
}
