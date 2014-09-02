#include <cstdio>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <cmath>

struct node_t : public std::vector<int> {
	node_t()
		: parent(-1)
		, level(-1) {
	}

	int parent;
	int jump;
	int level;
};

int dfs(std::vector<node_t>& nodes, int root) {
	std::vector<std::pair<int, int> > stack(1, std::make_pair(root, 0));
	nodes[root].parent = root;
	nodes[root].level = 0;
	int height = 0;
	while (!stack.empty()) {
		if (stack.back().second < int(nodes[stack.back().first].size())) {
			int child = nodes[stack.back().first][stack.back().second];
			if (nodes[child].parent == -1) {
				nodes[child].parent = stack.back().first;
				nodes[child].level = nodes[stack.back().first].level + 1;
				++stack.back().second;
				stack.push_back(std::make_pair(child, 0));
				height = std::max(height, int(stack.size()));
			}
			else {
				nodes[stack.back().first][stack.back().second] = nodes[stack.back().first].back();
				nodes[stack.back().first].pop_back();
			}
		}
		else {
			stack.pop_back();
		}
	}
	return height;
}

int lca(std::vector<node_t>& nodes, int a, int b) {
	while (nodes[a].jump != nodes[b].jump) {
		if (nodes[a].level < nodes[b].level) {
			b = nodes[b].jump;
		}
		else {
			a = nodes[a].jump;
		}
	}

	while (a != b) {
		if (nodes[a].level < nodes[b].level) {
			b = nodes[b].parent;
		}
		else {
			a = nodes[a].parent;
		}
	}

	return a;
}

void init(std::vector<node_t>& nodes, int node, int sq, int root) {
	if (nodes[node].level < sq) {
		nodes[node].jump = root;
	}
	else {
		if (nodes[node].level % sq) {
			nodes[node].jump = nodes[nodes[node].parent].jump;
		}
		else {
			nodes[node].jump = nodes[node].parent;
		}
	}

	for (unsigned i = 0; i < nodes[node].size(); ++i) {
		init(nodes, nodes[node][i], sq, root);
	}
}

int main() {
	int num_nodes = 0;
	scanf("%d", &num_nodes);
	std::vector<node_t> nodes(num_nodes);
	for (int i = 0; i < num_nodes - 1; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		--u; --v;
		nodes[u].push_back(v);
		nodes[v].push_back(u);
	}

	int height = dfs(nodes, 0);
	int sq = int(std::sqrt(std::max(1, height)));

	init(nodes, 0, sq, 0);

	int num_queries = 0;
	scanf("%d", &num_queries);
	for (int i = 0; i < num_queries; ++i) {
		int r, a, b;
		scanf("%d%d%d", &r, &a, &b);
		--r; --a; --b;

		int u = lca(nodes, r, a);
		int v = lca(nodes, r, b);
		int w = lca(nodes, a, b);

		if (u == v && v == w) {
			printf("%d\n", ++u);
		}
		else if (u == v) {
			printf("%d\n", ++w);
		}
		else if (v == w) {
			printf("%d\n", ++u);
		}
		else {
			printf("%d\n", ++v);
		}
	}
	
	return 0;
}
