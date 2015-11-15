#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;
const int N = 3333;
char block[N][40];
int main() {
    int a, b;
    scanf("%d%d", &a, &b);
    char ch1 = '@';
    char ch2 = '.';
    if (a > b) {
        swap(a, b);
        swap(ch1, ch2);
    }
    
    int rest = b - a + 1;
    for (int i = 1; i <= 2000; i++) {
        for (int j = 1; j <= 32; j++) {
            block[i][j] = '*';
        }
    }
    
    int answern;
    for (int i = 1; rest > 0; i++) {
        for (int j = 1; j <= 32; j += 2) {
            block[i][j] = ch2;
            rest--;
            if (rest == 0) {
                break;
            }
        }
        i++;
        for (int j = 1; j <= 32; j++) {
            block[i][j] = ch1;
        }
        if (!rest) {
            for (int k = i + 1; k <= i + 2 * (a - 1); k++) {
                if ((k - i) & 1) {
                    for (int j = 1; j <= 32; j++) {
                        block[k][j] = ch2;
                    } 
                } else {
                    for (int j = 1; j <= 32; j++) {
                        block[k][j] = ch1;
                    }
                }
            }
            answern = i + 2 * (a - 1);
            break;
        }
    }
    printf("%d %d\n", answern, 32);
    for (int i = 1; i <= answern; i++) { 
        for (int j = 1; j <= 32; j++) {
            if (block[i][j] == ch2) {
                putchar(ch2);
            } else {
                putchar(ch1);
            }
        }
        puts("");
    }
}
