#include <iostream>
#include <fstream>
#include <cstring>
#include <array>
#include <vector>
#include <string>
using namespace std;

void ask_oracle() {
		std::string solver_path = "sat_oracle.py";
		std::string command = "python3 " + solver_path + " sat.cnf sat.sol";
		std::array<char, 512> buffer{};
		std::string output;

		auto pipe = popen(command.c_str(), "r");

		while (!feof(pipe)) {
			if (fgets(buffer.data(), 512, pipe) != nullptr) {
				output += buffer.data();
			}
		}

		auto rc = pclose(pipe);

		if (rc != EXIT_SUCCESS) {
			std::cerr << "Error encountered while running oracle" << std::endl;
			std::cerr << output << std::endl;
			exit(-1);
		}
}

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
	// urmeaza partea analoaga cu subpunctul anterior
	// dar in while pana obtinem true;

	int k = 1;
	int ok = 0;
	while (ok == 0 && k <= m) {
		ofstream fout("sat.cnf");
		int V = m * k;
		int F = n + k * (k - 1) / 2 * m + m * (m - 1) / 2 * k + k;
		fout << "p cnf " << V << ' ' << F << '\n';
		for (int i = 1; i <= k; ++i) {
			for (int j = 1; j <= m; ++j) {
				fout << j + (i - 1) * m << ' ';
			}
			fout << "0" << '\n';
		}

		int **helper = (int **)malloc((m + 1) * sizeof(int *));
		for (int i = 0; i < m + 1; ++i) {
			helper[i] = (int *)calloc((k + 1), sizeof(int));
		}

		for (int i = 1; i <= m; ++i) {
			for (int j = 1; j <= k; ++j) {
				//fout << -(i + (j - 1) * m) << ' ';
				helper[i][j] = (i + (j - 1) * m);
			}
			//fout << "0" << '\n';
		}
		for (int i = 1; i <= m; ++i) {
			for (int j = 1; j <= k; ++j) {
				for (int t = j + 1; t <= k; ++t) {
					fout << -helper[i][j] << ' ' << -helper[i][t] << ' ' << '0' << '\n';
				}
			}
		}

		for (int j = 1; j <= k; ++j) {
			for (int r = 1; r <= m; ++r)
				for (int s = r + 1; s <= m; ++s)
					fout << -helper[r][j] << ' ' << -helper[s][j] << ' ' << '0' << '\n';
		}

		for (int i = 1; i <= n; ++i) {
			// magie
			for (int j = 1; j <= m; ++j) {
				if (mat[j][i] == 1) {
					for (int z = 1; z <= k; ++z) {
						fout << helper[j][z] << ' ';
					}
				}
			}
			fout << '0' << '\n';
		}
		fout.close();
		for (int i = 0; i < m + 1; ++i) {
			free(helper[i]);
		}
		free(helper);
		// timpul pentru interpretarea oracoului
		ask_oracle();
		ifstream ffin("sat.sol");
		char buff[20];
		ffin.getline(buff, 20);
		if (strncmp(buff, "True", 4) == 0) {
			int auxi, elemy;
			cout << k << '\n';
			ffin >> auxi;
			for (int i = 1; i <= auxi; ++i) {
				ffin >> elemy;
				if (elemy > 0) {
					cout << 1 + (elemy -1) % m << ' ';
					//cout << elemy << ' ';
				}
			}
			ok = 1;
		} else {
			k++;
		}
		ffin.close();
	}
	if (ok == 0) {
		cout << "False\n";
	}


	for (int i = 0; i < m + 1; ++i) {
		free(mat[i]);
	}
	free(mat);
	return 0;
}
