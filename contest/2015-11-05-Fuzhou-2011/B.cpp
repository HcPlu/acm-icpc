#include <iostream>
#include <map>
#include <vector>

using namespace std;
const int N = 3333;
int n, m;
pair<int, int> quest[N];
long long f[211111];
int a[211111];

int gethour(int month, int day, int year, int hour) {
    int number = (year - 1) * 365;
    number += (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400;
    for (int i = 1; i < month; i++) {
        if (i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12) {
            number += 31;
        } else {
            if (i == 2) {
                if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
                    number += 29;
                } else {
                    number += 28;
                }
            } else {
                number += 30;
            }
        }
    }
    number += day;
    int ret = number * 24;
    ret -= (24 - hour);
    return ret;
}

int limit, cost;

void solve() {
    map<string, int> mat;
    mat["Jan"] = 1;
    mat["Feb"] = 2;
    mat["Mar"] = 3;
    mat["Apr"] = 4;
    mat["May"] = 5;
    mat["Jun"] = 6;
    mat["Jul"] = 7;
    mat["Aug"] = 8;
    mat["Sep"] = 9;
    mat["Oct"] = 10;
    mat["Nov"] = 11;
    mat["Dec"] = 12;

    for (int i = 1; i <= n; i++) {
        static char month[11];
        static int day, year, hour, number;
        scanf("%s%d%d%d%d", month, &day, &year, &hour, &number);
        string text = month;
        quest[i] = make_pair(gethour(mat[text], day, year, hour) - gethour(1, 1, 2000, 0), number);
    }
    scanf("%d%d", &limit, &cost);
    limit--;
    for (int i = 0; i < m; i++) {
        scanf("%d", &a[i]);
    }


    f[0] = 0;
    vector<int> stack;
    int head = 0;
    int last = 0;

    for (int i = 1; i <= n; i++) {
        int date = quest[i].first;
        if (head < (int)stack.size()) {
            for (; head < (int)stack.size() && date - stack[head] > limit; head++);
        }
        for (; last + limit < date; last++);
        for (; last <= date; last++) {
            while (stack.size() - head > 0 && 1LL * a[last] + 1LL * (date - last) * cost <
                                              1LL * a[stack.back()] + 1LL * (date - stack.back()) * cost) {
                stack.pop_back();
            }
            stack.push_back(last);
        }
        f[i] = f[i - 1] + 1LL * quest[i].second * (1LL * a[stack[head]] + 1LL * (date - stack[head]) * cost);
    }

    cout << f[n] << endl;
}

int main() {
    for (; scanf("%d%d", &n, &m) && (n || m); solve());
    return 0;
}
