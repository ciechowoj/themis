#include <cstdio>
#include <vector>

int main() {
	int num_elems;
	std::scanf("%d", &num_elems);
	std::vector<int> elems;
	elems.reserve(num_elems);
	elems.resize(num_elems);
	for (int i = 0; i < num_elems; ++i) {
		std::scanf("%d", &elems[i]);
	}

	for (int i = 1; i < num_elems; ++i) {
		bool swapped = false;
		for (int j = 0; j < num_elems - i; ++j) {
			if (elems[j] > elems[j + 1]) {
				std::swap(elems[j], elems[j + 1]);
				swapped = true;
			}
		}
		if (swapped) {
			for (int i = 0; i < num_elems; ++i) {
				printf("%d ", elems[i]);
			}
			printf("\n");
		}
		else {
			break;
		}
	}

	return 0;
}
