#include <cstdio>
#include <vector>

int main() {
	int n = 0;
	std::scanf("%d", &n);
	std::vector<int> buckets(128, 0);

	for (int i = 0; i < n; ++i) {
		int x = 0;
		std::scanf("%d", &x);
		++buckets[x];
	}

	for (unsigned i = 0; i < buckets.size(); ++i) {
		for (int j = 0; j < buckets[i]; ++j) {
			printf("%d ", i);
		}
	}

	return 0;
}
