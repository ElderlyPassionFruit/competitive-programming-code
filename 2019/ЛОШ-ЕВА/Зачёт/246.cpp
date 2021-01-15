#include <iostream>
#include <vector>

using namespace std;

void merge(vector <long long> &d1, vector <long long> &d2, long long add, long long p){
    vector <long long> nw;
    int n1 = 0, n2 = 0;
    while (n1 < d1.size() || n2 < d2.size()){
        if (n1 != d1.size() && (n2 == d2.size() || d1[n1] < d2[n2] + add)){
            if (nw.size() >= 2) {
                long long now = d1[n1];
                long long p2 = nw[nw.size() - 2];
                if ((p2 + 1) * (p) >= now * (p - 1)) {
                    nw.pop_back();
                }
            }
            nw.push_back(d1[n1]);
            n1++;
        }
        else {
            if (nw.size() >= 2) {
                long long now = d2[n2] + add;
                long long p2 = nw[nw.size() - 2];
                if ((p2 + 1) * (p) >= now * (p - 1)) {
                    nw.pop_back();
                }
            }
            nw.push_back(d2[n2] + add);
            n2++;
        }
    }
    d1 = nw;
}

void solve(){
    int n, m, q, p;
    cin >> n >> m >> q >> p;
    vector <vector <pair <int, long long> > > gr(n);
    for (int i = 0; i < m; i++){
        int u, v;
        long long w;
        cin >> u >> v >> w;
        u--;
        v--;
        gr[u].push_back({v, w});
    }
    vector <vector <long long> > dp(n);
    dp[0].push_back(0);
    for (int i = 0; i < n; i++){
        for (auto ptr: gr[i]){
            merge(dp[ptr.first], dp[i], ptr.second, p);
        }
    }
    for (int i = 0; i < q; i++){
        int f;
        long long r;
        cin >> f >> r;
        f--;
        int left = -1, right = dp[f].size();
        while (right - left > 1){
            int mid = (right + left) / 2;
            if (dp[f][mid] >= r){
                right = mid;
            }
            else {
                left = mid;
            }
        }
        if (right != dp[f].size()){
            if (dp[f][right] * (p - 1) <= r * p){
                cout << 1;
            }
            else {
                cout << 0;
            }
        }
        else {
            cout << 0;
        }
    }
    cout << endl;
}

int main() {
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        solve();
    }
    return 0;
}