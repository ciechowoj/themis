#include <cstdio>
#include <climits>
#include <set>
#include <vector>

static const long long infty = LLONG_MAX / 2;

struct edge_t {
	edge_t() {
	}

	edge_t(int target, int length)
		: target(target)
		, length(length) {
	}

	int target;
	int length;
};

struct vertex_t : public std::vector<edge_t> {
	vertex_t()
		: distance(infty) {
	}

	long long distance;
};

int main() {
	int num_towns = 0;
	int num_links = 0;
	scanf("%d%d", &num_towns, &num_links);

	std::vector<vertex_t> vertices(num_towns);
	vertices[0].distance = 0;
	for (int i = 0; i < num_links; ++i) {
		int from, to, dist;
		scanf("%d%d%d", &from, &to, &dist);
		--from; --to;
		vertices[from].push_back(edge_t(to, dist));
		vertices[to].push_back(edge_t(from, dist));
	}

	std::set<std::pair<long long, int> > queue;
	queue.insert(std::make_pair(0, 0));
	while (!queue.empty()) {
		int u = queue.begin()->second;
		queue.erase(queue.begin());
		for (unsigned i = 0; i < vertices[u].size(); ++i) {
			long long dist = vertices[u].distance + vertices[u][i].length;
			if (dist < vertices[vertices[u][i].target].distance) {
				queue.erase(std::make_pair(vertices[vertices[u][i].target].distance, vertices[u][i].target));
				queue.insert(std::make_pair(dist, vertices[u][i].target));
				vertices[vertices[u][i].target].distance = dist;
			}
		}
	}

	for (int i = 1; i < num_towns; ++i) {
		printf("%lld ", vertices[i].distance);
	}

	return 0;
}