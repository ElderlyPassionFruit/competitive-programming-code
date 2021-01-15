#include <bits/stdc++.h>

using namespace std;
//#define int long long

#define matrix vector <vector <char> >

bool check_win(matrix a) {
	for (int i = 0; i < 3; i++) {
		int cnt = 0;
		for (int j = 0; j < 3; j++) {
			cnt += a[i][j] == 'x';
		}
		if (cnt == 3)
			return true;
	}
	for (int j = 0; j < 3; j++) {
		int cnt = 0;
		for (int i = 0; i < 3; i++) {
			cnt += a[i][j] == 'x';
		}
		if (cnt == 3)
			return true;
	}
	if (a[0][0] == 'x' && a[1][1] == 'x' && a[2][2] == 'x') return true;
	if (a[2][0] == 'x' && a[1][1] == 'x' && a[0][2] == 'x') return true;

	return false;
}

bool operator==(matrix a, matrix b) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (a[i][j] != b[i][j]) {
				return false;
			}
		}
	}
	return true;
}

matrix transp(matrix a) {
	matrix ans(3, vector <char> (3, '.'));
	ans[0][0] = a[2][0];
	ans[0][1] = a[1][0];
	ans[0][2] = a[0][0];

	ans[1][0] = a[2][1];
	ans[1][1] = a[1][1];
	ans[1][2] = a[0][1];

	ans[2][0] = a[2][2];
	ans[2][1] = a[1][2];
	ans[2][2] = a[0][2];

	return ans;
}

matrix mirror(matrix a) {
	matrix ans = a;
	swap(ans[0][0], ans[2][0]);
	swap(ans[0][1], ans[2][1]);
	swap(ans[0][2], ans[2][2]);
	return ans;
}

int is_transp(matrix a, matrix b) {
	if (a == b) return 0;
	for (int i = 1; i <= 3; i++) {
		b = transp(b);
		if (a == b)
			return i;
	}
	return -1;
}

matrix is_win(matrix a) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (a[i][j] != '.') continue;
			a[i][j] = 'x';
			if (check_win(a)) {
				return a;
			}
			a[i][j] = '.';
		}
	}
	return a;
}

const matrix a0 = {{'.', '.', 'o'}, {'.', 'x', '.'}, {'.', '.', '.'}};
const matrix a1 = {{'.', '.', 'o'}, {'.', 'x', '.'}, {'.', '.', 'x'}};
const matrix a2 = {{'o', '.', 'o'}, {'.', 'x', '.'}, {'.', '.', 'x'}};
const matrix a3 = {{'o', '.', 'o'}, {'.', 'x', '.'}, {'.', 'x', 'x'}};

const matrix b0 = {{'.', 'o', '.'}, {'.', 'x', '.'}, {'.', '.', '.'}};
const matrix b1 = {{'.', 'o', '.'}, {'.', 'x', 'x'}, {'.', '.', '.'}};
const matrix b2 = {{'.', 'o', '.'}, {'o', 'x', 'x'}, {'.', '.', '.'}};
const matrix b3 = {{'.', 'o', '.'}, {'o', 'x', 'x'}, {'.', '.', 'x'}};

pair <int, int> check(matrix my, matrix test) {
	if (my == test)
		return {0, 0};
	for (int i = 1; i <= 4; i++) {
		my = transp(my);
		if (my == test) {
			return {i, 0};
		}
	}
	my = mirror(my);
	if (my == test) 
		return {0, 1};
	for (int i = 1; i <= 4; i++) {
		my = transp(my);
		if (my == test) {
			return {i, 1};
		}
	}
	return make_pair(-1, -1);
}

void write(matrix a) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << a[i][j];
		}
		cout << '\n';
	}
	cout.flush();
}

matrix make(matrix a, pair <int, int> b) {
	if (b.second == 1) {
		a = mirror(a);
	}
	for (int i = 0; i < b.first; i++) {
		a = transp(a);
	}
	return a;
}

matrix play(matrix a) {
	matrix fans = is_win(a);
	if (fans != a)
		return fans;

	pair <int, int> fcheck;


	// Проверяем a 
	fcheck = check(a0, a);
	if (fcheck != make_pair(-1, -1)) {
		return make(a1, fcheck);
	}

	fcheck = check(a1, a);
	if (fcheck != make_pair(-1, -1)) {
		return make(a2, fcheck);
	}

	fcheck = check(a2, a);
	if (fcheck != make_pair(-1, -1)) {
		return make(a3, fcheck);
	}


	// Проверяем b
	fcheck = check(b0, a);
	if (fcheck != make_pair(-1, -1)) {
		return make(b1, fcheck);
	}

	fcheck = check(b1, a);
	if (fcheck != make_pair(-1, -1)) {
		return make(b2, fcheck);
	}

	fcheck = check(b2, a);
	if (fcheck != make_pair(-1, -1)) {
		return make(b3, fcheck);
	}

	return a;
}

bool stop(matrix a) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (a[i][j] != 'x')
				return false;
		}
	}
	return true;
}

const matrix start = {{'.', '.', '.'}, {'.', '.', '.'}, {'.', '.', '.'}};
const matrix Next = {{'.', '.', '.'}, {'.', 'x', '.'}, {'.', '.', '.'}};

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	while (true) {
		matrix a = start;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				cin >> a[i][j];
			}
		}
		if (stop(a)) {
			break;
		}
		if (a == start) {
			write(Next);
			continue;
		}
		a = play(a);
		write(a);
	}
	return 0;
} 