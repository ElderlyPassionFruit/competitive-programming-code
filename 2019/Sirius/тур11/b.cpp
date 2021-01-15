#include <bits/stdc++.h>
 
using namespace std;
#define int long long
int n, q;
const int MAXN = 1e6 + 10;
int arr[MAXN];
void read() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
}

int pos[32], bad[32], pows[32];
void make() {
	pows[0] = 1;
	for (int i = 1; i < 32; i++) {
		pows[i] = pows[i - 1] * 2;
	}
    for (int i = 1; i < n; i++) {
        int a, b;
        a = arr[i - 1];
        b = arr[i];
        if (a <= b) {
            a ^= b;
            int p = -1;
            while (a) {
                a /= 2;
                p++;
            }
            bad[p]++;
        }
        else {
            a ^= b;
            int p = -1;
            while (a) {
                a /= 2;
                p++;
            }
            pos[p]++;
        }
    }
}

void insert(int a, int b) {
    if (a <= b) {
        a ^= b;
        int p = -1;
        while (a) {
            a /= 2;
            p++;
        }
        bad[p]++;
    }
    else {
        a ^= b;
        int p = -1;
        while (a) {
            a /= 2;
            p++;
        }
        pos[p]++;
    }
}

void erase(int a, int b) {
	if (a <= b) {
        a ^= b;
        int p = -1;
        while (a) {
            a /= 2;
            p++;
        }
        bad[p]--;
    }
    else {
        a ^= b;
        int p = -1;
        while (a) {
            a /= 2;
            p++;
        }
        pos[p]--;
    }
}

void fans(int pos, int val) {
	if (pos > 0) {
		erase(arr[pos - 1], arr[pos]);
	}
	if (pos < n - 1) {
		erase(arr[pos], arr[pos + 1]);
	}
	arr[pos] = val;
	if (pos > 0) {
		insert(arr[pos - 1], arr[pos]);
	}
	if (pos < n - 1) {
		insert(arr[pos], arr[pos + 1]);
	}
}

void get_ans() {
	int b = 0;
	for (int i = 0; i < 32; i++) {
		if (pos[i] > 0 && bad[i] > 0) {
			cout << "-1\n";
			return;
		}
		if (pos[i] > 0) {
			b += pows[i];
		}
	}
	cout << b << '\n';
}
 
void run() {
	make();
	get_ans();
	int q;
	cin >> q;
	while (q--) {
		int pos, val;
		cin >> pos >> val;
		pos--;
		fans(pos, val);
		get_ans();
	}
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