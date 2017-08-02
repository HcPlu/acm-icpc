#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>
#include <set>
#include <map>

using namespace std;

const int N = 11;
const int NN = 555;

int n, m;
char source[N][N], target[N][N], curr[N][N];
double num[NN][NN], constant[NN];
vector<int> states;
int relate[111111];

inline int encode(vector<int> &state) {
    int hash = 0;
    for (int i = 1; i <= n; ++i) {
        hash = hash * (m + 1) + state[i];
    }
    return hash;
}

inline vector<int> decode(int hash) {
    vector<int> ret;
    for (int i = 1; i <= n; ++i) {
        ret.push_back(hash % (m + 1));
        hash /= (m + 1);
    }
    ret.push_back(0);
    reverse(ret.begin(), ret.end());
    return ret;
}

inline int calc(char info[N][N]) {
    vector<int> ret;
    for (int i = n, j = 0; i >= 1; --i) {
        int k = m;
        while (k && info[i][k] == target[i][k]) {
            k--;
        }
        j = max(j, k);
        ret.push_back(j);
    }
    ret.push_back(0);
    reverse(ret.begin(), ret.end());
    return relate[encode(ret)];
}

inline void dfs(vector<int> state) {
    if ((int)state.size() == n + 1) {
        states.push_back(encode(state));
        return;
    }

    for (int i = 0; i <= state.back(); ++i) {
        state.push_back(i);
        dfs(state);
        state.pop_back();
    }
}

inline void solve() {
    states.clear();
    dfs(vector<int>(1, m));
    sort(states.begin(), states.end());
    for (int i = 0; i < (int)states.size(); ++i) {
        relate[states[i]] = i;
    }

    for (int i = 1; i <= n; ++i) {
        scanf("%s", source[i] + 1);
    }
    for (int i = 1; i <= n; ++i) {
        scanf("%s", target[i] + 1);
    }

    int nn = (int)states.size();
    for (int i = 0; i < nn; ++i) {
        for (int j = 0; j < nn; ++j) {
            num[i][j] = 0;
        }
        constant[i] = 0;
    }
    for (int i = 1; i < nn; ++i) {
        vector<int> state = decode(states[i]);
        num[i][i] = 1;
        for (int j = 1; j <= n; ++j) {
            for (int k = 1; k <= m; ++k) {
                for (int col = 0; col < 2; ++col) {
                    for (int x = 1; x <= n; ++x) {
                        for (int y = 1; y <= m; ++y) {
                            curr[x][y] = target[x][y];
                        }
                    }
                    for (int x = 1; x <= n; ++x) {
                        for (int y = 1; y <= state[x]; ++y) {
                            curr[x][y] = 'x';
                        }
                    }
                    for (int x = 1; x <= j; ++x) {
                        for (int y = 1; y <= k; ++y) {
                            curr[x][y] = col ? 'B' : 'W';
                        }
                    }
                    num[i][calc(curr)] -= 0.5 / n / m;
                    constant[i] += 0.5 * (j * k) / n / m;
                }
            }
        }
    }

    num[0][0] = 1;

    for (int i = 0; i < nn; ++i) {
        int k = i;
        for (int j = i; j < nn; ++j) {
            if (fabs(num[j][i]) > fabs(num[k][i])) {
                k = j;
            }
        }
        if (k != i) {
            swap(constant[i], constant[k]);
            for (int j = 0; j < nn; ++j) {
                swap(num[i][j], num[k][j]);
            }
        }
        for (int j = 0; j < nn; ++j) {
            if (j == i) {
                continue;
            }
            double coe = num[j][i] / num[i][i];
            for (int k = 0; k < nn; ++k) {
                num[j][k] -= num[i][k] * coe;
            }
            constant[j] -= constant[i] * coe;
        }
    }

    int idx = calc(source);
    printf("%.10f\n", constant[idx] / num[idx][idx]);
}

int main() {
    for (; ~scanf("%d%d", &n, &m) && n + m; solve());
    return 0;
}
