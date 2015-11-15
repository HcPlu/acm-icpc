#include<cstdio>
#include<cmath>
#include<cstdlib>

using namespace std;

double R, r1, r2, r3;

double calc(double x, double y) {
	double div = (x + y) / (x - y);
	double len = div * y;
	len += x + y;
	return sqrt(len * len - x * x);
}

void work() {
	double a = calc(R, r1);
	double b = calc(R, r2);
	double c = calc(R, r3);
	double sum = a + b + c;
	printf("%.2f\n", sqrt(sum * a) * sqrt(b * c));
}

int main() {
	int test = 0;
	while(1) {	
		scanf("%lf", &R);
		scanf("%lf%lf%lf", &r1, &r2, &r3);
		if(R < 0 && r1 < 0 && r2 < 0 && r3 < 0) break;
		printf("Case %d: ", ++test);
		work();
	}	
	return 0;
}
