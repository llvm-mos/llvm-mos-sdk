#include <ctype.h>
#include <stdlib.h>

template <typename T> static inline T _atoi(const char *str) {
	T result = 0;
	bool sign = false;

	while (isspace(*str)) { str++; }

	if (*str == '+') { str++; }
	else if (*str == '-') { sign = true; str++; }

	while (*str >= '0' && *str <= '9') {
		result = (result * 10) + (*(str++) - '0');
	}
	return sign ? -result : result;
}

extern "C" {
int atoi(const char *str) { return _atoi<int>(str); }
long atol(const char *str) { return _atoi<long>(str); }
}
