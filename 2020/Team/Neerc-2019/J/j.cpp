#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int N = 41;
int n;
string words[N];
int x;
vector<string> have;

void delH(string& s) {
    string ans = "";
    for (auto i : s) {
        if (i == '#') break;
        ans += i;
    }
    s = ans;
}

vector<string> myWords;

void genWords(string s) {
    for (int i = 0; i < s.size(); ++i) {
        if (i == ' ') continue;
        
    }
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> words[i];
    }
    cin >> x;
    string s;
    getline(cin, s);
    for (int i = 0; i < x; ++i) {
        string s;
        getline(cin, s);
        delH(s);
        genWords(s);
        have.push_back(s);
    }

	return 0;
}