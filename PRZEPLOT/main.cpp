#include <cstdio>
#include <vector>
#include <cstring>

int main() {
	static const int max_len = 1000;

	char seq0[max_len + 1];
	char seq1[max_len + 1];
	char seq2[max_len * 2 + 1];

	scanf("%s%s%s", seq0, seq1, seq2);

	int seq0_len = std::strlen(seq0);
	int seq1_len = std::strlen(seq1);
	int seq2_len = std::strlen(seq2);

	if (seq0_len + seq1_len != seq2_len) {
		printf("NIE");
		return 0;
	}

	std::vector<bool> table((seq0_len + 1) * (seq1_len + 1));

	table[0] = true;
	for (int i = 0; i < seq0_len; ++i) {
		table[i + 1] = seq0[i] == seq2[i] && table[i];
	}
	for (int i = 0; i < seq1_len; ++i) {
		table[(i + 1) * (seq0_len + 1)] = seq1[i] == seq2[i] && table[i * (seq0_len + 1)];
	}
	for (int j = 0; j < seq1_len; ++j) {
		for (int i = 0; i < seq0_len; ++i) {
			if (seq0[i] == seq2[i + j + 1] && seq1[j] == seq2[i + j + 1]) {
				table[(j + 1) * (seq0_len + 1) + (i + 1)] = table[j * (seq0_len + 1) + (i + 1)] || table[(j + 1) * (seq0_len + 1) + i];
			}
			else if (seq0[i] == seq2[i + j + 1]) {
				table[(j + 1) * (seq0_len + 1) + (i + 1)] = table[(j + 1) * (seq0_len + 1) + i];
			}
			else if (seq1[j] == seq2[i + j + 1]) {
				table[(j + 1) * (seq0_len + 1) + (i + 1)] = table[j * (seq0_len + 1) + (i + 1)];
			}
			else {
				table[(j + 1) * (seq0_len + 1) + (i + 1)] = false;
			}
		}
	}

	if (table[seq1_len * (seq0_len + 1) + seq0_len]) {
		printf("TAK");
	}
	else {
		printf("NIE");
	}

	return 0;
}
