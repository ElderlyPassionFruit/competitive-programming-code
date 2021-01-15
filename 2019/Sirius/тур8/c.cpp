#include <bits/stdc++.h>
 
using namespace std;
#define int long long

#define lnum vector <int>
const int MOD = 10;

lnum make(string s) {
	lnum n(s.length(), 0);
	for (int i = 0; i < s.length(); i++) {
		n[i] = s[i] - '0';
	}
	return n;
}

string s, t;
void read() {
    cin >> s >> t;
}
int ans;
void run() {
    ans = 0;
    int cntU = 0, cntD = 0;
    for (auto i : s) {
        if (i == '1' || i == '2') {
            cntD++;
        }
        else if (i == 'U') {
            cntU++;
        }
    }
    int l_s = cntD - cntU;
    cntU = cntD = 0;
    for (auto i : t) {
        if (i == '1' || i == '2') {
            cntD++;
        }
        else if (i == 'U') {
            cntU++;
        }
    }
    int l_t = cntD - cntU;
    bool flag = max(l_s, l_t) > 50;
    ans += abs(l_s - l_t);
    //cout << ans << endl;
    while (l_s > l_t) {
        s += "U";
        l_s--;
    }
    while (l_t > l_s) {
        t += "U";
        l_t--;
    }
    int v_s = 1;
    for (auto i : s) {
        if (i == '1') {
            v_s *= 2;
        }
        if (i == '2') {
            v_s *= 2;
            v_s += 1;
        }
        if (i == 'U') {
            v_s /= 2;
        }
        if (i == 'L') {
            v_s--;
        }
        if (i == 'R') {
            v_s++;
        }
    }
    int v_t = 1;
    for (auto i : t) {
        if (i == '1') {
            v_t *= 2;
        }
        if (i == '2') {
            v_t *= 2;
            v_t += 1;
        }
        if (i == 'U') {
            v_t /= 2;
        }
        if (i == 'L') {
            v_t--;
        }
        if (i == 'R') {
            v_t++;
        }
    }
    //cout << "v_t = " << v_t << " v_s = " << v_s << endl;
    int fans = 1e18;
	if (flag)
		fans = abs(v_s - v_t);
	else{
	    int need = 0;
	    while (v_s && v_t) {
	        int help = need + abs(v_s - v_t);
	        fans = min(fans, help);
	        need += 2;
	        v_s /= 2;
	        v_t /= 2;
	    }
	}
    ans += fans;
}
 
void write() {
	unsigned long long for_out = ans;
    cout << for_out << endl;
}
 
signed main() {
    freopen("board.in", "r", stdin);
    freopen("board.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);    
    read();
    run();
    write();
    return 0;
}