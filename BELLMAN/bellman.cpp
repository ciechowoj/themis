#include <cstdio>
#include <climits>
#include <vector>

struct edge_t {
	edge_t() {
	}

	edge_t(int source, int target, int weight)
		: source(source)
		, target(target)
		, weight(weight) {
	}

	short source;
	short target;
	int weight;
};

int main() {
	int num_vertices = 0;
	int num_edges = 0;
	int start = 0;
	scanf("%d%d%d", &num_vertices, &num_edges, &start);

	std::vector<edge_t> edges(num_edges);
	for (int i = 0; i < num_edges; ++i) {
		scanf("%hd%hd%d", &edges[i].source, &edges[i].target, &edges[i].weight);
	}

	std::vector<int> vertices(num_vertices, INT_MAX / 2);
	vertices[start] = 0;

	for (int v = 0; v < num_vertices - 1; ++v) {
		for (int e = 0; e < num_edges; ++e) {
			if (vertices[edges[e].source] != INT_MAX / 2 && vertices[edges[e].source] + edges[e].weight < vertices[edges[e].target]) {
				vertices[edges[e].target] = vertices[edges[e].source] + edges[e].weight;
			}
		}
	}

	for (int e = 0; e < num_edges; ++e) {
		if (vertices[edges[e].source] != INT_MAX / 2 && vertices[edges[e].source] + edges[e].weight < vertices[edges[e].target]) {
			printf("NIE");
			return 0;
		}
	}

	for (int i = 0; i < num_vertices; ++i) {
		if (i != start && vertices[i] != INT_MAX / 2) {
			printf("%d %d\n", i, vertices[i]);
		}
	}
	
	return 0;
}