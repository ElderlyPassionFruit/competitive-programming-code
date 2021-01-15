#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MAXK = 201;
const int MAXN = 1e5 + 10;

bitset<MAXK> can[MAXK];

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    int s, l, n;
    cin >> s >> l >> n;
    map<string, int> numb;
    set<string> name;
    vector<string> real;
    for (int i = 0; i < s; ++i){
        string s;
        cin >> s;
        name.insert(s);
        //can[i][i] = 1;
    }
    for (auto elem : name){
        real.push_back(elem);
        numb[elem] = real.size() - 1;
    }
    for (int i = 0; i < s; i++){
        for (int j = 0; j < s; j++){
            can[i][j] = 1;
        }
        can[i][i] = 0;
    }
    for (int i = 0; i < l; i++){
        string a, b;
        cin >> a >> b;
        int a1 = numb[a];
        int b1 = numb[b];
        can[a1][b1] = 0;
        can[b1][a1] = 0;
    }
    vector<int> arr(n);
    vector<vector<int> > pos(s);
    vector<int> pt(s);
    vector<int> ans;
    for (int i = 0; i < n; i++){
        string s;
        cin >> s;
        arr[i] = numb[s];
        pos[arr[i]].push_back(i);
    }
    set<pair<int, int> > ord;
    for (int i = 0; i < s; i++){
        if (pt[i] != pos[i].size())
            ord.insert({pos[i][0], i});
    }
    for (int i = 0; i < n; i++){
        int val = s + 5;
        bitset<MAXK> now;
        for (auto elem : ord){
            if ((now & can[elem.second]).count() == 0){
                val = min(val, elem.second);
            }
            now[elem.second] = 1;
        }
        ans.push_back(val);
        ord.erase({pos[val][pt[val]], val});
        pt[val]++;
        if (pt[val] < pos[val].size()){
            ord.insert({pos[val][pt[val]], val});
        }
    }
    for (auto elem : ans){
        cout << real[elem] << " ";
    }
    cout << "\n";
	return 0;
}