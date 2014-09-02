#include <cstdio>
#include <cstring>
#include <algorithm>

void test() {
	const int max_digits = 100;
	char seq0[max_digits + 1];
	char seq1[max_digits + 1];
	char seq2[max_digits + 1];

	std::scanf("%s%s%s", seq0, seq1, seq2);

	int seq0_len = std::strlen(seq0);
	int seq1_len = std::strlen(seq1);
	int seq2_len = std::strlen(seq2);

	char* table = new char[seq0_len * seq1_len * seq2_len];

	for (int k = 0; k < seq2_len; ++k) {
		for (int j = 0; j < seq1_len; ++j) {
			for (int i = 0; i < seq0_len; ++i) {
				if (seq0[i] == seq1[j] && seq1[j] == seq2[k]) {
					if (i == 0 || j == 0 || k == 0) {
						table[k * seq0_len * seq1_len + j * seq0_len + i] = 1;
					}
					else {
						table[k * seq0_len * seq1_len + j * seq0_len + i] 
							= table[(k - 1) * seq0_len * seq1_len + (j - 1) * seq0_len + (i - 1)] + 1;
					}
				}
				else {
					int ii = i == 0 ? 0 : table[k * seq0_len * seq1_len + j * seq0_len + (i - 1)];
					int jj = j == 0 ? 0 : table[k * seq0_len * seq1_len + (j - 1) * seq0_len + i];
					int kk = k == 0 ? 0 : table[(k - 1) * seq0_len * seq1_len + j * seq0_len + i];
					table[k * seq0_len * seq1_len + j * seq0_len + i] = std::max(ii, std::max(jj, kk));
				}
			}
		}
	}

	int result = table[(seq2_len - 1) * seq0_len * seq1_len + (seq1_len - 1) * seq0_len + (seq0_len - 1)];
	std::printf("%d\n", result);
	delete[] table;
}

int main() {
	int num_tests = 0;
	std::scanf("%d", &num_tests);

	for (int i = 0; i < num_tests; ++i) {
		test();
	}

	return 0;
}
