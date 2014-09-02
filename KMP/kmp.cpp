#include <cstdio>
#include <string>
#include <cctype>
#include <vector>

void instance() {
	std::string pattern;
	std::string text;
	char c = getchar();
	while (std::isspace(c)) {
		c = getchar();
	}
	while (std::isgraph(c)) {
		pattern.push_back(c);
		c = getchar();
	}
	while (std::isspace(c)) {
		c = getchar();
	}
	while (std::isgraph(c)) {
		text.push_back(c);
		c = getchar();
	}

	std::vector<int> table(pattern.size() + 1);
	table[0] = -1;
	
	for (int i = 0; i < pattern.size(); ++i) {
		table[i + 1] = table[i] + 1;
		while (table[i + 1] > 0 && pattern[i] != pattern[table[i + 1] - 1]) {
			table[i + 1] = table[table[i + 1] - 1] + 1;
		}
	}

	int j = 0;
	for (int i = 0; i < text.size(); ++i) {
		while (true) {
			if (text[i] == pattern[j]) {
				++j;       
				if (j == pattern.size()) {   // maybe that was the last state
					printf("%d\n", i - j + 1);
					j = table[j];
				}
				break;
			}
			else if (j == 0) {
				break;   // no match in state j=0, give up
			}
			else {
				j = table[j];    // try shorter partial match
			}
		}
	}
}

int main() {
	int num_instances = 0;
	std::scanf("%d", &num_instances);
	for (int i = 0; i < num_instances; ++i) {
		instance();
	}
	return 0;
}
