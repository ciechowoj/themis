#include <cstdio>
#include <vector>
#include <cctype>
#include <algorithm>

struct pair_t {
	int first;
	int second;
	int index;

	bool operator<(const pair_t& that) const {
		return first == that.first ? second < that.second : first < that.first;
	}

	bool operator>(const pair_t& that) const {
		return that.operator<(*this);
	}

	bool operator==(const pair_t& that) const {
		return first == that.first && second == that.second;
	}

	bool operator!=(const pair_t& that) const {
		return first != that.first || second != that.second;
	}
};

int main() {
	std::vector<std::vector<int> > table(1);
	int chr = std::getchar();
	while (std::isgraph(chr)) {
		table[0].push_back(chr);
		chr = std::getchar();
	}

	unsigned size = table[0].size();
	std::vector<pair_t> pairs;
	pairs.reserve(table[0].size());
	for (int j = 1; (1 << j) <= size; ++j) {
		int p = 1 << j;
		pairs.resize(size - p + 1);
		for (int i = 0; i < pairs.size(); ++i) {
			pairs[i].first = table[j - 1][i];
			pairs[i].second = table[j - 1][i + p / 2];
			pairs[i].index = i;
		}

		std::sort(pairs.begin(), pairs.end());

		int id = 0;
		table.push_back(std::vector<int>(pairs.size(), 0));
		table[j][pairs[0].index] = id;
		for (int i = 1; i < pairs.size(); ++i) {
			if (pairs[i] != pairs[i - 1]) {
				++id;
			}
			table[j][pairs[i].index] = id;
		}
	}

	int begin = 0, end = size;
	int half = begin + (end - begin) / 2;

	while (end - begin > 1) {
		int q = 0;
		while ((1 << q) <= half) {
			++q;
		}
		--q;
		int p = 1 << q;

		pairs.resize(size - half + 1);
		for (int i = 0; i < pairs.size(); ++i) {
			pairs[i].first = table[q][i];
			pairs[i].second = table[q][i + half - p];
			pairs[i].index = i;
		}

		std::sort(pairs.begin(), pairs.end());

		int count = 1;
		int maximum = 1;
		for (int i = 1; i < pairs.size(); ++i) {
			if (pairs[i] == pairs[i - 1]) {
				++count;
			}
			else {
				count = 1;
			}
			maximum = std::max(maximum, count);
		}

		if (maximum < 2) {
			end = half;
		}
		else {
			begin = half;
		}
		half = begin + (end - begin) / 2;
	}

	printf("%d", begin);
	return 0;
}
