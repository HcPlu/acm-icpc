#include<cstdio>
#include<vector>

using namespace std;

vector<int> ans;

int n;

void dfs(int x) {
    int size = 0;
    if (x == 1) {
        ans.push_back(0);
        return;
    }
    while (x) {
        size++;
        ans.push_back(x & 1);
        x /= 2;
    }
    dfs(size - 1);
    return;
}

void work() {
    ans.clear();
    dfs(n);
    reverse(ans.begin(), ans.end());
    for (int i = 0; i < ans.size(); i++)
        printf("%d", ans[i]);
    puts("");
    return;
}

int main() {
    while (scanf("%d", &n) == 1 && n) {
        work();
    }
    return 0;
}
