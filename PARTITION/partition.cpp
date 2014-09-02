#include <cstdio>
#include <vector>
#include <algorithm>

int main() {
	int num_players = 0;
	int selection = 0;
	scanf("%d%d", &num_players, &selection);

	std::vector<int> heights(num_players);
	for (int i = 0; i < num_players; ++i) {
		scanf("%d", &heights[i]);
	}

	std::swap(heights[selection - 1], heights[0]);
	
	int itr = 1, jtr = num_players - 1, ktr = 1;
	while (itr <= jtr) {
		if (heights[itr] > heights[0]) {
			while (heights[jtr] > heights[0]) {
				--jtr;
			}
			if (itr < jtr) {
				std::swap(heights[itr], heights[jtr]);
			}
			else {
				break;
			}
		}
		if (heights[itr] == heights[0]) {
			std::swap(heights[itr], heights[ktr++]);
		}
		++itr;
	}

	for (int i = 0, s = std::min(ktr, itr - ktr); i < s; ++i) {
		std::swap(heights[i], heights[itr - s + i]);
	}

	for (int i = 0; i < heights.size(); ++i) {
		printf("%d ", heights[i]);
	}

	return 0;
}