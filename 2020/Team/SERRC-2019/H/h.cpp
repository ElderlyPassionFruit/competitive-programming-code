#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

#define int ll

int M = 1099511627776;
int S = 1611516670;

void nxt() {
    S = (S + (S >> 20) + 12345) % M;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    /*
    cout << S % 2 << " ";
    for (int i = 0; i < 1000; ++i) {
        nxt();
        cout << S % 2 << " ";
    }
    cout << endl;*/
    set<int> have;
    have.insert(S);
    
    for (int i = 0; i < 1e8; ++i) {
        nxt();
        if (have.count(S)) {
            cout << "i = " << i << endl;
        }
        have.insert(S);
    }
	return 0;
}