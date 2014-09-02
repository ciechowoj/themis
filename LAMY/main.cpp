#include <cstdio>
#include <vector>
#include <map>

struct llama_t {
	llama_t()
		: rank(0)
		, parent(this)
		, diff(0) {
	}

	llama_t* parent;
	int rank;
	int diff;
};

llama_t* find(llama_t* llama) {
	if (llama->parent != llama) {
		llama_t* new_parent = find(llama->parent);
		llama->diff += llama->parent->diff;
		llama->parent = new_parent;
	}

	return llama->parent;
}

void unionx(llama_t* a, llama_t* b, int diff) {
	llama_t* a_root = find(a);
	llama_t* b_root = find(b);

	if (a_root != b_root) {
		if (a_root->rank < b_root->rank) {
			a_root->parent = b_root;
			a_root->diff = diff + b->diff - a->diff;
		}
		else if (a_root->rank > b_root->rank) {
			b_root->parent = a_root;
			b_root->diff = -diff + a->diff - b->diff;
		}
		else {
			b_root->parent = a_root;
			b_root->diff = -diff + a->diff - b->diff;
			++a_root->rank;
		}
	}
}

void instance(int n, int m) {
	std::vector<llama_t> llamas(n);
	for (int i = 0; i < llamas.size(); ++i) {
		llamas[i].parent = &llamas[i];
	}

	char ev[16];
	int a, b, w;
	for (int i = 0; i < m; ++i) {
		scanf("%s%d%d", ev, &a, &b);
		--a; --b;
		if (ev[0] == '!') {
			scanf("%d", &w);
			unionx(&llamas[a], &llamas[b], w);
		}
		else if(ev[0] == '?') {
			llama_t* a_root = find(&llamas[a]);
			llama_t* b_root = find(&llamas[b]);

			if (a_root == b_root) {
				printf("%d\n", llamas[a].diff - llamas[b].diff);
			}
			else {
				printf("UNKNOWN\n");
			}
		}
	}
}

int main() {
	int n = 0, m = 0;
	std::scanf("%d %d", &n, &m);
	while (n != 0 && m != 0) {
		instance(n, m);
		std::scanf("%d %d", &n, &m);
	}
	return 0;
}
