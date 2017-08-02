#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

const int mod = 1e9 + 7;
const int N = 111;

int n, m, k;
std::pair<int, int> graph[N][N];
int degree[N], item[N][N], data[N], father[N];

int find(int x) {
    if (father[x] != x) {
        father[x] = find(father[x]);
    }
    return father[x];
}

void merge(int x, int y) {
    x = find(x);
    y = find(y);
    father[x] = y;
}

long long pow(const long long &x, const long long &k) {
    long long answer = 1, number = x;
    for (long long i = k; i > 0; i >>= 1) {
        if (i & 1) {
            (answer *= number) %= mod;
        }
        (number *= number) %= mod;
    }
    return answer;
}

void fix(int &x) {
    x %= mod;
    x += mod;
    x %= mod;
}

int inverse(int x) {
    fix(x);
    return pow(x, mod - 2);
}

class Equation {
public:
    int item[N];

    Equation() {
        memset(item, 0, sizeof(item));
    }

    friend Equation operator *(const Equation &a, const Equation &b) {
        Equation c;
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= i; ++j) {
                c.item[i] += 1LL * a.item[j] * b.item[i - j] % mod;
                fix(c.item[i]);
            }
        }
        return c;
    }

    friend Equation operator +(const Equation &a, const Equation &b) {
        Equation c;
        for (int i = 0; i <= n; ++i) {
            c.item[i] = a.item[i] + b.item[i];
            fix(c.item[i]);
        }
        return c;
    }
};

int calc() {
    int answer = 1;
    /*
        puts("");

        for (int i = 1; i <= n; ++i, puts("")) {
            for (int j = 1; j <= n; ++j, putchar(' ')) {
                printf("%d", item[i][j]);
            }
        }

        puts("");
    */
    for (int i = 1; i <= n - 1; ++i) {
        int k = i;
        for (int j = i + 1; j <= n - 1; ++j) {
            if (std::abs(item[j][i]) > std::abs(item[k][i])) {
                k = j;
            }
        }
        if (k != i) {
            answer = -answer;
            for (int j = 1; j <= n - 1; ++j) {
                std::swap(item[i][j], item[k][j]);
            }
        }
        for (int j = i + 1; j <= n - 1; ++j) {
            int coefficient = 1LL * item[j][i] * inverse(item[i][i]) % mod;
            for (int k = 1; k <= n - 1; ++k) {
                item[j][k] -= 1LL * item[i][k] * coefficient % mod;
                fix(item[j][k]);
            }
        }
    }
    /*
        puts("");

        for (int i = 1; i <= n - 1; ++i, puts("")) {
            for (int j = 1; j <= n - 1; ++j, putchar(' ')) {
                printf("%d", item[i][j]);
            }
        }

        puts("");
    */
    for (int i = 1; i <= n - 1; ++i) {
        answer = 1LL * answer * item[i][i] % mod;
    }
    fix(answer);
    return answer;
}

void solve(void) {
    scanf("%d%d%d", &n, &m, &k);

    for (int i = 1; i <= n; ++i) {
        degree[i] = 0;
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            graph[i][j] = std::make_pair(0, 0);
        }
    }

    for (int i = 1; i <= n; ++i) {
        father[i] = i;
    }

    for (int i = 1; i <= m; ++i) {
        int x, y, w;
        scanf("%d%d%d", &x, &y, &w);

        if (w == 1) {
            graph[x][y] = graph[y][x] = std::make_pair(1, 0);
        } else if (w == 2) {
            graph[x][y] = graph[y][x] = std::make_pair(0, 1);
        } else {
            graph[x][y] = graph[y][x] = std::make_pair(1, 1);
        }
        degree[x]++;
        degree[y]++;

        merge(x, y);
    }

    for (int i = 1; i <= n; ++i) {
        if (find(i) != find(1)) {
            puts("0");
            return;
        }
    }

    for (int val = 1; val <= n; ++val) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (i == j) {
                    item[i][i] = 0;
                    for (int k = 1; k <= n; ++k) {
                        if (k != i) {
                            item[i][i] += (graph[i][k].first * val + graph[i][k].second);
                        }
                    }
                } else {
                    item[i][j] = -(graph[i][j].first * val + graph[i][j].second);
                }
            }
        }
        data[val] = calc();
    }

    Equation answer;

    for (int i = 1; i <= n; ++i) {
        int coefficient = data[i];
        for (int j = 1; j <= n; ++j) {
            if (j != i) {
                coefficient = 1LL * coefficient * inverse(i - j) % mod;
            }
        }
        Equation temp;
        temp.item[0] = coefficient;

        for (int j = 1; j <= n; ++j) {
            if (j != i) {
                Equation item;
                item.item[0] = -j;
                item.item[1] = 1;
                temp = temp * item;
            }
        }

        answer = answer + temp;
    }

    int result = 0;
    for (int i = 0; i <= k; ++i) {
        result += answer.item[i];
        fix(result);
    }

    printf("%d\n", result);
}

int main(void) {
    int tests;
    scanf("%d", &tests);
    for (int i = 1; i <= tests; ++i) {
        printf("Case #%d: ", i);
        solve();
    }
}
