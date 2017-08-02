#include <iostream>
#include <vector>

using namespace std;

const int N = 11111;

struct Line {
    int tp;
    char forch, limit;

    Line() {
    }

    Line(int tp, char forch, char limit) : tp(tp), forch(forch), limit(limit) {
    }
} line[N];

int variable[8888];
int length[N], begin[N], counter;
char text[222][1111];
vector<int> next[N];
int n;

class Fraction {
public:
    long long numerator, denominator;

    void reduce() {
        long long divisor = std::__gcd(numerator, denominator);
        numerator /= divisor;
        denominator /= divisor;

        if (divisor == 0) {
            numerator = 0;
            denominator = 1;
            return;
        }

        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
    }

    Fraction(const long long &numerator = 0, const long long &denominator = 1) : numerator(numerator),
                                                                                 denominator(denominator) {
        reduce();
    }

    friend Fraction operator +(const Fraction &a, const Fraction &b) {
        return Fraction(a.denominator * b.numerator + b.denominator * a.numerator, a.denominator * b.denominator);
    }

    friend Fraction operator *(const Fraction &a, const Fraction &b) {
        return Fraction(a.numerator * b.numerator, a.denominator * b.denominator);
    }

    void print(bool empty) const {
        if (numerator < 0) {
            printf("-");
            if (std::abs(denominator) == 1) {
                std::cout << -numerator;
            } else {
                std::cout << -numerator << "/" << denominator;
            }
        } else {
            if (!empty) {
                printf("+");
            }
            if (std::abs(denominator) == 1) {
                std::cout << numerator;
            } else {
                std::cout << numerator << "/" << denominator;
            }
        }
    }
};

class Polynomial {
public:
    Fraction item[10];

    Polynomial() {
        for (int i = 0; i < 10; ++i) {
            item[i] = Fraction();
        }
    }

    friend Polynomial operator *(const Polynomial &a, const Polynomial &b) {
        Polynomial c;
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j <= i; ++j) {
                c.item[i] = c.item[i] + a.item[j] * b.item[i - j];
            }
        }
        return c;
    }

    friend Polynomial operator +(const Polynomial &a, const Polynomial &b) {
        Polynomial c;
        for (int i = 0; i < 10; ++i) {
            c.item[i] = a.item[i] + b.item[i];
        }
        return c;
    }
};

void run(int x) {
    if (line[x].tp == 0) {
        counter++;
        return;
    }
    for (variable[line[x].forch] = 0; variable[line[x].forch] < variable[line[x].limit]; variable[line[x].forch]++) {
        for (int i = 0; i < (int)next[x].size(); i++) {
            run(next[x][i]);
        }
    }
}

int calc(int nn) {
    memset(variable, 0, sizeof variable);
    variable['n'] = nn;
    for (int i = '0'; i <= '9'; i++) {
        variable[i] = i - '0';
    }
    for (int i = 0; i < n; i++) {
        begin[i] = -1;
        length[i] = strlen(text[i]);
        for (int j = 0; j < length[i]; j++) {
            if (text[i][j] != ' ' && text[i][j] != '\n') {
                begin[i] = j;
                if (j + 13 < length[i]) {
                    if (text[i][j] == 'f' && text[i][j + 1] == 'o' && text[i][j + 2] == 'r') {
                        line[i] = Line(1, text[i][j + 4], text[i][j + 15]);
                    }
                } else {
                    line[i] = Line(0, -1, -1);
                }
                break;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        next[i].clear();
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (begin[j] <= begin[i]) {
                break;
            }
            if (begin[j] == begin[i] + 4) {
                next[i].push_back(j);
            }
        }
    }

    counter = 0;

    for (int i = 0; i < n; i++) {
        if (begin[i] == 0) {
            run(i);
        }
    }
    return counter;
}

void solve() {
    n--;

    Polynomial answer;
    for (int i = 0; i <= 6; ++i) {
        long long a = calc(i);
        long long b = 1;

        for (int j = 0; j <= 6; ++j) {
            if (j != i) {
                b *= i - j;
            }
        }

        Fraction coefficient = Fraction(a, b);

        Polynomial temp;
        temp.item[0] = coefficient;

        for (int j = 0; j <= 6; ++j) {
            if (j != i) {
                Polynomial item;
                item.item[0] = -j;
                item.item[1] = 1;
                temp = temp * item;
            }
        }

        answer = answer + temp;
    }

    bool empty = true;
    for (int i = 0; i <= 6; ++i) {
        if (answer.item[i].numerator) {
            answer.item[i].print(empty);
            empty = false;
            if (i > 0) {
                for (int j = 0; j < i; ++j) {
                    printf("*n");
                }
            }
        }
    }
    if (empty) {
        printf("0");
    }
    puts("");
}

int main() {
    n = 0;
    for (; gets(text[n++]););
    solve();
}
