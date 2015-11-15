#include <cstdio>
#include <cassert>
#include <algorithm>
#include <vector>
#include <set>

const int N = 1111111;

int n, m, k;
std::vector<int> edge[N];
int degree[N];

int main(void) {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= m; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        edge[x].push_back(y);
        degree[y]++;
    }
    
    std::vector<int> result;
    std::vector<std::pair<int, int> > edges;

    std::set<int> seta, setb;
    for (int i = 1; i <= n; ++i) {
        if (degree[i] == 0) {
            seta.insert(i);
        }
    }
    
    while (!seta.empty() || !setb.empty()) {
        if (seta.empty()) {
            int x = *setb.rbegin();
            setb.erase(x);
            
assert(!result.empty());
            
            edges.push_back(std::make_pair(result.back(), x));
            result.push_back(x);

            for (int i = 0; i < (int)edge[x].size(); ++i) {
                int y = edge[x][i];
                if (--degree[y] == 0) {
                    seta.insert(y);
                }
            }
        } else {
            int w = *seta.rbegin();
            if (!setb.empty()) {
                w = std::max(w, *setb.rbegin());
            }
            
            int x = *seta.begin();
            seta.erase(x);
            
            if (k <= 0 || x == w) {
                result.push_back(x);
                
                for (int i = 0; i < (int)edge[x].size(); ++i) {
                    int y = edge[x][i];
                    if (--degree[y] == 0) {
                        seta.insert(y);
                    }
                }
            } else {
                setb.insert(x);
                k--;
            }
        }
    }
    
    for (int i = 0; i < (int)result.size(); ++i) {
        printf("%d%s", result[i], (i == (int)result.size() - 1) ? "\n" : " ");
    }
    printf("%d\n", (int)edges.size());
    for (int i = 0; i < (int)edges.size(); ++i) {
        printf("%d %d\n", edges[i].first, edges[i].second);
    }
}
