#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>

#define SIZE(vec) ((int)vec.size())

using namespace std;
const double eps = 1e-8;
const double PI = acos(-1.);
int mark[222][222];
int n, cnt, father[22222];
double S[2222];

double sign(double x) {
    return x < -eps ? -1 : x > eps;
}

struct Point {
    double x, y, z;

    Point() {
    }

    Point(double x, double y, double z) : x(x), y(y), z(z) {
    }

    Point cross(const Point &p) const {
        return Point(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x);
    }

    double dot(const Point &p) const {
        return x * p.x + y * p.y + z * p.z;
    }

    double length() const {
        return sqrt(x * x + y * y + z * z);
    }

    Point unit() {
        double d = length();
        return Point(x / d, y / d, z / d);
    }

    void input() {
        scanf("%lf%lf%lf", &x, &y, &z);
    }

    friend Point operator -(const Point &a, const Point &b) {
        return Point(a.x - b.x, a.y - b.y, a.z - b.z);
    }

    friend Point operator +(const Point &a, const Point &b) {
        return Point(a.x + b.x, a.y + b.y, a.z + b.z);
    }

    friend Point operator *(const Point &a, const double &d) {
        return Point(a.x * d, a.y * d, a.z * d);
    }

    friend Point operator /(const Point &a, const double &d) {
        return Point(a.x / d, a.y / d, a.z / d);
    }

    friend double mix(const Point &a, const Point &b, const Point &c) {
        return a.dot(b.cross(c));
    }

    friend bool operator <(const Point &a, const Point &b) {
        double d = sign(a.x - b.x);
        if (d != 0) {
            return d < 0;
        } else {
            double dd = sign(a.y - b.y);
            if (dd != 0) {
                return dd < 0;
            } else {
                return sign(a.z - b.z) < 0;
            }
        }
    }

    friend bool operator ==(const Point &a, const Point &b) {
        return sign(a.x - b.x) == 0 && sign(a.y - b.y) == 0 && sign(a.z - b.z) == 0;
    }

    friend Point intersection(const Point &l1, const Point &l2, const Point &s1, const Point &s2, const Point &s3) {
        Point ret = l2 - l1;
        double t = (ret.x * (s1.x - l1.x) + ret.y * (s1.y - l1.y) + ret.z * (s1.z - l1.z)) /
                   (ret.x * (l2.x - l1.x) + ret.y * (l2.y - l1.y) + ret.z * (l2.z - l1.z));
        ret = l1 + (l2 - l1) * t;
        return ret;
    }
};

struct Point2 {
    double x, y;

    Point2() {
    }

    Point2(double x, double y) : x(x), y(y) {
    }

    friend Point2 operator -(const Point2 &a, const Point2 &b) {
        return Point2(a.x - b.x, a.y - b.y);
    }

    friend Point2 operator +(const Point2 &a, const Point2 &b) {
        return Point2(a.x + b.x, a.y + b.y);
    }

    friend double det(const Point2 &a, const Point2 &b) {
        return a.x * b.y - a.y * b.x;
    }

    friend double det(const Point2 &a, const Point2 &b, const Point2 &c) {
        return det(a - c, b - c);
    }

    friend bool operator <(const Point2 &a, const Point2 &b) {
        int d = sign(a.x - b.x);
        if (d != 0) {
            return d < 0;
        } else {
            return sign(a.y - b.y) < 0;
        }
    }
};

Point info[222];

double area(int a, int b, int c) {
    return ((info[b] - info[c]).cross(info[c] - info[a])).length();
}

double volume(int a, int b, int c, int d) {
    return mix(info[b] - info[a], info[c] - info[a], info[d] - info[a]);
}

struct Face {
    int a, b, c;

    Face() {
    }

    Face(int a, int b, int c) : a(a), b(b), c(c) {
    }

    int &operator [](int k) {
        return k == 0 ? a : k == 1 ? b : c;
    }
};

vector<Face> face;

inline void insert(int a, int b, int c) {
    face.push_back(Face(a, b, c));
}

void add(int v) {
    vector<Face> tmp;
    int a, b, c;
    cnt++;
    for (int i = 0; i < SIZE(face); i++) {
        a = face[i][0];
        b = face[i][1];
        c = face[i][2];
        if (sign(volume(v, a, b, c) < 0)) {
            mark[a][b] = mark[b][a] = mark[b][c] = mark[c][b] = mark[c][a] = mark[a][c] = cnt;
        } else {
            tmp.push_back(face[i]);
        }
    }

    face = tmp;

    for (int i = 0; i < SIZE(tmp); i++) {
        a = face[i][0];
        b = face[i][1];
        c = face[i][2];
        if (mark[a][b] == cnt) {
            insert(b, a, v);
        }
        if (mark[b][c] == cnt) {
            insert(c, b, v);
        }
        if (mark[c][a] == cnt) {
            insert(a, c, v);
        }
    }

}

int Find() {
    for (int i = 2; i < n; i++) {
        Point ndir = (info[0] - info[i]).cross(info[1] - info[i]);
        if (ndir == Point()) {
            continue;
        }
        swap(info[i], info[2]);
        for (int j = i + 1; j < n; j++) {
            if (sign(volume(0, 1, 2, j)) != 0) {
                swap(info[j], info[3]);
                insert(0, 1, 2);
                insert(0, 2, 1);
                return 1;
            }
        }

    }
    return 0;
}

int getfa(int x) {
    return x == father[x] ? x : father[x] = getfa(father[x]);
}

Point rotate(Point a, Point b, double angle) {
    Point e1, e2, e3;
    b = b.unit();
    e3 = b;
    double lens = a.dot(e3);
    e1 = a - e3 * lens;
    if (e1.length() > 1e-8) {
        e1 = e1.unit();
    } else {
        return a;
    }
    e2 = e1.cross(e3);
    double x1, y1, x, y;
    y1 = a.dot(e1);
    x1 = a.dot(e2);
    x = x1 * cos(angle) - y1 * sin(angle);
    y = x1 * sin(angle) + y1 * cos(angle);
    return e3 * lens + e1 * y + e2 * x;
}

vector<Point2> convex_hull(vector<Point2> point2) {
    sort(point2.begin(), point2.end());
    vector<Point2> convex;
    {
        vector<Point2> stack;
        for (int i = 0; i < (int)point2.size(); ++i) {
            while ((int)stack.size() >= 2 && sign(det(stack[(int)stack.size() - 2], stack.back(), point2[i])) <= 0) {
                stack.pop_back();
            }
            stack.push_back(point2[i]);
        }
        for (int i = 0; i < (int)stack.size(); ++i) {
            convex.push_back(stack[i]);
        }
    }
    {
        vector<Point2> stack;
        for (int i = (int)point2.size() - 1; i >= 0; --i) {
            while ((int)stack.size() >= 2 && sign(det(stack[(int)stack.size() - 2], stack.back(), point2[i])) <= 0) {
                stack.pop_back();
            }
            stack.push_back(point2[i]);
        }
        for (int i = 1; i < (int)stack.size() - 1; ++i) {
            convex.push_back(stack[i]);
        }
    }
    return convex;
}


double getarea(int to) {
    Point vec = (info[face[to][1]] - info[face[to][0]]).cross(info[face[to][2]] - info[face[to][0]]);
    vector<Point> point;
    for (int i = 0; i < n; i++) {
        Point p1 = info[i];
        Point p2 = info[i] + vec;
        point.push_back(intersection(p1, p2, info[face[to][0]], info[face[to][1]], info[face[to][2]]));
    }

    vector<Point2> point2;
    sort(point.begin(), point.end());

    point.erase(unique(point.begin(), point.end()), point.end());
    point2.push_back(Point2(0., 0.));
    Point dirx = point[1] - point[0];
    Point diry = rotate(dirx, vec, PI / 2);
    dirx = dirx.unit();
    diry = diry.unit();
    for (int i = 1; i < (int)point.size(); i++) {
        Point dir = point[i] - point[0];
        double x = dir.dot(dirx);
        double y = dir.dot(diry);
        point2.push_back(Point2(x, y));
    }

    vector<Point2> convex = convex_hull(point2);
    double ret = 0;
    for (int i = 0; i < (int)convex.size(); i++) {
        ret += det(convex[i], convex[(i + 1) % (int)convex.size()], convex[0]);
    }
    ret = fabs(ret);
    return ret / 2;
}

pair<double, double> getanswer(int vertex, int to) {
    double dist = fabs(volume(vertex, face[to][0], face[to][1], face[to][2])) /
                  fabs(area(face[to][0], face[to][1], face[to][2]));
    double now_area = getarea(to);
    return make_pair(dist, -now_area);
}

void get_convex() {
    sort(info, info + n);
    n = unique(info, info + n) - info;
    face.clear();
    random_shuffle(info, info + n);
    if (Find()) {
        memset(mark, 0, sizeof mark);
        cnt = 0;
        for (int i = 3; i < n; i++)
            add(i);
    }
}

void solve() {
    for (int i = 0; i < n; i++) {
        info[i].input();
    }

    get_convex();
    memset(S, 0, sizeof S);

    pair<double, double> answer = make_pair(-1., -1.);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < SIZE(face); j++) {
            answer = max(answer, getanswer(i, j));
        }
    }
    printf("%.3f %.3f\n", answer.first, -answer.second);
}

int main() {
    for (; scanf("%d", &n) && n; solve());
}

