#include <cstdio>
#include <vector>
#include <algorithm>

struct edge_t {
	edge_t() {
	}

	edge_t(int target, int weight) 
		: target(target) 
		, weight(weight) {
	}

	int target;
	int weight;

	bool operator<(const edge_t& that) const {
		return weight > that.weight;
	}

	bool operator>(const edge_t& that) const {
		return that.operator<(*this);
	}
};

struct vertex_t : public std::vector <edge_t> {
	vertex_t()
		: in_mst() {
	}

	bool in_mst;
};

int main() {
	int num_vertices = 0;
	int num_edges = 0;
	scanf("%d%d", &num_vertices, &num_edges);

	std::vector<vertex_t> vertices(num_vertices);

	for (int i = 0; i < num_edges; ++i) {
		int from, to, weight;
		scanf("%d%d%d", &from, &to, &weight);
		--from; --to;
		vertices[from].push_back(edge_t(to, weight));
		vertices[to].push_back(edge_t(from, weight));
	}

	vertices[0].in_mst = true;
	std::vector<edge_t> queue;
	int value = 0;
	for (unsigned i = 0; i < vertices[0].size(); ++i) {
		queue.push_back(edge_t(vertices[0][i].target, vertices[0][i].weight));
		std::push_heap(queue.begin(), queue.end());
	}

	for (int i = 1; i < num_vertices; ++i) {
		edge_t entry = queue.front();
		while (vertices[entry.target].in_mst) {
			std::pop_heap(queue.begin(), queue.end());
			queue.pop_back();
			entry = queue.front();
		}

		vertices[entry.target].in_mst = true;
		value += entry.weight;

		for (unsigned i = 0; i < vertices[entry.target].size(); ++i) {
			if (!vertices[vertices[entry.target][i].target].in_mst) {
				queue.push_back(edge_t(vertices[entry.target][i].target, vertices[entry.target][i].weight));
				std::push_heap(queue.begin(), queue.end());
			}
		}
	}

	printf("%d", value);
	return 0;
}
