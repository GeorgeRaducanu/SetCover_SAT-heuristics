#include <iostream>
#include <fstream>
#include <cstring>
#include <array>
#include <vector>
#include <string>
using namespace std;

int main(void) {
	int N, M, P;
	cin >> N >> M >> P;
	cin.get();
	vector<string> posesions;
	string line;
	for (int i = 1; i <= N; ++i) {
		//cin.get();
		getline(cin, line);
		posesions.push_back(line);
	}

	vector<string> wanted;
	for (int i = 1; i <= M; ++i) {
		getline(cin, line);
		wanted.push_back(line);
	}

	vector<string> needed;
	// parcurg ce vreau si daca nu il am il adaug in lista;
	for (auto it = wanted.begin(); it != wanted.end(); ++it) {
		int ok = 0;
		for (auto it2 = posesions.begin(); it2 != posesions.end(); ++it2) {
			if (*it == *it2)
				ok = 1;
		}
		if (ok == 0)
			needed.push_back(*it);
	}

	// cout << "Needed " << needed.size() << '\n';
	// for (auto it = needed.begin(); it != needed.end(); ++it)
	//     cout << *it << '\n';
	int n = needed.size();
	int m = P; // numarul de pachete citite
	int **mat = (int **)malloc((m + 1) * sizeof(int *));
	for (int i = 0; i < m + 1; ++i) {
		mat[i] = (int *)calloc((n + 1), sizeof(int));
	}
	// matrice de frecventa pentru de m linii si n coloane
	// pe linia x =1,m pt submultimea x se trece 1 pe coloana
	// y = 1,n daca elementul y apartine lui x, altfel 0;
	int card;
	string buff_str;
	for (int i = 1; i <= m; ++i) {
		cin >> card;
		cin.get();
		for (int j = 1; j <= card; ++j) {
			getline(cin, buff_str);
			int idx = 0;
			for (auto it = needed.begin(); it != needed.end(); it++) {
				idx++;
				if (*it == buff_str)
					mat[i][idx] = 1;
			}
		}
	}
	// urmeaza euristica
	// la fiecare pas aleg pachetul cu nr maxim de 
	// carti ce nu a fost alese pana la momentul respectiv;
	vector<int> choosen_idx;
	int reuniun_sum = 0, fail = 0;
	int num_of_sets = 0, s, maxi, idx_maxi;
	while (reuniun_sum != n &&  num_of_sets != m && fail == 0) {
		// caut indexul liniei coresp
		// sumei maxime
		maxi = -1, idx_maxi = -1;
		for (int i = 1; i <= m; ++i) {
			s = 0;
			for (int j = 1; j <= n; ++j)
				s += mat[i][j];

			if (s > maxi) {
				maxi = s;
				idx_maxi = i;
			}
		}
		if (maxi == 0) {
			fail = 1;
		} else {
			// alegem linia cu indicele idx_maxi
			choosen_idx.push_back(idx_maxi);
			reuniun_sum += maxi;
			num_of_sets++;
			// acuma trb sa zeroizam unde are asta 1
			// pe toate liniile
			for (int i = 1; i <= n; ++i) {
				if (mat[idx_maxi][i] == 1) {
					for (int j = 1; j <= m; ++j)
						mat[j][i] = 0;
				}
			}
		}
	}
	if (fail == 1) {
		cout << "Fail\n";
	} else {
		if (num_of_sets == m && reuniun_sum != n) {
			cout << "Fail\n";
		} else {
			cout << num_of_sets << "\n";
			for (auto it = choosen_idx.begin(); it != choosen_idx.end(); ++it)
			    cout << *it << " ";
		}
	}

	for (int i = 0; i < m + 1; ++i) {
		free(mat[i]);
	}
	free(mat);
	return 0;
}
