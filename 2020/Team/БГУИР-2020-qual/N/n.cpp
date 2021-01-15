#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

// нижний - чёрные, верхний - белые

// пустая - . 
// ферзь - q, Q
// слон - b, B
// конь - k, K
// ладья - r, R

int get_type(char x) {
	if (x == '.') return -1;
	if (x >= 'a' && x <= 'z') return 1;
	return 0;
}

char make(char x) {
	if (get_type(x) == 1) return x;
	return x - 'A' + 'a'; 
}

bool check(int x, int y) {
	return x >= 0 && x < 8 && y >= 0 && y < 8;
}

vector<vector<int>> dx = {
	{-1, -1, -1, 0, 1, 1, 1, 0},
	{-1, -1, 1, 1},
	{-1, -2, -2, -1, 1, 2, 2, 1},
	{-1, 0, 1, 0}
};

vector<vector<int>> dy = {
	{-1, 0, 1, 1, 1, 0, -1, -1}, 
	{-1, 1, 1, -1},
	{-2, -1, 1, 2, 2, 1, -1, -2},
	{0, 1, 0, -1}
};

vector<int> len = {
	8,
	8,
	1,
	8
};

vector<vector<char>> need{
	{'Q', 'B', 'K', 'R'},
	{'q', 'b', 'k', 'r'}
};

bool check(int x, int y, int dx, int dy, int len, char need, vector<vector<char>> & table) {
	//cerr << x << " " << y << " " << dx << " " << dy << " " << len << " " << need << endl;
	if (!check(x, y)) return false;
	if (len == 0) return false;
	if (table[x][y] == need) return true;
	if (table[x][y] != '.') return false;
	return check(x + dx, y + dy, dx, dy, len - 1, need, table);
}

bool check(int x, int y, vector<vector<char>> & table) {
	int type = get_type(table[x][y]);
	//cerr << "type = " << type << endl;
	assert(type != -1);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < (int)dx[i].size(); j++) {
			if (check(x + dx[i][j], y + dy[i][j], dx[i][j], dy[i][j], len[i], need[type ^ 1][i], table)) {
				return true;
			}
		}
	}
	return false;
}

int help[51][51];

pair<int, int> calc(vector<vector<char>> table) {
	pair<int, int> ans = {0, 0};
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			//help[i][j] = -1;
			if (get_type(table[i][j]) == -1) { 
				continue;
			}
			else if (get_type(table[i][j]) == 0) {
				if (check(i, j, table))
				//help[i][j] = 0;
				ans.first += check(i, j, table);
			}
			else {
				if (check(i, j, table))
				//help[i][j] = 1;
				ans.second += check(i, j, table); 
			}
		}
	}
	return ans;
}

mt19937 rnd(time(0));

void precalc() {
	map<pair<int, int>, vector<vector<char>> > mem;
	for (int i = 0; i < 51; i++) for (int j = 0; j < 51; j++) if (i + j > 64) help[i][j] = -1;
	
	for (int MEGA_IT = 0; MEGA_IT < 20; MEGA_IT++) {
		cerr << "MEGA_IT = " << MEGA_IT << endl;	
		cerr << "puhh1" << endl;
		for (int it = 0; it < 200000; it++) {
			for (int y = 0; y < 4; y++) {	
				for (int x = 1; x < 3; x++) {
					int n = 8;
					vector<vector<char>> table(n, vector<char> (n, '.'));
					for (int i = 0; i < n; i++) {
						for (int j = 0; j < n; j++) {
							if (rnd() % x != 0) continue;
							table[i][j] = need[rnd() % 2][y]; 
						}
					}
					pair<int, int> fans = calc(table);
					if (max(fans.first, fans.second) > 50) continue;
					if (mem.count(fans)) continue;
					help[fans.first][fans.second] = 1;
					mem[fans] = table;
					if (mem.size() % 100 == 0) cerr << mem.size() << endl;
					cerr << "cnt = " << mem.size() << endl;
					//cerr << fans.first << " " << fans.second << endl;
				}
			}
		}
		if (mem.size() == 1935) break;
		cerr << "puhh3" << endl;
		for (int it = 0; it < 100000; it++) {
			if (it % 10000 == 0)
			//cerr << "it = " << it << endl;
			for (int y = 0; y < 4; y++) {	
				for (int x = 3; x < 14; x++) {
					int n = 8;
					vector<vector<char>> table(n, vector<char> (n, '.'));
					int cnt1 = rand() % 51;
					int cnt2 = rand() % 51;
					vector<pair<int, int>> have;
					for (int i = 0; i < n; i++)
						for (int j = 0; j < n; j++) 
							have.push_back({i, j});
					shuffle(all(have), rnd);
					for (int i = 0; i < have.size(); i++) {
						if (i >= 0 && i < cnt1) {
							table[have[i].first][have[i].second] = need[0][0];
						}
						else if (i >= cnt1 && i < cnt1 + cnt2) {
							table[have[i].first][have[i].second] = need[1][2];
						}
					}
					pair<int, int> fans = calc(table);

					if (max(fans.first, fans.second) > 50) continue;
					if (mem.count(fans)) continue;
					help[fans.first][fans.second] = 1;
					mem[fans] = table;
					if (mem.size() % 100 == 0) cerr << mem.size() << endl;
					cerr << "cnt = " << mem.size() << endl;
					//cerr << fans.first << " " << fans.second << endl;
				}
			}
		}
		if (MEGA_IT < 1) { 
			cerr << "puhh4" << endl;
			for (int it = 0; it < 100000; it++) {
				int n = 8;
				vector<vector<char>> table(n, vector<char> (n, '.'));
				int now = rnd() % 2;
				vector<pair<int, int>> have;
				for (int i = 0; i < n; i++) {
					for (int j = 0; j < n; j++) {
						if ((i + j) % 2 == 0 && rnd() % 2 == 0) {
							table[i][j] = need[now][1];
						}
						else {
							have.push_back({i, j});
						}
					}
				}
				int cnt = rnd() % 65;
				for (int i = 0; i < n; i++)
					for (int j = 0; j < n; j++)
						if ((i + j) % 2 == 1) 
							have.push_back({i, j});
				shuffle(all(have), rnd);
				for (int i = 0; i < have.size(); i++) {
					if (i < cnt) {
						table[have[i].first][have[i].second] = need[now ^ 1][0];
					}
				}
				pair<int, int> fans = calc(table);

				if (max(fans.first, fans.second) > 50) continue;
				if (mem.count(fans)) continue;
				help[fans.first][fans.second] = 1;
				mem[fans] = table;
				if (mem.size() % 100 == 0) cerr << mem.size() << endl;
				cerr << "cnt = " << mem.size() << endl;
				//cerr << fans.first << " " << fans.second << endl;
			}
			cerr << "puhh5" << endl;
			for (int it = 0; it < 100000; it++) {
				for (int x = 1; x < 10; x++) {
					int n = 8;
					vector<vector<char>> table(n, vector<char> (n, '.'));
					int now = rnd() % 2;
					for (int i = 0; i < n; i += 2) {
						for (int j = 0; j < n; j++) {
							table[i][j] = need[now][1];
						}
					}
					for (int i = 1; i < n; i += 4) {
						for (int j = 0; j < n; j += 2) {
							table[i][j] = need[now][1];
						}
					}
					for (int i = 3; i < n; i += 4) {
						for (int j = 1; j < n; j += 2) {
							table[i][j] = need[now][1];
						}
					}
					for (int i = 0; i < n; i++) {
						for (int j = 0; j < n; j++) {
							if (table[i][j] != '.') continue;
							if (rnd() % x == 0) continue;
							table[i][j] = need[now ^ 1][0];
						}
					}
					pair<int, int> fans = calc(table); 
					if (max(fans.first, fans.second) > 50) continue;
					if (mem.count(fans)) continue;
					help[fans.first][fans.second] = 1;
					mem[fans] = table;
					if (mem.size() % 100 == 0) cerr << mem.size() << endl;
					cerr << "cnt = " << mem.size() << endl;
					//cerr << fans.first << " " << fans.second << endl;
				}
			}
			cerr << "puhh6" << endl;
			for (int it = 0; it < 100000; it++) {
				for (int x = 5; x < 30; x++) {
					int n = 8;
					vector<vector<char>> table(n, vector<char> (n, '.'));
					int now = rnd() % 2;
					for (int i = 0; i < n; i += 2) {
						for (int j = 0; j < n; j += 2) {
							table[i][j] = need[now][3];
						}
					}
					for (int i = 0; i < n; i += 2) {
						for (int j = 1; j < n; j += 2) {
							table[i][j] = need[now][1];
						}
					}
					for (int i = 1; i < n; i += 2) {
						for (int j = 0; j < n; j += 2) {
							table[i][j] = need[now][1];
						}
					}
					for (int i = 0; i < n; i++) {
						for (int j = 0; j < n; j++) {
							if (table[i][j] != '.') {
								if (rnd() % x != 0) continue;
							}
							else {
								if (rnd() % (x / 3) == 0) continue;
							}
							table[i][j] = need[now ^ 1][0];
						}
					}
					pair<int, int> fans = calc(table); 
					if (max(fans.first, fans.second) > 50) continue;
					if (mem.count(fans)) continue;
					help[fans.first][fans.second] = 1;
					mem[fans] = table;
					if (mem.size() % 100 == 0) cerr << mem.size() << endl;
					cerr << "cnt = " << mem.size() << endl;
					//cerr << fans.first << " " << fans.second << endl;
				}
			}	
		}
		if (MEGA_IT < 2) {
			cerr << "puhh7" << endl;
			for (int it = 0; it < 40000; it++) {
				for (int mod = 5; mod < 25; mod++) {
					int n = 8;
					vector<vector<char>> table(n, vector<char> (n, '.'));
					int now = rnd() % 2;
					for (int i = 0; i < n; i += 2) {
						for (int j = 0; j < n; j += 3) {
							table[i][j] = need[now][3];
						}
						for (int j = 2; j < n; j += 3) {
							table[i][j] = need[now][3];
						}
						for (int j = 1; j < n; j += 3) {
							table[i][j] = need[now][1];
						}
					}
					for (int i = 1; i < n; i += 2) {
						for (int j = 0; j < n; j += 3) {
							table[i][j] = need[now][1];
						}
						for (int j = 2; j < n; j += 3) {
							table[i][j] = need[now][1];
						}
					}
					int cnt = rnd() % 15;
					for (int i = 0; i < n; i++) {
						for (int j = 0; j < n; j++) {
							if (table[i][j] != '.') {
								if (rnd() % mod != 0) continue;
								table[i][j] = need[now][rnd() % 4];
							}
							else {
								if (cnt == 0) continue;
								cnt--;
								table[i][j] = need[now ^ 1][rnd() % 2];
							}
						}
					}
					pair<int, int> fans = calc(table); 
					if (max(fans.first, fans.second) > 50) continue;
					if (mem.count(fans)) continue;
					help[fans.first][fans.second] = 1;
					mem[fans] = table;
					if (mem.size() % 100 == 0) cerr << mem.size() << endl;
					cerr << "cnt = " << mem.size() << endl;
					//cerr << fans.first << " " << fans.second << endl;
				}
			}
			cerr << "puhh8" << endl;
			for (int it = 0; it < 40000; it++) {
				for (int mod = 5; mod < 25; mod++) {
					int n = 8;
					vector<vector<char>> table(n, vector<char> (n, '.'));
					int now = rnd() % 2;
					for (int i = 0; i < n; i += 2) {
						for (int j = 0; j < n; j += 3) {
							table[i][j] = need[now][3];
						}
						for (int j = 2; j < n; j += 3) {
							table[i][j] = need[now][3];
						}
						for (int j = 1; j < n; j += 3) {
							table[i][j] = need[now][1];
						}
					}
					for (int i = 1; i < n; i += 2) {
						for (int j = 0; j < n; j += 3) {
							table[i][j] = need[now][1];
						}
						if (i <= 5) {
							for (int j = 2; j < n; j += 3) {
								table[i][j] = need[now][1];
							}	
						}
					}
					vector<pair<int, int>> have;
					for (int i = 0; i < n; i++) {
						for (int j = 0; j < n; j++) {
							if (table[i][j] == '.') {
								have.push_back({i, j});
							}
						}
					}

					for (int i = 0; i < n; i++) {
						for (int j = 0; j < n; j++) {
							if (table[i][j] != '.') {
								if (rnd() % mod != 0) continue;
								table[i][j] = need[now][rnd() % 4];
							}
						}
					}


					int cnt = rnd() % 20;
					shuffle(all(have), rnd);
					for (auto [i, j] : have) {
						cnt--;
						if (cnt <= 0) break;
						table[i][j] = need[now ^ 1][rnd() % 2];
					}
					pair<int, int> fans = calc(table); 
					//cerr << fans.first << " " << fans.second << endl;
					if (max(fans.first, fans.second) > 50) continue;
					if (mem.count(fans)) continue;
					help[fans.first][fans.second] = 1;
					mem[fans] = table;
					if (mem.size() % 100 == 0) cerr << mem.size() << endl;
					cerr << "cnt = " << mem.size() << endl;
					//cerr << fans.first << " " << fans.second << endl;
				}
			}
			cerr << "puhh9" << endl;
			for (int it = 0; it < 40000; it++) {
				for (int mod = 5; mod < 25; mod++) {
					int n = 8;
					vector<vector<char>> table(n, vector<char> (n, '.'));
					int now = rnd() % 2;
					for (int i = 0; i < n; i += 2) {
						for (int j = 0; j < n; j += 3) {
							table[i][j] = need[now][3];
						}
						for (int j = 2; j < n; j += 3) {
							table[i][j] = need[now][3];
						}
						for (int j = 1; j < n; j += 3) {
							table[i][j] = need[now][1];
						}
					}
					for (int i = 1; i < n; i += 2) {
						for (int j = 0; j < n; j += 3) {
							table[i][j] = need[now][1];
						}
						if (i <= 5) {
							for (int j = 2; j < n; j += 3) {
								table[i][j] = need[now][1];
							}	
						}
					}
					vector<pair<int, int>> have;
					for (int i = 0; i < n; i++) {
						for (int j = 0; j < n; j++) {
							if (table[i][j] == '.') {
								have.push_back({i, j});
							}
						}
					}

					for (int i = 0; i < n; i++) {
						for (int j = 0; j < n; j++) {
							if (table[i][j] != '.') {
								if (rnd() % mod != 0) continue;
								table[i][j] = need[now][0];
							}
						}
					}


					int cnt = rnd() % 20;
					shuffle(all(have), rnd);
					for (auto [i, j] : have) {
						cnt--;
						if (cnt <= 0) break;
						table[i][j] = need[now ^ 1][0];
					}
					pair<int, int> fans = calc(table); 
					//cerr << fans.first << " " << fans.second << endl;
					if (max(fans.first, fans.second) > 50) continue;
					if (mem.count(fans)) continue;
					help[fans.first][fans.second] = 1;
					mem[fans] = table;
					if (mem.size() % 100 == 0) cerr << mem.size() << endl;
					cerr << "cnt = " << mem.size() << endl;
					//cerr << fans.first << " " << fans.second << endl;
				}
			}

			cerr << "puhh11" << endl;
			for (int it = 0; it < 2000; it++) {
				//if (it % 100 == 0)
				//cerr << it << endl;
				for (int mod = 1; mod < 40; mod++) {
					for (int mod2 = 1; mod2 < 40; mod2++) {
						int n = 8;
						vector<vector<char>> table(n, vector<char> (n, '.'));
						int now = rnd() % 2;
						for (int i = 0; i < n; i += 2) {
							for (int j = 0; j < n; j += 3) {
								table[i][j] = need[now][3];
							}
							for (int j = 2; j < n; j += 3) {
								table[i][j] = need[now][3];
							}
							for (int j = 1; j < n; j += 3) {
								table[i][j] = need[now][1];
							}
						}
						for (int i = 1; i < n; i += 2) {
							for (int j = 0; j < n; j += 3) {
								table[i][j] = need[now][1];
							}
							if (i <= 5) {
								for (int j = 2; j < n; j += 3) {
									if (rnd() % mod2 == 0) continue;
									table[i][j] = need[now][1];
								}	
							}
						}
						vector<pair<int, int>> have;
						for (int i = 0; i < n; i++) {
							for (int j = 0; j < n; j++) {
								if (table[i][j] == '.') {
									have.push_back({i, j});
								}
							}
						}

						for (int i = 0; i < n; i++) {
							for (int j = 0; j < n; j++) {
								if (table[i][j] != '.') {
									if (rnd() % mod != 0) continue;
									table[i][j] = need[now][0];
								}
							}
						}


						int cnt = rnd() % 20;
						shuffle(all(have), rnd);
						for (auto [i, j] : have) {
							cnt--;
							if (cnt <= 0) break;
							table[i][j] = need[now ^ 1][0];
						}
						pair<int, int> fans = calc(table); 
						//cerr << fans.first << " " << fans.second << endl;
						if (max(fans.first, fans.second) > 50) continue;
						if (mem.count(fans)) continue;
						help[fans.first][fans.second] = 1;
						mem[fans] = table;
						if (mem.size() % 100 == 0) cerr << mem.size() << endl;
						cerr << "cnt = " << mem.size() << endl;
						//cerr << fans.first << " " << fans.second << endl;
					}
				}
			}
			cerr << "puhh12" << endl;
			for (int it = 0; it < 2000; it++) {
				for (int mod = 5; mod < 25; mod++) {
					int n = 8;
					vector<vector<char>> table(n, vector<char> (n, '.'));
					int now = rnd() % 2;
					for (int i = 0; i < n; i += 2) {
						for (int j = 0; j < n; j += 3) {
							table[i][j] = need[now][3];
						}
						for (int j = 2; j < n; j += 3) {
							table[i][j] = need[now][3];
						}
						for (int j = 1; j < n; j += 3) {
							table[i][j] = need[now][1];
						}
					}
					for (int i = 1; i < n; i += 2) {
						for (int j = 0; j < n; j += 3) {
							table[i][j] = need[now][1];
						}
						if (i <= 5) {
							for (int j = 2; j < n; j += 3) {
								table[i][j] = need[now][1];
							}	
						}
					}
					vector<pair<int, int>> have;
					for (int i = 0; i < n; i++) {
						for (int j = 0; j < n; j++) {
							if (table[i][j] == '.') {
								have.push_back({i, j});
							}
						}
					}

					for (int i = 0; i < n; i++) {
						for (int j = 0; j < n; j++) {
							if (table[i][j] != '.') {
								if (rnd() % mod != 0) continue;
								table[i][j] = need[now][rnd() % 4];
							}
						}
					}


					int cnt = rnd() % 20;
					shuffle(all(have), rnd);
					for (auto [i, j] : have) {
						cnt--;
						if (cnt <= 0) break;
						table[i][j] = need[now ^ 1][rnd() % 2];
					}
					pair<int, int> fans = calc(table); 
					//cerr << fans.first << " " << fans.second << endl;
					if (max(fans.first, fans.second) > 50) continue;
					if (mem.count(fans)) continue;
					help[fans.first][fans.second] = 1;
					mem[fans] = table;
					if (mem.size() % 100 == 0) cerr << mem.size() << endl;
					cerr << "cnt = " << mem.size() << endl;
					//cerr << fans.first << " " << fans.second << endl;
				}
			}

		}
	}
	
	cerr << mem.size() << endl;
	for (int i = 0; i < 51; i++) {
		for (int j = 0; j < 51; j++) {
			if (help[i][j] != -1)
			cerr << help[i][j] << " ";
		}
		cerr << endl;
	}
	cerr << endl;

	//cerr << "------------------------";
	//cerr << "mem = " << endl;
	cerr << mem.size() << endl;
	cout << "vector<pair<int, int>> nums = {";

	for (auto [p, table] : mem) {
		cout << "{" << p.first << "," << p.second << "},";
	}

	cout << "}" << endl;
	cout << "vector<string> table = {";
	for (auto [p, table] : mem) {
		cout << "\"";
		for (auto i : table) for (auto j : i) cout << j;
		cout << "\",";
	}
	cout << "}";
}

void gen() {
	int n = 8;
	vector<vector<char>> table(n, vector<char> (n, '.'));
	int now = rnd() % 2;
	for (int i = 0; i < n; i += 2) {
		for (int j = 0; j < n; j += 3) {
			table[i][j] = need[now][3];
		}
		for (int j = 2; j < n; j += 3) {
			table[i][j] = need[now][3];
		}
		for (int j = 1; j < n; j += 3) {
			table[i][j] = need[now][1];
		}
	}
	for (int i = 1; i < n; i += 2) {
		for (int j = 0; j < n; j += 3) {
			table[i][j] = need[now][1];
		}
		if (i <= 5) {
			for (int j = 2; j < n; j += 3) {
				table[i][j] = need[now][1];
			}	
		}
	}
	for (auto i : table) {
		for (auto j : i) {
			cout << j << " ";
		}
		cout << endl;
	}
	int cnt = 0;
	for (int i = 0; i <= 50; i++) {
		for (int j = 0; j <= 50; j++) {
			if (i + j > 64) continue;
			cnt++;
		}
	}
	cout << cnt << endl;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	//gen();
	//return 0;
	precalc();
	return 0;
	int n = 8;
	vector<vector<char>> table(n, vector<char> (n, ' '));
	for (auto &i : table) for (auto &j : i) cin >> j;
	//cerr << check(7, 2, table) << endl;
	//return 0;
	auto ans = calc(table);
	cerr << ans.first << " " << ans.second << endl;
	/*for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (help[i][j] == -1) cerr << "X";
			else if (help[i][j] == 0) cerr << "W";
			else cerr << "B";
			cerr << " ";
			continue;
 			cerr << help[i][j] << " ";
		}
		cerr << endl;
	}*/
	return 0;
}