#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

long long fib[100];

vector<int> ans;
long long n;

void work() {
    long long temp = n;
    ans.clear();
    for (int i = 90; i >= 1; i--) {
        if (fib[i] <= n) {
            ans.push_back(i);
            n -= fib[i];
        }
    }
    cout << temp << endl;
    for (int i = 0; i < ans.size(); i++) {
        if (i + 1 != ans.size()) {
            cout << ans[i] << " ";
        } else {
            cout << ans[i] << "\n";
        }
    }

    for (int i = 0; i < ans.size(); i++) {
        if (i + 1 != ans.size()) {
            cout << fib[ans[i]] << " ";
        } else {
            cout << fib[ans[i]] << "\n";
        }
    }
    puts("");
}

int main(void) {
    fib[0] = fib[1] = 1;
    for (int i = 2; i <= 90; ++i) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }
    while (cin >> n) {
        work();
    }
    return 0;
}
