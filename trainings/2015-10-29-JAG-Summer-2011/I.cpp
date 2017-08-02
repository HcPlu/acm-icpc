#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

const double eps = 1e-7;
const double g = 9.8;
const double PI = acos(-1);
vector<pair<int, pair<int, int> > > horizontal, vertical;

int n, v, targetx, targety;
int limit = 1 << 29;

bool check(double theta) {
    double cosa = cos(theta);
    double sina = sin(theta);
    double A = sina / cosa;
    double B = -.5 * g / cosa / cosa / v / v;

    bool collide = false;
    for (int i = 0; i < (int)vertical.size(); i++) {
        if (vertical[i].first > targetx) {
            break;
        }
        double x = vertical[i].first;
        double y = B * x * x + A * x;
        if (y < vertical[i].second.first + eps && y > vertical[i].second.second - eps) {
            collide = true;
            break;
        }
    }

    for (int i = 0; i < (int)horizontal.size(); i++) {
        if (horizontal[i].second.first > targetx) {
            break;
        }

        double y = horizontal[i].first;
        double delta = A * A + 4 * B * y;
        if (delta < 0 && delta > -eps) {
            delta = 0;
        }
        if (delta < -eps) {
            continue;
        }

        double x1 = (-A + sqrt(max(delta, 0.))) / 2 / B;
        double x2 = (-A - sqrt(max(delta, 0.))) / 2 / B;

        if (x1 < horizontal[i].second.second + eps && x1 > horizontal[i].second.first) {
            if (x1 < targetx + eps) {
                collide = true;
                break;
            }
        }

        if (x2 < horizontal[i].second.second + eps && x2 > horizontal[i].second.first) {
            if (x2 < targetx + eps) {
                collide = true;
                break;
            }
        }

    }
    if (collide) {
        return false;
    }

    double y = B * targetx * targetx + A * targetx;
    if (y < targety + eps) {
        return false;
    }
    if (y > limit - eps) {
        return false;
    }
    return true;
}

bool cmp(pair<int, pair<int, int> > p1, pair<int, pair<int, int> > p2) {
    return p1.second.first < p2.second.first;
}

int main() {
    scanf("%d%d%d%d", &n, &v, &targetx, &targety);
    for (int i = 1; i <= n; i++) {
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        vertical.push_back(make_pair(x1, make_pair(y2, y1)));
        vertical.push_back(make_pair(x2, make_pair(y2, y1)));
        horizontal.push_back(make_pair(y1, (make_pair(x1, x2))));
        horizontal.push_back(make_pair(y2, (make_pair(x1, x2))));
        if (x1 <= targetx && x2 >= targetx && y1 > targety) {
            limit = min(limit, y1);
        }
        if (x1 <= targetx && x2 >= targetx && y2 > targety) {
            limit = min(limit, y2);
        }
    }

    sort(vertical.begin(), vertical.end());
    sort(horizontal.begin(), horizontal.end(), cmp);

    double step = PI / 2 / 1e6;
    double theta = 0;
    bool find = false;
    for (; theta < PI + eps; theta += step) {
        if (check(theta)) {
            puts("Yes");
            find = true;
            break;
        }
    }

    if (!find) {
        puts("No");
    }
    return 0;
}
