#include <iostream>
#include <cmath>


using namespace std;
const long double eps = 1e-10;
const long double pi = acos((long double)-1.);

double width, height, sa, sb, area;

int sign(long double x) {
    return x < -eps ? -1 : x > eps;
}

struct Point {
    double x, y;

    Point() {
    }

    Point(double x, double y) : x(x), y(y) {
    }

    friend long double dot(const Point &a, const Point &b) {
        return a.x * b.x + a.y * b.y;
    }

    friend long double det(const Point &a, const Point &b) {
        return a.x * b.y - a.y * b.x;
    }

    friend long double dist(const Point &a, const Point &b) {
        return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    }

    friend Point operator -(const Point &a, const Point &b) {
        return Point(a.x - b.x, a.y - b.y);
    }

    friend Point operator /(const Point &a, const long double &x) {
        return Point(a.x / x, a.y / x);
    }
};

void solve() {
    int flg = 0;
    if (sa < sb) {
        swap(sa, sb);
        flg = 1;
    }

    long double radiusa = sqrt(sa / pi);
    long double radiusb = sqrt(sb / pi);
    if (2 * radiusa - width > 2 * 1e-4 || 2 * radiusa - height > 2 * 1e-4 || 2 * radiusb - width > 2 * 1e-4 ||
        2 * radiusb - height > 2 * 1e-4) {
        puts("impossible");
        return;
    }

    Point oa = Point(radiusa, radiusa);
    Point ob = Point(width - radiusb, height - radiusb);
    long double maxdist = dist(oa, ob);
    if (maxdist < eps) {
        if (sign(sb - area) != 0) {
            puts("impossible");
        } else {
            double xa = oa.x;
            double ya = oa.y;
            double xb = oa.x;
            double yb = oa.y;
            if (flg) {
                printf("%.9f %.9f %.9f %.9f %.9f %.9f\n", xb, yb, (double)radiusb, xa, ya, (double)radiusa);
            } else {
                printf("%.9f %.9f %.9f %.9f %.9f %.9f\n", xa, ya, (double)radiusa, xb, yb, (double)radiusb);
            }
        }
        return;
    }

    Point norm = (ob - oa) / maxdist;
    if (sb < area - eps) {
        puts("impossible");
        return;
    }

    long double l = 0, r = min(maxdist, radiusa + radiusb);
    int times = 80;
    long double ans = -999;

    while (times--) {
        long double mid = (l + r) / 2;
        long double cosb = (radiusb * radiusb + mid * mid - radiusa * radiusa) / (2 * radiusb * mid);
        long double angleb = 2 * acos(cosb);
        long double sinb = 2 * cosb * sqrt(1 - cosb * cosb);

        long double cosa = (radiusa * radiusa + mid * mid - radiusb * radiusb) / (2 * radiusa * mid);
        long double anglea = 2 * acos(cosa);
        long double sina = 2 * cosa * sqrt(1 - cosa * cosa);
        long double now = sa * anglea / 2 / pi - radiusa * radiusa * sina / 2 + sb * angleb / 2 / pi -
                          radiusb * radiusb * sinb / 2;
        if (mid < radiusa - radiusb + eps) {
            now = sb;
        }
        int d = sign(now - area);
        if (d > 0) {
            l = mid;
        } else {
            if (d < 0) {
                r = mid;
            } else {
                ans = mid;
                break;
            }
        }
    }

    if (ans < -eps) {
        puts("impossible");
    } else {
        double xa = oa.x;
        double ya = oa.y;
        double xb = oa.x + ans * norm.x;
        double yb = oa.y + ans * norm.y;
        if (flg) {
            printf("%.9f %.9f %.9f %.9f %.9f %.9f\n", xb, yb, (double)radiusb, xa, ya, (double)radiusa);
        } else {
            printf("%.9f %.9f %.9f %.9f %.9f %.9f\n", xa, ya, (double)radiusa, xb, yb, (double)radiusb);
        }
    }
}

int main() {
    for (; scanf("%lf%lf%lf%lf%lf", &width, &height, &sa, &sb, &area) &&
           (width + height + sa + sb + area > eps); solve());
}
