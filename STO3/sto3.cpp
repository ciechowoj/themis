#include <cstdio>
#include <vector>
#include <utility>
#include <climits>
#include <algorithm>

static const int infty = INT_MAX / 2;

void instance() {
	int num_rows, num_cols;
	std::scanf("%d%d", &num_rows, &num_cols);

	std::vector<std::vector<std::pair<int, int> > > table(num_cols, std::vector<std::pair<int, int> >(num_rows + 2, std::make_pair(infty, infty)));

	for (int row = 0; row < num_rows; ++row) {
		for (int col = 0; col < num_cols; ++col) {
			std::scanf("%d", &table[col][row + 1]);
		}
	}

	for (int row = 0; row < num_rows; ++row) {
		table[0][row + 1].second = table[0][row + 1].first;
	}

	for (int col = 1; col < num_cols; ++col) {
		for (int row = 1; row <= num_rows; ++row) {
			int north = table[col][row - 1].second;
			int north_west = table[col - 1][row - 1].second;
			int west = table[col - 1][row].second;
			int south_west = table[col - 1][row + 1].second;
			// int south = table[col][row + 1].second;
			int best = std::min(std::min(north, north_west), std::min(west, south_west));
			table[col][row].second = best + table[col][row].first;
		}

		for (int row = num_rows; row != 0; --row) {
			int north_west = table[col - 1][row - 1].second;
			int west = table[col - 1][row].second;
			int south_west = table[col - 1][row + 1].second;
			int south = table[col][row + 1].second;
			int best = std::min(std::min(south, north_west), std::min(west, south_west));
			table[col][row].second = std::min(table[col][row].second, best + table[col][row].first);
		}
	}

	int best = infty;
	for (int row = 0; row < num_rows; ++row) {
		best = std::min(best, table[num_cols - 1][row + 1].second);
	}

	std::printf("%d\n", best);
}

int main() {
	instance();
	return 0;
}