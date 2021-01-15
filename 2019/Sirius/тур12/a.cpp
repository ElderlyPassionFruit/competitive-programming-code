#include <bits/stdc++.h>
 
using namespace std;

int n, m;
map <pair <int, int>, int > a;
void read() {
    cin >> n >> m;
    if (m == 2) {
    	cout << -1 << endl;
    	exit(0);
    }
    for (int i = 0; i < n; i++){
    	int x, y;
    	cin >> x >> y;
    	if (x > y) swap(x, y);
    	a[{x, y}]++;
    }
}
  
void run() {
	vector <pair <int, int> > help;
	for (auto i : a) {
		if (i.second > 1)
			help.push_back(i.first);
	}

	set <int> fans;

	for (auto i : help) {
		fans.insert(i.first);
		fans.insert(i.second);
	}

	for (int i = 1; i <= m; i++) {
		if (fans.find(i) == fans.end()) {
			cout << 1 << endl << i << endl;
			return;
		}
	}

	map <int, set <int> > help2;

	for (auto i : help) {
		help2[i.first].insert(i.second);
		help2[i.second].insert(i.first);
	}

	for (auto i : help2) {
		if (i.second.size() != m) {
			for (int c = 1; c <= m; c++) {
				if (c == i.first)
					continue;
				if (i.second.find(c) == i.second.end()) {
					cout << 2 << endl;
					cout << i.first << " " << c << endl;
					return;
				}
			}
		}
	}

    cout << 3 << endl;
    cout << "1 2 3" << endl;
}
 
void write() {
 
}
 
signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    read();
    run();
    write();
    return 0;
}