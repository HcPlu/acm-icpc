#include <cstdio>
#include <algorithm>
#include <vector>

const int N = 111;

int n;
std::vector<std::pair<int, int> > edge;
bool graph[N][N];

bool solve(std::vector<std::pair<int, int> > &value) {
    if (value.empty()) {
        return true;
    }

    std::sort(value.begin(), value.end());

    int x = value.back().second;
    int num = value.back().first;

    if ((int)value.size() - 1 < num) {
        return false;
    }

    for (int i = (int)value.size() - 2; num > 0; --i, --num) {
        int y = value[i].second;
        value[i].first--;
        if (value[i].first < 0) {
            return false;
        }
        edge.push_back(std::make_pair(x, y));
        graph[x][y] = graph[y][x] = true;
    }

    value.pop_back();
    return solve(value);
}

void print() {
    for (int i = 0; i < (int)edge.size(); ++i) {
        for (int j = i + 1; j < (int)edge.size(); ++j) {
            int x1 = edge[i].first, y1 = edge[i].second;
            int x2 = edge[j].first, y2 = edge[j].second;
            if (x1 != y2 && x2 != y1 && !graph[x1][y2] && !graph[x2][y1]) {
                puts("MULTIPLE");
                printf("%d %d\n", n, (int)edge.size());
                for (int k = 0; k < (int)edge.size(); ++k) {
                    printf("%d%s", edge[k].first, (k == (int)edge.size() - 1) ? "\n" : " ");
                }
                for (int k = 0; k < (int)edge.size(); ++k) {
                    printf("%d%s", edge[k].second, (k == (int)edge.size() - 1) ? "\n" : " ");
                }
                edge[i] = std::make_pair(x1, y2);
                edge[j] = std::make_pair(x2, y1);
                printf("%d %d\n", n, (int)edge.size());
                for (int k = 0; k < (int)edge.size(); ++k) {
                    printf("%d%s", edge[k].first, (k == (int)edge.size() - 1) ? "\n" : " ");
                }
                for (int k = 0; k < (int)edge.size(); ++k) {
                    printf("%d%s", edge[k].second, (k == (int)edge.size() - 1) ? "\n" : " ");
                }
                edge[i] = std::make_pair(x1, y1);
                edge[j] = std::make_pair(x2, y2);
                return;
            }
            if (x1 != x2 && y1 != y2 && !graph[x1][x2] && !graph[y1][y2]) {
                puts("MULTIPLE");
                printf("%d %d\n", n, (int)edge.size());
                for (int k = 0; k < (int)edge.size(); ++k) {
                    printf("%d%s", edge[k].first, (k == (int)edge.size() - 1) ? "\n" : " ");
                }
                for (int k = 0; k < (int)edge.size(); ++k) {
                    printf("%d%s", edge[k].second, (k == (int)edge.size() - 1) ? "\n" : " ");
                }
                edge[i] = std::make_pair(x1, x2);
                edge[j] = std::make_pair(y1, y2);
                printf("%d %d\n", n, (int)edge.size());
                for (int k = 0; k < (int)edge.size(); ++k) {
                    printf("%d%s", edge[k].first, (k == (int)edge.size() - 1) ? "\n" : " ");
                }
                for (int k = 0; k < (int)edge.size(); ++k) {
                    printf("%d%s", edge[k].second, (k == (int)edge.size() - 1) ? "\n" : " ");
                }
                edge[i] = std::make_pair(x1, y1);
                edge[j] = std::make_pair(x2, y2);
                return;
            }
        }
    }
    puts("UNIQUE");
    printf("%d %d\n", n, (int)edge.size());
    for (int k = 0; k < (int)edge.size(); ++k) {
        printf("%d%s", edge[k].first, (k == (int)edge.size() - 1) ? "\n" : " ");
    }
    for (int k = 0; k < (int)edge.size(); ++k) {
        printf("%d%s", edge[k].second, (k == (int)edge.size() - 1) ? "\n" : " ");
    }
    if (edge.empty()) {
        puts("");
        puts("");
    }
}

void solve(void) {
    std::vector<std::pair<int, int> > value;

    for (int i = 1; i <= n; ++i) {
        int x;
        scanf("%d", &x);
        value.push_back(std::make_pair(x, i));
    }

    edge.clear();
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            graph[i][j] = false;
        }
    }

    if (!solve(value)) {
        puts("IMPOSSIBLE");
    } else {
        print();
    }
}

int main(void) {
    for (; ~scanf("%d", &n); solve());
}
