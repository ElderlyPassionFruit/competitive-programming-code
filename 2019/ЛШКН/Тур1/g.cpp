#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

pair <int, int> operator-(pair <int, int> a, pair <int, int> b) {
    return {a.first - b.first, a.second - b.second};
}


int n;
vector<pair <int, int> > a;
void read() {
    cin >> n;
    a.resize(n);
    for (auto &i : a)
        cin >> i.first >> i.second;
}

pair <int, int> make(pair <int, int> a) {
    if (a.first < 0) {
        a.first *= -1;
        a.second *= -1;
    }
    if (a.first == 0 && a.second < 0) {
        a.second *= -1;
    }
    return a;
}

int ans;

void run() {
    vector<pair <int, int> > help;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            help.push_back(make(a[i] - a[j]));
        }
    }
    sort(help.begin(), help.end());
    /*cout << "help = " << endl;
    for (auto i : help)
        cout << i.first << " " << i.second << endl;
    cout << "pos = " << endl;*/
    for (int i = 0; i < help.size(); i++) {
        int j = i + 1;
        while (j < help.size() && help[j] == help[i])
            j++;
        int x = j - i;
        //cout << i << " " << j << endl;
        ans += x * (x - 1) / 2;
        i = j - 1;
    }
    ans /= 2;
}

void write() {
    cout << ans << endl;
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