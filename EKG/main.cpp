#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>

struct beaver {
	int next;
	int prev;
	int visited;

	beaver()
		: next(-1)
		, prev(-1)
		, visited(false) {
	}
};

int main() {
	int n = 0, x = 0;
	std::scanf("%d %d", &n, &x);
	--x;
	std::vector<beaver> beavers(n);
	for (int i = 0; i < n; ++i) {
		scanf("%d", &beavers[i].prev);
		if (--beavers[i].prev != -1) {
			beavers[beavers[i].prev].next = i;
		}
	}

	int xpos = 1;
	int j = x;
	beavers[x].visited = true;
	while (beavers[j].prev != -1) {
		j = beavers[j].prev;
		beavers[j].visited = true;
		++xpos;
	}
	j = x;
	while (beavers[j].next != -1) {
		j = beavers[j].next;
		beavers[j].visited = true;
	}

	std::multiset<int> queues;
	for (int i = 0; i < n; ++i) {
		if (!beavers[i].visited) {
			beavers[i].visited = true;
			int num = 1;
			int j = i;
			while (beavers[j].prev != -1) {
				j = beavers[j].prev;
				beavers[j].visited = true;
				++num;
			}
			j = i;
			while (beavers[j].next != -1) {
				j = beavers[j].next;
				beavers[j].visited = true;
				++num;
			}
			queues.insert(num);
		}
	}

	int queues_sum = 0;
	for (std::multiset<int>::const_iterator itr = queues.begin(); itr != queues.end(); ++itr) {
		queues_sum += *itr;
	}

	std::vector<bool> table((queues_sum + 1) * (queues.size() + 1), false);
	table[0] = true;

	j = 1;
	for (std::multiset<int>::const_iterator itr = queues.begin(); itr != queues.end(); ++itr) {
		for (int i = 0; i <= queues_sum; ++i) {
			if (table[(j - 1) * (queues_sum + 1) + i]) {
				table[j * (queues_sum + 1) + i] = true;
				table[j * (queues_sum + 1) + i + *itr] = true;
			}
		}
		++j;
	}

	for (int i = 0; i <= queues_sum; ++i) {
		if (table[queues.size() * (queues_sum + 1) + i]) {
			printf("%d\n", i + xpos);
		}
	}

	return 0;
}
