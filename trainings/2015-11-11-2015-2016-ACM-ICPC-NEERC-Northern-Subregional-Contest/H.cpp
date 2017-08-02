#include<cstdio>

using namespace std;

const int N = 1005;

char str[N], temp[N];

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        str[i] = i % 3 + 'a';
        temp[i] = str[i];
    }
    puts(str + 1);
    for (int i = 1; i < n; i++) {
        for (int j = 1; j <= n; j++)
            str[j] = temp[j];
        str[i]++;
        str[i + 1]++;
        str[i + 1] = str[i + 1] + 'A' - 'a';
        puts(str + 1);
    }
    return 0;
}
