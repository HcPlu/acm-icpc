#include <cstdio>
#include <string>

const std::string name[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

const int sum[] = {0, 1, 5, 4, 1, 4, 5, 5, 6, 0, 4, 6, 0, 6, 6, 0, 2, 0, 1, 6, 0, 0, 1, 5, 6, 3, 0, 6, 6, 0, 1, 4, 6, 5,
                   6, 6, 0, 2, 4, 5, 0, 6, 6, 0, 4, 3, 0, 3, 4, 4, 5, 6, 3, 5, 6, 5, 5, 6, 1, 6, 0, 5, 6, 6, 0, 4, 5, 2,
                   6, 5, 5, 6, 0, 3, 5, 4, 5, 5, 6, 1, 3, 4, 6, 5, 5, 6, 3, 2, 6, 2, 3, 3, 4, 5, 2, 4, 5, 4, 4, 5, 0, 5,
                   6, 4, 5, 5, 6, 3, 4, 1, 5, 4, 4, 5, 6, 2, 4, 3, 4, 4, 5, 0, 2, 3, 5, 4, 4, 5, 2, 1, 5, 1, 2, 2, 3, 4,
                   1, 3, 4, 3, 3, 4, 6, 4, 5, 3, 4, 4, 5, 2, 3, 0, 4, 3, 3, 4, 5, 1, 3, 2, 3, 3, 4, 6, 1, 2, 4, 3, 3, 4,
                   1, 0, 4, 0, 1, 1, 2, 3, 0, 2, 3, 2, 2, 3, 5, 3, 4, 2, 3, 3, 4, 1, 2, 6, 3, 2, 2, 3, 4, 0, 2, 1, 2, 2,
                   3, 5, 0, 1, 3, 2, 2, 3, 0, 6, 3, 6, 0, 0, 1, 2, 6, 1, 2, 1, 1, 2, 4, 2, 3, 1, 2, 2, 3, 0, 1, 5, 2, 1,
                   1, 2, 3, 6, 1, 0, 1, 1, 2, 4, 6, 0, 2, 1, 1, 2, 6, 5, 2, 5, 6, 6, 0, 1, 5, 0, 1, 0, 0, 1, 3, 1, 2, 0,
                   1, 1, 2, 6, 0, 4, 1, 0, 0, 1, 2, 5, 0, 6, 0, 0, 1, 3, 5, 6, 1, 0};

void solve(void) {
    int number;
    scanf("%d", &number);
    int answer = (6 + sum[number % 294]) % 7;
    printf("%s\n", name[answer].c_str());
}

int main(void) {
    int tests;
    for (scanf("%d", &tests); tests--; solve());
}
