#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int N = 26;
const int M = 1010;

int n, m, k;

struct team{
    string name;
    char c[N];
    int a[N], t[N];
    team() {
        name = "";
    }
    void read() {
        cin >> name;
        for (int i = 0; i < n; i++) {
            cin >> c[i] >> a[i] >> t[i];
        }
    }
    int calcTasks() {
        int ans = 0;
        for (int i = 0; i < n; i++) {
            ans += c[i] == '+';
        }
        return ans;
    }
    int calcTime() {
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (c[i] != '+') continue;
            ans += (a[i] - 1) * 20 + t[i];
        }
        return ans;
    }
    int calcLast() {
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (c[i] != '+') continue;
            ans = max(ans, t[i]);
        }
        return ans;
    }
};

team getMax(team a) {
    for (int i = 0; i < n; i++) {
        if (a.c[i] == '+') continue;
        a.c[i] = '+';
        a.a[i]++;
        a.t[i] = 240;
    }
    return a;
}

team getMin(team a) {
    return a;
}

bool checkUpper(team a, team b) {
    if (a.calcTasks() != b.calcTasks()) {
        return a.calcTasks() > b.calcTasks();
    }
    if (a.calcTime() != b.calcTime()) {
        return a.calcTime() < b.calcTime();
    }
    if (a.calcLast() != b.calcLast()) {
        return a.calcLast() < b.calcLast();
    }
    return a.name < b.name;
}

team frozen[M];
team result[M];

void no() {
    cout << "Fake\n";
    exit(0);
}

void check(team a) {
    if (checkUpper(getMax(a), result[0])) return;
    if (checkUpper(result[k - 1], getMin(a))) return;
    no();
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    cin >> n >> m >> k;
    for (int i = 0; i < m; i++) {
        frozen[i].read();
    }
    set<string> setik;
    for (int i = 0; i < k; i++) {
        result[i].read();
        setik.insert(result[i].name);
    }
    for (int i = 0; i < m; i++) {
        if (setik.count(frozen[i].name)) continue;
        check(frozen[i]);
    }
    cout << "Leaked\n";
	return 0;
}