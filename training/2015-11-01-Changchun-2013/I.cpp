#include <cstdio>
#include <algorithm>
#include <vector>

const unsigned long long MAGIC = 4423;

const int N = 555555;

int length, m, l;
char text[N];
int count[N], item[N];
unsigned long long hash[N], magic[N], substring[N];

unsigned long long get(int left, int right) {
    return hash[right] - hash[left - 1] * magic[right - left + 1];
}

void solve(void) {
    scanf("%s", text + 1);
    int length = (int)strlen(text + 1);

    hash[0] = 0;
    magic[0] = 1;
    for (int i = 1; i <= length; ++i) {
        hash[i] = hash[i - 1] * MAGIC + text[i];
        magic[i] = magic[i - 1] * MAGIC;
    }

    int answer = 0;
    for (int mod = 1; mod <= l; ++mod) {
        std::vector<unsigned long long> value;

        int size = 0;
        for (int start = mod; start + l - 1 <= length; start += l) {
            size++;
            substring[size] = get(start, start + l - 1);
            value.push_back(substring[size]);
        }

        std::sort(value.begin(), value.end());
        value.erase(std::unique(value.begin(), value.end()), value.end());
        for (int i = 1; i <= size; ++i) {
            item[i] = std::lower_bound(value.begin(), value.end(), substring[i]) - value.begin() + 1;
        }

        for (int i = 1; i <= size; ++i) {
            count[i] = 0;
        }

        int differ = 0;
        for (int i = 1, j = 1; i + m - 1 <= size; ++i) {
            for (; j - i + 1 <= m; ++j) {
                if (count[item[j]] == 0) {
                    differ++;
                }
                count[item[j]]++;
            }
            if (differ == m) {
                answer++;
            }
            count[item[i]]--;
            if (count[item[i]] == 0) {
                differ--;
            }
        }
    }

    printf("%d\n", answer);
}

int main(void) {
    for (; ~scanf("%d%d", &m, &l); solve());
}
