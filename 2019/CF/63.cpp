#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1e6 + 3;


vector <int> operator-(vector <int> a, vector <int> b) {
	vector <int> ans;
	for (int i = 0; i < a.size(); i++) {
		ans.push_back(a[i] - b[i]);
	}
	return ans;
}

vector <int> operator*(vector <int> a, int num) {
	for (int i = 0; i < a.size(); i++)
		a[i] *= num;
	return a;
}

int gcd(vector <int> a, int num) {
	int ans = num;
	for (auto i : a)
		ans = __gcd(abs(ans), abs(i));
	return ans;
} 

vector <int> operator/(vector <int> a, int num) {
	for (int i = 0; i < a.size(); i++)
		a[i] /= num;
	return a;
}

int pows(int a, int n) {
	int ans = 1;
	for (int i = 0; i < n; i++) {
		ans *= a;
		ans %= MOD;
	}
	return ans;
}

signed main() {
	//freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	vector <vector <int> > matrix;
	vector <int> num;
	int n;
	n = 11;
	//cin >> n;
	matrix.assign(n, vector <int> (n, 0));
	num.assign(n, 0);
	
	int fans;
	for (int i = 0; i < n; i++) {
		cout << "? " << i << endl;
		//cout << "puhh" << endl;
		cin >> fans;
		num[i] = fans;
		for (int j = 0; j < n; j++) {
			matrix[i][j] = pows(i, j);
		}
	}

	/*cout << "matrix = " << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << num[i] << endl;
	}*/

	for (int pos = 0; pos < n; pos++) {
		for (int need = 0; need < n; need++) {
			if (pos == need)
				continue;
			if (matrix[need][pos] == 0)
				continue;
			
			int x1 = matrix[pos][pos];
			int x2 = matrix[need][pos];
			matrix[pos] = matrix[pos] * x2;
			matrix[need] = matrix[need] * x1;
			
			num[pos] *= x2;
			num[need] *= x1;

			matrix[need] = matrix[need] - matrix[pos];
			num[need] = num[need] - num[pos];

			x1 = gcd(matrix[pos], num[pos]);
			x2 = gcd(matrix[need], num[need]);

			num[pos] /= x1;
			matrix[pos] = matrix[pos] / x1;
			
			num[need] /= x2;
			matrix[need] = matrix[need] / x2;
		}
	}


	vector <int> a;
	//cout << "ans" << endl;
	for (int i = 0; i < n; i++) {
		int x = -1;
		for (int j = 0; j < n; j++) {
	//		cout << (matrix[i][j] != 0) << " ";
			if (matrix[i][j] != 0)
				x = matrix[i][j];
		}
		int g = __gcd(abs(num[i]), abs(x));
		num[i] /= g;
		x /= g;
		if (x < 0)
			num[i] *= -1, x *= -1;
		a.push_back(num[i]);
	//	cout << num[i] << "/" << x << endl;
	}


	cout << "a = " << endl;
	for (auto i : a)
		cout << i << " ";
	cout << endl;
	cout << MOD << endl;

	for (int i = 0; i < 1e6 + 3; i++) {
		int ans = 0;
		int x = 1;
		for (int j = 0; j < n; j++) {
			ans += x * a[j];
			x *= i;
			ans %= MOD;
			x %= MOD;
		}

		if (ans == 0){
			cout << "! " << i << endl;
			return 0;
		}
	}	
	cout << "! -1" << endl;
	return 0;
}