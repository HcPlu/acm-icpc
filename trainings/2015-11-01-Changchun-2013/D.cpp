#include <iostream>
#include <cmath>

#define left ____left
#define right ____right

using namespace std;

const long double eps = 1e-9;

int sign(long double x) {
    return x < -eps ? -1 : x > eps;
}

const int N = 222222;

int n, L;
pair<long double, long double> point[N];
long double k[N], b[N];
int tp[N], d;

void fix(pair<int, long double> &state) {
    int now = state.first;
    int next = state.first + 1;
    if (point[now].first + state.second > point[next].first - eps) {
        state.first++;
        state.second = 0;
    }
}

void solve() {
    scanf("%d%d", &n, &L);
    for (int i = 1; i <= n; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        point[i].first = 1. * x;
        point[i].second = 1. * y;
    }
    point[n + 1] = point[n];
    for (int i = 1; i < n; i++) {
        k[i] = (point[i + 1].second - point[i].second) / (point[i + 1].first - point[i].first);
        b[i] = -(k[i] * point[i].first - point[i].second);
    }

    scanf("%d", &d);

    long double area_left = 0, area_right = 0;

    pair<int, long double> left_state;
    pair<int, long double> right_state;

    left_state = make_pair(1, 0.);

    for (int i = 1; i <= n; i++) {
        if (point[i + 1].first > point[1].first + 2 * d - eps) {
            long double rest = point[1].first + 2 * d - point[i].first;
            area_right += fabs((rest * k[i] + point[i].second * 2) * rest) / 2;
            right_state = make_pair(i, 2 * d + point[1].first - point[i].first);
            break;
        } else {
            area_right += fabs((point[i + 1].first - point[i].first) * (point[i].second + point[i + 1].second)) / 2;
        }
    }

    long double answer = 0;

    for (; point[left_state.first].first + left_state.second < L + eps && left_state.first < n &&
           right_state.first < n;) {
        fix(left_state);
        fix(right_state);
        int left = left_state.first;
        int right = right_state.first;
        answer = max(answer, area_right - area_left);
        long double stepl = point[left + 1].first - point[left].first - left_state.second;
        long double stepr = point[right + 1].first - point[right].first - right_state.second;
        long double step = min(stepl, stepr);
        if (left != right) {
            long double k1 = k[left], k2 = k[right];
            long double b1 = point[left].second + k1 * left_state.second, b2 =
                    point[right].second + k2 * right_state.second;
            if (sign(k1 - k2) != 0) {
                long double x = (b2 - b1) / (k1 - k2);
                if (x > -eps && x < step + eps) {
                    long double height1 = left_state.second * k1 + point[left].second;
                    long double area1 = area_left + fabs((height1 * 2 + k1 * x) * x) / 2;
                    long double height2 = right_state.second * k2 + point[right].second;
                    long double area2 = area_right + fabs((height2 * 2 + k2 * x) * x) / 2;
                    answer = max(answer, area2 - area1);
                }
            }
        }

        long double heightl = left_state.second * k[left] + point[left].second;
        long double heightr = right_state.second * k[right] + point[right].second;
        area_left += fabs((heightl * 2 + step * k[left]) * step) / 2;
        area_right += fabs((heightr * 2 + step * k[right]) * step) / 2;
        left_state.second += step;
        right_state.second += step;
    }

    printf("%.3f\n", (double)answer / (2 * d * 1.));
}

int main() {
    int tests;
    scanf("%d", &tests);
    for (int i = 1; i <= tests; i++) {
        solve();
    }
    return 0;
}
