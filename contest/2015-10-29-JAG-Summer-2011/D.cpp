#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstring>

using namespace std;

const int N = 105;
const double eps = 1e-8;
double C[N][N];

int n, m;
double p[N], t[N], v[N];
double f[N][N];
double P[N][N];

int main() {
	double l;
	scanf("%d%d%lf", &n, &m, &l);
	for(int i = 1; i <= n; i++)
		scanf("%lf%lf%lf", &p[i], &t[i], &v[i]);		
	for(int i = 1; i <= n; i++) {
		p[i] /= 100.;
	}
	C[1][1] = 1.;
	for(int i = 2; i <= m + 1; i++) {
		C[i][1] = 1.; C[i][i] = 1.;
		for(int j = 2; j < i; j++)
			C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
	}
	
	for(int i = 1; i <= n; i++) {
		f[i][0] = 1.;
		for(int j = 1; j <= m; j++) {
			f[i][j] = f[i][j - 1] * p[i];
		}
		double res = 1.;
		for(int j = m; j >= 0; j--) {
			f[i][j] *= res;
			res *= (1. - p[i]);
		}
	}
	
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++) {
			f[i][j] = f[i][j] * C[m + 1][j + 1];
		}
	
	for(int i = 1; i <= n; i++) {
		for(int j = m; j >= 0; j--) {
			P[i][j] = P[i][j + 1] + f[i][j];
		}
	}
		
	for(int i = 1; i <= n; i++) {
		double ans = 0.;
		for(int j = 0; j <= m; j++) {
			double result = 1.;
			if(fabs(v[i]) < eps) {
				result = 0.;
			} else {
				for(int k = 1; k <= n; k++) {
					if(i == k) continue;
					if(fabs(v[k]) < eps) continue;
					double need = l / v[i] - l / v[k];
					need += t[i] * j;
					int times;
					if(t[k] != 0) {
						times = (int)floor(need / t[k]) + 1;
					} else {
						if(need < -eps) {
							times = 0;
						} else {
							times = m + 2;
						}
					}
					times = max(times, 0);
					times = min(times, m + 1);
					result *= P[k][times];
				}
			}
			ans += f[i][j] * result;
		}
		printf("%.8f\n", ans);
	}
	return 0;
}
