#include <cstdio>
#include <climits>
#include <vector>
#include <algorithm>
#include <functional>

inline bool is_a(std::pair<int, int> a) {
	return a.first >= a.second;
}

struct pred_t {
	bool operator()(std::pair<int, int> a, std::pair<int, int> b) const {
		return a.first + a.second > b.first + b.second;
	}
};

int main() {
	int num_stacks = 0;
	int num_turns = 0;
	std::scanf("%d%d", &num_stacks, &num_turns);

	std::vector<std::pair<int, int> > stacks(num_stacks);
	for (int i = 0; i < num_stacks; ++i) {
		std::scanf("%d", &stacks[i].first);
	}
	for (int i = 0; i < num_stacks; ++i) {
		std::scanf("%d", &stacks[i].second);	
	}

	int itr = 0, partition = 0;
	while (itr < num_stacks) {
		if (is_a(stacks[itr])) {
			std::swap(stacks[partition], stacks[itr]);
			++partition;
		}
		++itr;
	}

	std::vector<long long> stacks_a(partition * 2 + 1);
	for (int i = 0; i < partition; ++i) {
		stacks_a[2 * i + 1] = stacks[i].first;
		stacks_a[2 * i + 2] = stacks[i].second;
	}

	std::sort(stacks_a.begin() + 1, stacks_a.end(), std::greater<long long>());
	for (unsigned i = 1; i < stacks_a.size(); ++i) {
		stacks_a[i] += stacks_a[i - 1];
	}

	std::sort(stacks.begin() + partition, stacks.end(), pred_t());
	std::vector<int> suffix_max(stacks.size() - partition);
	std::vector<int> prefix_min(stacks.size() - partition);
	int maximum = 0;
	int minimum = INT_MAX;
	for (unsigned i = 0; i < stacks.size() - partition; ++i) {
		if (maximum < stacks[stacks.size() - i - 1].first) {
			maximum = stacks[stacks.size() - i - 1].first;
		}
		suffix_max[stacks.size() - partition - i - 1] = maximum;

		if (minimum > stacks[i + partition].second) {
			minimum = stacks[i + partition].second;
		}
		prefix_min[i] = minimum;
	}

	std::vector<long long> stacks_b((stacks.size() - partition) * 2 + 1);
	for (unsigned i = 1; i < stacks_b.size(); ++i) {
		int j = (i - 1) / 2;
		int sum = stacks[partition + j].first + stacks[partition + j].second;
		if (i % 2 == 0) {
			stacks_b[i] = stacks_b[i - 2] + sum;
		}
		else {
			stacks_b[i] = std::max(stacks_b[i - 1] + suffix_max[j], stacks_b[i - 1] + sum - prefix_min[j]);
		}
	}

	long long max_value = 0;


	for (int i = std::max(0, num_turns - int(stacks_b.size() - 1)); i < std::min(int(stacks_a.size()), num_turns + 1); ++i) {
		long long value = stacks_a[i] + stacks_b[num_turns - i];
		if (max_value < value) {
			max_value = value;
		}
	}






	std::printf("%lld", max_value);

	return 0;
}
