//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,avx,avx2,mmx,abm")
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int BUBEN = 4e5 + 10;
int lp[BUBEN];
vector<int> pr;

void build() {
    for (int i = 2; i < BUBEN; i++) {
        if (lp[i] == 0) {
            lp[i] = i;
            pr.push_back(i);
        }
        for (int j = 0; j < (int)pr.size() && pr[j] * i < BUBEN && pr[j] <= lp[i]; j++) {
            lp[i * pr[j]] = pr[j];
        }
    }
    while (pr.back() > 31625) pr.pop_back();
}

void get_div(int now, int pos, vector<pair<int, int>> & a, vector<int> & ans) {
    if (pos == a.size()) {
        ans.push_back(now);
        return;
    }
    for (int i = 0; i <= a[pos].second; i++) {
        get_div(now, pos + 1, a, ans);
        now *= a[pos].first;
    }
}

vector<int> get_div(int x) {
    vector<pair<int, int>> a;

    for (auto i : pr) {
        if (x < BUBEN) break;
        if (x % i) continue;
        a.push_back({i, 0});
        while (x % i == 0) {
            a[a.size() - 1].second++;
            x /= i;
        }
    }

    if (x > BUBEN) {
    	a.push_back({x, 1});
	    vector<int> ans;
	    get_div(1, 0, a, ans);
	    return ans;
    }

    while (lp[x]) {
        int now = lp[x];
        a.push_back({now, 0});
        while (x % now == 0) {
            a[a.size() - 1].second++;
            x /= now;
        }
    }

    vector<int> ans;
    get_div(1, 0, a, ans);
    return ans;
}

unordered_map<int, int> g;

int grandy(int x) {
	if (g.find(x) != g.end()) {
		return g[x];
	}
	vector<int> divs = get_div(x);
	vector<char> s(60);	
	for (int d : divs) {
		if (d != x && x / d % 2 == 1) {
			s[grandy(d)] = 1;
		} else if (d != x) {
			s[0] = 1;
		}
	}

	int cur = 0;
	while (s[cur])
		cur++;
	return g[x] = cur;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	build();
	/*for (int i = 1; i <= pr.back(); i++) {
		g_small[i] = grandy(i);
		used[i] = true;
	}*/
	int n;
	cin >> n;
	vector<int> arr(n);
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	sort(arr.begin(), arr.end());
	vector<int> arr2;
	for (int i = 0; i < n; i++) {
		if (!arr2.empty() && arr2.back() == arr[i]) {
			arr2.pop_back();
		} else {
			arr2.push_back(arr[i]);
		}
	}
	arr = arr2;
	n = arr.size();
	int ans = 0;
	for (int i = 0; i < n; i++) {
		g.clear();
		//cout << grandy(arr[i]) << " " << arr[i] << endl;
		ans ^= grandy(arr[i]);
	}
	if (ans == 0) {
		cout << "Bob" << endl;
	} else {
		cout << "Alice" << endl;
	}
	return 0;	
}