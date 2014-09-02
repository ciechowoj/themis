#include <cstdio>
#include <vector>
#include <climits>
#include <algorithm>

static const int infty = INT_MAX / 2;

struct field_t {
	field_t()
		: cost(0)
		, dist(infty)
		, prev(-1) {
	}

	int cost;
	int dist;
	int prev;
};

void instance() {
	int num_rows, num_cols;
	std::scanf("%d%d", &num_rows, &num_cols);

	std::vector<std::vector<field_t> > table(num_cols, std::vector<field_t>(num_rows + 2));

	for (int row = 0; row < num_rows; ++row) {
		for (int col = 0; col < num_cols; ++col) {
			std::scanf("%d", &table[col][row + 1]);
		}
	}

	for (int row = 0; row < num_rows; ++row) {
		table[0][row + 1].dist = table[0][row + 1].cost;
	}

	for (int col = 1; col < num_cols; ++col) {
		for (int row = 1; row <= num_rows; ++row) {
			int top = table[col - 1][row - 1].dist;
			int center = table[col - 1][row].dist;
			int bottom = table[col - 1][row + 1].dist;
			int best, index;
			if (top < center) {
				if (top < bottom) {
					index = row - 1;
					best = top;
				}
				else {
					index = row + 1;
					best = bottom;
				}
			}
			else {
				if (center < bottom) {
					index = row;
					best = center;
				}
				else {
					index = row + 1;
					best = bottom;
				}
			}

			table[col][row].dist = best + table[col][row].cost;
			table[col][row].prev = index;
		}
	}

	int best = infty;
	int start = 0;
	for (int row = 0; row < num_rows; ++row) {
		if (table[num_cols - 1][row + 1].dist < best) {
			best = table[num_cols - 1][row + 1].dist;
			start = row + 1;
		}
	}

	std::vector<int> path(num_cols);
	path[num_cols - 1] = start;
	for (int i = 0; i < num_cols - 1; ++i) {
		path[num_cols - i - 2] = table[num_cols - i - 1][path[num_cols - i - 1]].prev;
	}

	for (int i = 0; i < num_cols; ++i) {
		std::printf("%d ", path[i] - 1);
	}
}

int main() {
	instance();
	return 0;
}