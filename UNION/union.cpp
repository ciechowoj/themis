#include <cstdio>
#include <vector>

struct node_t {
	node_t()
		: rank(0)
		, parent(-1) {
	}

	int rank;
	int parent;
};

int find(std::vector<node_t>& nodes, int a) {
	if (nodes[a].parent != a) {
		nodes[a].parent = find(nodes, nodes[a].parent);
	}
	return nodes[a].parent;
}

void unio(std::vector<node_t>& nodes, int a, int b) {
	int aa = find(nodes, a);
	int bb = find(nodes, b);

	if (aa != bb) {
		if (nodes[aa].rank < nodes[bb].rank) {
			nodes[aa].parent = bb;
		}
		else if (nodes[bb].rank < nodes[aa].rank) {
			nodes[bb].parent = aa;
		}
		else {
			nodes[aa].parent = bb;
			++nodes[bb].rank;
		}
	}
}

int main() {
	int num_towns, num_links, num_queries;
	std::scanf("%d%d%d", &num_towns, &num_links, &num_queries);

	std::vector<node_t> nodes(num_towns);
	for (std::size_t i = 0; i < nodes.size(); ++i) {
		nodes[i].parent = i;
	}

	for (int i = 0; i < num_links; ++i) {
		int a, b;
		std::scanf("%d%d", &a, &b);
		--a; --b;
		unio(nodes, a, b);
	}

	for (int i = 0; i < num_queries; ++i) {
		int w, a, b;
		std::scanf("%d%d%d", &w, &a, &b);
		--a; --b;

		if (w) {
			unio(nodes, a, b);
		}
		else {
			if (find(nodes, a) == find(nodes, b)) {
				printf("TAK\n");
			}
			else {
				printf("NIE\n");
			}
		}
	}

	return 0;
}
