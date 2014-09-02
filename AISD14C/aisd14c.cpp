#include <cstdio>
#include <vector>
#include <climits>
#include <algorithm>

int main() {
	int num_symbols, num_keys;
	std::scanf("%d%d", &num_keys, &num_symbols);
	std::vector<int> occurences(num_symbols);
	for (int i = 0; i < num_symbols; ++i) {
		scanf("%d", &occurences[i]);
	}

	std::vector<int> suffixes_a(num_symbols + 1, 0);
	std::vector<int> suffixes_b(num_symbols + 1, 0);
	suffixes_a[num_symbols - 1] = occurences[num_symbols - 1];
	suffixes_b[num_symbols - 1] = occurences[num_symbols - 1];

	for (int i = 1; i < num_symbols; ++i) {
		suffixes_b[num_symbols - i - 1] = occurences[num_symbols - i - 1] + suffixes_b[num_symbols - i];
		suffixes_a[num_symbols - i - 1] = suffixes_b[num_symbols - i - 1] + suffixes_a[num_symbols - i];
	}

	std::vector<std::vector<std::pair<int, int> > > 
		table(num_keys, std::vector<std::pair<int, int> >(num_symbols, std::make_pair(0, 0)));
	for (int k = 0; k < num_keys; ++k) {
		for (int s = k; s < num_symbols - num_keys + k + 1; ++s) {
			if (k == 0) {
				table[k][s].first = suffixes_a[0] - suffixes_a[s + 1] - suffixes_b[s + 1] * (s + 1);
			}
			else {
				int lastkey = s - table[k][s - 1].second - 1;
				int minimum = INT_MAX;
				int separator = -1;
				for (int i = std::max(k - 1, s - lastkey - 1); i < s; ++i) {
					int current = table[k - 1][i].first + suffixes_a[i + 1] - suffixes_a[s + 1] - suffixes_b[s + 1] * (s - i);
					if (minimum > current) {
						minimum = current;
						separator = i;
					}
				}
				table[k][s].first = minimum;
				table[k][s].second = separator;
			}
		}
	}

	std::vector<int> separators(num_keys + 1, 0);
	int itr = num_symbols - 1;
	for (int i = 0; i < num_keys; ++i) {
		separators[num_keys - i] = itr + 1;
		itr = table[num_keys - i - 1][itr].second;
	}

	printf("%d\n", table[num_keys - 1][num_symbols - 1]);
	for (int i = 0; i < num_keys; ++i) {
		printf("%d ", separators[i + 1] - separators[i]);
	}

	return 0;
}