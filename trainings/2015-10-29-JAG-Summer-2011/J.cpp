#include <cstdio>
#include <algorithm>
#include <cmath>

const int N = 111;

double sqr(const double &x) {
    return x * x;
}

int m;

class Vector {
public:
    double item[N];

    Vector() {
        for (int i = 1; i <= m; ++i) {
            item[i] = 0;
        }
    }

    Vector(const Vector &other) {
        *this = other;
    }

    Vector &operator =(const Vector &other) {
        if (this == &other) {
            return *this;
        }
        for (int i = 1; i <= m; ++i) {
            item[i] = other.item[i];
        }
        return *this;
    }

    friend double operator *(const Vector &a, const Vector &b) {
        double answer = 0;
        for (int i = 1; i <= m; ++i) {
            answer += a.item[i] * b.item[i];
        }
        return answer;
    }

    friend Vector operator -(const Vector &a, const Vector &b) {
        Vector answer;
        for (int i = 1; i <= m; ++i) {
            answer.item[i] = a.item[i] - b.item[i];
        }
        return answer;
    }

    friend Vector operator *(const Vector &a, const double &k) {
        Vector answer;
        for (int i = 1; i <= m; ++i) {
            answer.item[i] = a.item[i] * k;
        }
        return answer;
    }

    friend Vector operator /(const Vector &a, const double &k) {
        Vector answer;
        for (int i = 1; i <= m; ++i) {
            answer.item[i] = a.item[i] / k;
        }
        return answer;
    }

    double norm() const {
        double answer = 0;
        for (int i = 1; i <= m; ++i) {
            answer += item[i] * item[i];
        }
        return sqrt(answer);
    }

    void read() {
        for (int i = 1; i <= m; ++i) {
            scanf("%lf", item + i);
        }
    }
};

int n;
int used[N], pass[N], eg[N], more, queue[N];
double g[N][N];
Vector vector[N];

void combine(int id, double &sum) {
    int tot = 0, from, i, j, k;
    for (; id != 0 && !pass[id]; id = eg[id]) {
        queue[tot++] = id;
        pass[id] = 1;

    }
    for (from = 0; from < tot && queue[from] != id; from++) {
    }
    if (from == tot) {
        return;
    }
    more = 1;
    for (i = from; i < tot; ++i) {
        sum += g[eg[queue[i]]][queue[i]];
        if (i != from) {
            used[queue[i]] = 1;
            for (j = 1; j <= n; ++j) {
                if (!used[j]) {
                    if (g[queue[i]][j] < g[id][j]) {
                        g[id][j] = g[queue[i]][j];
                    }
                }
            }
        }
    }
    for (i = 1; i <= n; ++i) {
        if (!used[i] && i != id) {
            for (j = from; j < tot; ++j) {
                k = queue[j];
                if (g[i][id] > g[i][k] - g[eg[k]][k]) {
                    g[i][id] = g[i][k] - g[eg[k]][k];
                }
            }
        }
    }
}

double mdst(int root) {
    int i, j, k;
    double sum = 0;
    memset(used, 0, sizeof(used));
    for (more = 1; more;) {
        more = 0;
        memset(eg, 0, sizeof(eg));
        for (i = 1; i <= n; ++i) {
            if (!used[i] && i != root) {
                for (j = 1, k = 0; j <= n; ++j) {
                    if (!used[j] && i != j) {
                        if (k == 0 || g[j][i] < g[k][i]) {
                            k = j;
                        }
                    }
                }
                eg[i] = k;
            }
        }
        memset(pass, 0, sizeof(pass));
        for (i = 1; i <= n; ++i) {
            if (!used[i] && !pass[i] && i != root) {
                combine(i, sum);
            }
        }
    }
    for (i = 1; i <= n; ++i) {
        if (!used[i] && i != root) {
            sum += g[eg[i]][i];
        }
    }
    return sum;
}

int main(void) {
    scanf("%d%d", &m, &n);
    n++;

    vector[1] = Vector();
    for (int i = 2; i <= n; ++i) {
        vector[i].read();
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (i == j) {
                continue;
            }
            if (std::abs(vector[i].norm()) < 1e-6) {
                g[i][j] = sqr(vector[j].norm());
            } else {
                double dot = vector[i] * vector[j] / vector[i].norm();
                g[i][j] = sqr((vector[j] - vector[i] / vector[i].norm() * dot).norm());
            }
        }
    }
    printf("%.10f\n", mdst(1));
}
