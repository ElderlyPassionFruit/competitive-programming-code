#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define pb push_back
#define all(a) (a).begin(), (a).end()
const int MOD = 1e9 + 7;
const int inf = 1e9 + 8;
const int maxn = 1e5 + 10;
//#define 
int n, d;

void cou(int a) {
	for (int i = 0; i < a - 1; i++) {
		cout << d << "+";
	}
	if (a != 0) {
		cout << d;
	}
}

void make(int a) {
	if (a == 0) return;
	cou(a % d);
	if (a / d != 0) {
		if (a % d != 0) {
			cout << "+";
		}
		cout << d << "*(";
		make(a/d);
		cout << ")";
	}
}

void make1(int a) {
	if (a % 2 == 1) {
		cout << 1;
	}
	if (a / 2 != 0) {
		if (a % 2 == 1) {
			cout << "+";
		}
		cout << "(1+1)*(";
		make1(a/2);
		cout << ")";	
	}
}

signed main() {
	// freopen("text.in", "rt", stdin);
	// freopen("text.out", "wt", stdout);
	// cout << fixed << setprecision(20);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    cin >> n >> d;
    if (n % d != 0) {
    	cout << "no solution";
    	return 0;
    }
    n /= d;
    if (d != 1) {
    	make(n);
    } else {
    	make1(n);
    }
}