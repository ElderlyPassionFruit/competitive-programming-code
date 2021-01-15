#include <bits/stdc++.h>
 
using namespace std;
#define int long long
 
const int MAXN = 1e7 + 10;
int arr[MAXN][2];
int n, m;
set <int> h1, h2;
 
int sq(int x) {
    return x * x;
}
 
int dist(pair <int, int> a, pair <int, int> b) {
    return sq(a.first - b.first) + sq(a.second - b.second);
}
 
signed main() {
    freopen("tram.in", "r", stdin);
    freopen("tram.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    vector <pair <int, int> > fhelp;
    vector <pair <int, int> > fout;
    int cnt = 0;
 
    for (int test = 0; test < m; test++) {
        // /    cout << endl;
        //cout << "test = " << test << endl;
        char x;
        cin >> x;
        if (x == 'E') {
            pair <int, int> fans;
             
 
            if (cnt > 0) {
                int ans = -1e9;
                int last1 = -1e9, last2 = -1e9;
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < 2; j++) {
                        if (arr[i][j]) {
                            if (j == 0)
                                last1 = i;
                            else
                                last2 = i;
                            continue;
                        }
 
                        auto it1 = h1.lower_bound(i);
                        auto it2 = h2.lower_bound(i);
 
                        int h = min(dist({last1, 0}, {i, j}), dist({last2, 1}, {i, j}));
 
                        if (it1 != h1.end()) {
                            int pos = *it1;
                            pair <int, int> help = {pos, 0};
                            h = min(h, dist(help, {i, j}));
                        }
 
                         
                        if (it2 != h2.end()) {
                            int pos = *it2;
                            pair <int, int> help = {pos, 1};
                            h = min(h, dist(help, {i, j}));
                        }
                        //cout << "help! " << "h = " <<  h << " ans = " << ans << " i = " << i << " j = " << j << endl;
                        if (h > ans) {
                        //  cout << "help! " << "h = " <<  h << " ans = " << ans << " i = " << i << " j = " << j << endl;
                            ans = h;
                            fans = {i, j};
                        }
                    }
                }
            }
            else {
                fans = {0, 0};
            }
            fhelp.push_back(fans);
            if (fans.second == 0)
                h1.insert(fans.first);
            else
                h2.insert(fans.first);
            arr[fans.first][fans.second] = 1;
            fout.push_back(fans);
            //cout << endl;
            //cout << fans.first + 1 << " " << fans.second + 1 << endl;
            cnt++;
        }
        else if (x == 'L') {
            int pos;
            cin >> pos;
            pos--;
            pair <int, int> fans = fhelp[pos];
            arr[fans.first][fans.second] = 0;
            if (fans.second == 0)
                h1.erase(fans.first);
            else
                h2.erase(fans.first);
            cnt--;
            fhelp.push_back(fans);
        }
    /*  cout << "h1 = ";
        for (auto i : h1) {
            cout << i << " ";
        }           
        cout << endl;
        cout << "h2 = ";
        for (auto i : h2) {
            cout << i << " ";
        }
        cout << endl;*/
    }
    //cout << endl;
    for (auto i : fout) {
        cout << i.first + 1 << " " << i.second + 1 << endl;
    }
    return 0;
}