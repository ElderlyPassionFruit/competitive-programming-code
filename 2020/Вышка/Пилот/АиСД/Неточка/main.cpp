#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

string query(string s) {
    cout << s << endl;
    int x;
    cin >> x;
    if (x >= 1000) {
        exit(0);
    }
    string ans;
    cin >> ans;
    return ans;
}

const int LEN = 100;

vector<pair<int, int>> borders;
vector<queue<int>> queries;
string last;

string getMove(string now) {
    string ans(LEN, 'N');
    /*for (auto [l, r] : borders) {
        int pos = l;
        while (now[pos] != 'd' && now[pos] != 'D') ++pos;
        int posL = pos, posR = pos;
        while (posL >= l && now[posL] != '1' && now[posL] != '2' && now[posL] != '3') --posL;
        while (posR <= r && now[posR] != '1' && now[posR] != '2' && now[posR] != '3') ++posR;
        if (posL == l - 1) {
            if (posR == r + 1) {
                if (pos < (l + r) / 2) {
                    ans[pos] = 'R';
                } else if (pos > (l + r) / 2) {
                    ans[pos] = 'L';
                } else {
                    ans[pos] = 'S';
                }
            } else {
                ans[pos] = 'R';
            }
        } else if (posR == r + 1) {
            ans[pos] = 'L';
        } else if (pos - posL <= posR - pos) {
            ans[pos] = 'L';
        } else {
            ans[pos] = 'R';
        }
    }*/
    int ind = 0;
    for (auto [l, r] : borders) {
        while (!queries[ind].empty() && (now[queries[ind].front()] != '1' && now[queries[ind].front()] != '2' && now[queries[ind].front()] != '3')) {
            queries[ind].pop();
        }
        for (int i = l; i <= r; ++i) {
            if (last[i] == '0' && (now[i] == '1' || now[i] == '2' || now[i] == '3')) {
                queries[ind].push(i);
            }
        }
        int pos = l;
        while (now[pos] != 'd' && now[pos] != 'D') ++pos;
        
        if (queries[ind].empty()) {
            if (pos - l < r - pos) {
                ans[pos] = 'R';
            } else if (pos - l > r - pos) {
                ans[pos] = 'L';
            } else {
                ans[pos] = 'S';
            }
        } else {
            int need = queries[ind].front();
            if (need < pos) {
                ans[pos] = 'L';
            } else {
                ans[pos] = 'R';
            }
        }
        ++ind;
    }
    return ans;
}

mt19937 rnd(time(0));

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
    int k;
    cin >> k;
    string s(LEN, '0');
    int x = 100 / k;
    vector<int> pos;
    for (int i = 0, cnt = 0; i < LEN && cnt < k; i += x, ++cnt) {
        s[i] = '1';
        pos.push_back(i);
    }
    /*for (int i = 0; i < k; ++i) {
        s[i] = '1';
    }
    shuffle(all(s), rnd);
    */
    for (int i = 0; i < LEN; ++i) {
        if (s[i] == '0') continue;
        pos.push_back(i);
    }

    if (pos.size() == 1) {
        borders.push_back({0, LEN - 1});
    } else {
        for (int i = 0; i < k; ++i) {
            int l = (i == 0 ? 0 : (pos[i] + pos[i - 1]) / 2 + 1);
            int r = (i == k - 1 ? LEN - 1 : (pos[i + 1] + pos[i]) / 2);
            borders.push_back({l, r});
        }
    }
    queries.resize(borders.size());

    /*cerr << "borders = " << endl;
    for (auto i : borders) {
        cerr << i.first << " " << i.second << endl;
    }*/

    s = query(s);
    last = string(LEN, '0');
    while (true) {
        /*for (int i = 0; i < s.size(); ++i) {
            if (s[i] == 'd' || s[i] == 'D') {
                s[i] = 'L';
            } else {
                s[i] = 'N';
            }
        }*/
        auto x = s;
        s = getMove(s);
        last = x;
        s = query(s);
    }
    return 0;
}