#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;
const double eps = 1e-8;
struct Point{
	double x, y;
	Point() {}
	Point(double x, double y) : x(x), y(y) {}
	
	double length() const{
		return sqrt(x * x + y * y);
	}
	double norm() const{
		return length(); 
	}
	double norm2() const{
		return (x * x + y * y);
	}
	friend double det(const Point &a, const Point &b) {
		return a.x * b.y - a.y * b.x;
	}
	friend double dot(const Point &a, const Point &b) {
		return a.x * b.x + a.y * b.y;
	}
	
	friend Point operator - (const Point &a, const Point &b) {	
		return Point(a.x - b.x, a.y - b.y);
	}
	friend Point operator + (const Point &a, const Point &b) {
		return Point(a.x + b.x, a.y + b.y);
	}
	
	Point unit() {
		double d = norm();
		return Point(x / d, y / d);
	}
	friend double dist(const Point &a, const Point &b) {
		return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
	}
	
	friend Point operator * (const Point &a, const double &t)  {
		return Point(a.x * t, a.y * t);
	}
	friend Point operator / (const Point &a, const double &t) {
		return Point(a.x / t, a.y / t);
	}	
};

struct Line {
	Point s, t;
	Line() {}
	Line(Point s, Point t) : s(s), t(t) {}
	inline double length() {
		return dist(s, t);
	}
};

struct Circle {
	Point center;
	double radius;
	Circle() {}
	Circle(Point center, double radius) : center(center), radius(radius) {}
};

double sqr(double x) {
	return x * x;
}

Point project_to_line(const Point &p, const Line &l) {
	return l.s + (l.t - l.s) * (dot(p - l.s, l.t - l.s) / (l.t - l.s).norm2());	
}

double point_to_line(const Point &p, const Line &l) {
	return fabs(det(l.t - l.s, p - l.s)) / dist(l.s, l.t);
}

Point intersect(const Line &l, const Circle &c) {
	double x = sqrt(sqr(c.radius) - sqr(point_to_line(c.center, l)));
	return project_to_line(c.center, l) + (l.s - l.t).unit() * x;
}

double x, y, vx, vy, radiusM, radiusR, radius;
void solve() {
	radiusM += radius;
	radiusR += radius;

	Point p1 = Point(x, y);
	Point p2 = Point(vx + x, vy + y);
	
	Line line = Line(p1, p2);
	double dis = point_to_line(Point(0., 0.), line);
	double answer;
	if (dis > radiusR - eps) {
		answer = 0;
		printf("%.3f\n", answer);
		return;
	}
	if (dis > radiusM - eps) {
		Circle circleR = Circle(Point(0., 0.), radiusR);
		Point cross = intersect(line, circleR);
		if (dot(line.t - line.s, cross - line.s) < -eps) {
			puts("0.000");
			return;
		}
		answer = sqrt(radiusR * radiusR - dis * dis) * 2 / (sqrt(vx * vx + vy * vy));
		printf("%.3f\n", answer);
		return;
	}
	
	Circle circleR = Circle(Point(0., 0.), radiusR);
	Circle circleM = Circle(Point(0., 0.), radiusM);
	
	Point cross1 = intersect(line, circleR);
	Point cross2 = intersect(line, circleM);
	if (dot(line.t - line.s, cross1 - line.s) < -eps) {
		puts("0.000");
		return;
	}
	
	answer = dist(cross1, cross2) / sqrt(vx * vx + vy * vy);
	
	printf("%.3f\n", answer * 2); 
			
}

int main() {
	for (; ~scanf("%lf%lf%lf%lf%lf%lf%lf", &radiusM, &radiusR, &radius, &x, &y, &vx, &vy); solve());
	return 0;
}
