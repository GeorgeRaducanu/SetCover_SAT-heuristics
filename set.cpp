#include <iostream>
#include <fstream>
#include <cstring>
#include <array>
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
	//ifstream fin("set.in");
	ofstream fout("sat.cnf");
	int n, m, k;
	cin >> n >> m >> k;
	int **mat = (int **)malloc((m + 1) * sizeof(int *));
	for (int i = 0; i < m + 1; ++i) {
		mat[i] = (int *)calloc((n + 1), sizeof(int));
	}
	// matrice de frecventa pentru de m linii si n coloane
	// pe linia x =1,m pt submultimea x se trece 1 pe coloana
	// y = 1,n daca elementul y apartine lui x, altfel 0;
	int card, elem;
	for (int z = 0; z < m; ++z) {
		cin >> card;
		for (int i = 0; i < card; ++i) {
			cin >> elem;
			mat[z + 1][elem] = 1;
		}
	}

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

	//fin.close();
	fout.close();
	for (int i = 0; i < m + 1; ++i) {
		free(mat[i]);
	}
	free(mat);
	for (int i = 0; i < m + 1; ++i) {
		free(helper[i]);
	}
	free(helper);
	
	// apelez oracolul
	ask_oracle();


	ifstream ffin("sat.sol");
	//ofstream ffout("set.out");

	char buff[20];
	ffin.getline(buff, 20);
	
	if (strncmp(buff, "True", 4) == 0) {
		cout << "True\n";
		int auxi, elemy;
		cout << k << '\n';
		ffin >> auxi;
		int count = 0;
		for (int i = 1; i <= auxi; ++i) {
			ffin >> elemy;
			if (elemy > 0) {
				cout << 1 + (elemy -1) % m << ' ';
				//cout << elemy << ' ';
				count++;
			}
		}
	} else {
		cout << "False\n";
	}

	ffin.close();
	return 0;
}