#include <cstdio>
#include <vector>

struct place_t {
	unsigned roads;
	unsigned paths;

	inline bool south() const {
		return (roads & 4u) != 0;
	}

	inline bool south_east() const {
		return (roads & 2u) != 0;
	}

	inline bool east() const {
		return (roads & 1u) != 0;
	}
};

int main() {
	int n, m;
	std::scanf("%d%d", &m, &n);
	std::vector<place_t> a(n + 1), b(n + 1);
	place_t* tables[2] = { &a[0], &b[0] };

	getchar(); // '\n'
	tables[0][0].roads = getchar() - '0';
	tables[0][0].paths = 1;
	for (int i = 1; i < n + 1; ++i) {
		tables[0][i].roads = getchar() - '0';
		tables[0][i].paths = tables[0][i - 1].east() ? tables[0][i - 1].paths : 0;
	}

	for (int j = 0; j < m; ++j) {
		getchar(); // '\n'
		tables[1][0].roads = getchar() - '0';
		tables[1][0].paths = tables[0][0].south() ? tables[0][0].paths : 0;
		for (int i = 1; i < n + 1; ++i) {
			tables[1][i].roads = getchar() - '0';
			tables[1][i].paths = 0;
			if (tables[0][i - 1].south_east()) {
				tables[1][i].paths += tables[0][i - 1].paths;
			}
			if (tables[0][i].south()) {
				tables[1][i].paths += tables[0][i].paths;
			}
			if (tables[1][i - 1].east()) {
				tables[1][i].paths += tables[1][i - 1].paths;
			}
			tables[1][i].paths %= 999979;
		}
		std::swap(tables[0], tables[1]);
	}

	printf("%d", tables[0][n].paths);
	return 0;
}