#include <cstdio>
#include <cstring>
#include <cctype>

char buffer[1111111];

int main(void) {
	while (true) {
		int answer = 0;
		for (; ~scanf("%s", buffer); ) {
			if (!strcmp(buffer, "###")) {
				printf("%d:%02d\n", answer / 60, answer % 60);
				return 0;
			}
			if (!strcmp(buffer, "$$$")) {
				break;
			}
			
			int a = 0, b = 0, sign = 1, number = 0;

			bool before = true;
			int length = (int)strlen(buffer);
			
			for (int i = 0; i < length; ++i) {
				if (buffer[i] == '.' || buffer[i] == ':') {
					before = false;
					a = number;
					number = 0;
				} else if (buffer[i] == '-') {
					sign = -1;
				} else if (isdigit(buffer[i])){
					number = number * 10 + buffer[i] - '0';
				}
			}
			
			b = number;
			
			answer += sign * (a * 60 + b);
		}
		printf("%d:%02d\n", answer / 60, answer % 60);
	}
}
