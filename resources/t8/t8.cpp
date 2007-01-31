#include <iostream>

int main(size_t argc, char *argv[]) {
	register volatile size_t i = 1;
	register char const* arg;
	while ((arg = argv[i++]))
		std::cout << (strtol(arg, NULL, 10)<<3) << std::endl;
	return 0;
}
