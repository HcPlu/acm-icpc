#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    scanf("%d", &n);
    n--;
    vector<int> answer;
    for (int i = 1; 1LL * i * i <= n; i++) {
        if (n % i == 0) {
            answer.push_back(i);
            if (i * i != n) {
                answer.push_back(n / i);
            }
        }
    }

    sort(answer.begin(), answer.end());

    for (int i = 0; i < (int)answer.size(); i++) {
        printf("%d ", answer[i]);
    }
    puts("");
}
