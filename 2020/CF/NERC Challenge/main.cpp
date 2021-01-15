#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

int n, m;
vector<int> nowPos;
vector<int> needPos;

vector<int> sC;
vector<int> sM;
vector<int> nowC;
vector<int> nowM;


vector<int> vmC;
vector<int> vmM;
vector<int> pos;

void read() {
    cin >> n >> m;
    sC.resize(n);
    sM.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> sC[i] >> sM[i];
    }
    vmC.resize(m);
    vmM.resize(m);
    for (int i = 0; i < m; ++i) {
        cin >> vmC[i] >> vmM[i];
    }
    nowPos.resize(m);
    needPos.resize(m);
    for (int i = 0; i < m; ++i) {
        cin >> nowPos[i];
        cin >> needPos[i];
        sC[nowPos[i]] -= vmC[i];
        sM[nowPos[i]] -= vmM[i];
    }
    pos = nowPos;
    nowC = sC;
    nowM = sM;
}

vector<vector<int>> myMoves;
vector<vector<vector<int>>> ans, realAns;

ld calc(vector<vector<vector<int>>> now) {
    int have = 0;
    for (auto i : now) {
        for (auto j : i) {
            have += vmM[j[2]];
        }
    }   
    return have * now.size();
}

void relax() {
    if (realAns.empty() || calc(ans) < calc(realAns)) {
        swap(ans, realAns);
    }
    ans.clear();
}

void mergeMoves() {
    vector<int> oldC = nowC;
    vector<int> oldM = nowM;
    sC = nowC;
    sM = nowM;

    for (int l = 0; l < myMoves.size(); ++l) {
        nowC = sC;
        nowM = sM;
        vector<int> cntQ(n, 0);
        int r = l;
        set<int> used;
        while (r < myMoves.size()) {
            int from = myMoves[r][0];
            int to = myMoves[r][1];
            int ind = myMoves[r][2];
            if (used.count(ind)) break;
            if (cntQ[from] == 2) break;
            if (cntQ[to] == 2) break;
            if (nowC[to] - vmC[ind] < 0) break;
            if (nowM[to] - vmM[ind] < 0) break;
            used.insert(ind);
            cntQ[from]++;
            cntQ[to]++;
            nowC[to] -= vmC[ind];
            nowM[to] -= vmM[ind];
            ++r;
        }
        ans.push_back({});
        for (int x = l; x < r; ++x) {
            ans[ans.size() - 1].push_back(myMoves[x]);
            int from = myMoves[x][0];
            int to = myMoves[x][1];
            int ind = myMoves[x][2];
            sC[from] += vmC[ind];
            sM[from] += vmM[ind];
            sC[to] -= vmC[ind];
            sM[to] -= vmM[ind];
        }
        l = r - 1;
    }
    nowC = oldC;
    nowM = oldM;
}

vector<set<int>> myVm;

void addQuery(int from, int to, int ind) {
    myVm[from].erase(ind);
    myVm[to].insert(ind);
    myMoves.push_back({from, to, ind});
    sC[from] += vmC[ind];
    sM[from] += vmM[ind];
    sC[to] -= vmC[ind];
    sM[to] -= vmM[ind];
    nowPos[ind] = to;
}

void smartSwap(int i, int j, int pos) {
    if (vmM[i] > vmM[j]) swap(i, j);
    int posI = nowPos[i];
    int posJ = nowPos[j];
    addQuery(posI, pos, i);
    addQuery(posJ, posI, j);
    addQuery(pos, posJ, i);
}

void mySwap(int i, int j) {
    int nowI = nowPos[i];
    int needI = needPos[i];
    addQuery(nowI, needI, i);
    addQuery(needI, nowI, j);
}

void myMove(int i) {
    int nowI = nowPos[i];
    int needI = needPos[i];
    addQuery(nowI, needI, i);
}

bool checkSwap(int i, int j) {
    if (sC[nowPos[j]] - vmC[i] < 0) return false;
    if (sM[nowPos[j]] - vmM[i] < 0) return false;
    if (sC[nowPos[i]] - vmC[j] < 0) return false;
    if (sM[nowPos[i]] - vmM[j] < 0) return false;
    return true;
}

bool checkSmartSwap(int i, int j, int pos) {
    if (vmM[i] > vmM[j]) swap(i, j);
    if (sC[pos] - vmC[i] < 0) return false;
    if (sM[pos] - vmM[i] < 0) return false;
    if (sC[nowPos[i]] + vmC[i] - vmC[j] < 0) return false;
    if (sM[nowPos[i]] + vmM[i] - vmM[j] < 0) return false;
    if (sC[nowPos[j]] + vmC[j] - vmC[i] < 0) return false;
    if (sM[nowPos[j]] + vmM[j] - vmM[i] < 0) return false;
    return true;
}

bool checkMove(int i) {
    return sC[needPos[i]] - vmC[i] >= 0 && sM[needPos[i]] - vmM[i] >= 0;
}

bool checkMove(int i, int pos) {
    return sC[pos] - vmC[i] >= 0 && sM[pos] - vmM[i] >= 0;
}

mt19937 rnd(time(0));

void tryPath(int v, vector<int>& used, vector<int>& nowC, vector<int>& nowM, vector<int>& path) {
    used[nowPos[v]]++;
    used[needPos[v]]++;
    nowC[needPos[v]] -= vmC[v];
    nowM[needPos[v]] -= vmM[v];
    path.push_back(v);
    for (auto i : myVm[needPos[v]]) {
        if (nowPos[i] == needPos[i]) continue;
        if (used[nowPos[i]] == 2) continue;
        if (used[needPos[i]] == 2) continue;
        if (nowC[needPos[i]] - vmC[i] < 0) continue;
        if (nowM[needPos[i]] - vmM[i] < 0) continue;
        tryPath(i, used, nowC, nowM, path);
        break;
    }
} 

bool tryPath(int v) {
    if (nowPos[v] == needPos[v]) return false; 
    if (!checkMove(v)) return false;
    vector<int> nowC = sC, nowM = sM;
    vector<int> used(n, 0);
    vector<int> path;
    tryPath(v, used, nowC, nowM, path);
    for (auto i : path) {
        myMove(i);
    }
    return true;
}

void solve(bool shuff) {
    sC = nowC;
    sM = nowM;
    nowPos = pos;
    myMoves.clear();
    ans.clear();
 
    /*cout << "sC = " << endl;
    for (auto i : sC) cout << i <<" ";
    cout << endl;
    cout << "sM = " << endl;
    for (auto i : sM) cout << i <<" ";
    cout << endl;
    for (auto i : vmC) cout << i <<" ";
    cout << endl;
    cout << "vmM = " << endl;
    for (auto i : vmM) cout << i <<" ";
    cout << endl;*/
 
    myVm.assign(n, {});
    for (int i = 0; i < m; ++i) {
        myVm[nowPos[i]].insert(i);
    }
 
    vector<int> order(m);
    iota(all(order), 0);
    if (shuff) {
        shuffle(all(order), rnd);
    }


    /*int needMoves = 0;
    for (int i = 0; i < m; ++i) {
        needMoves += nowPos[i] != needPos[i];   
    }

    for (int i = 0; i * 50 < needMoves; ++i) {
        int ind1 = (ull)rnd() % m;
        for (int it = 0; it < 10; ++it) {
            int ind2 = (ull)rnd() % m;
            if (nowPos[ind1] == nowPos[ind2]) continue;
            if (!checkSwap(ind1, ind2)) continue;
            //if (nowPos[ind] == pos) continue;
            //if (!checkMove(ind, pos)) continue;
            //addQuery(nowPos[ind], pos, ind);
            mySwap(ind1, ind2);
            break;
        }
    }*/

    while (true) {
        bool ok = false;
        for (auto i : order) {
            ok |= tryPath(i);
        }
        if (!ok) break;
    }

    int cntSmart = 0;

    while (true) {
        bool ok = false;
        bool relaxed = false;
        for (auto i : order) {
            if (needPos[i] == nowPos[i]) continue;
            ok = true;
            //for (auto j : order) {
            for (auto j : myVm[needPos[i]]) {
                if (needPos[j] == nowPos[j]) continue;
                if (nowPos[j] != needPos[i]) continue;
                if (nowPos[i] != needPos[j]) continue;
                if (!checkSwap(i, j)) continue;
                mySwap(i, j);
                relaxed = true;
                break;
            }
        }
        if (relaxed) continue;
        for (auto i : order) {
            if (needPos[i] == nowPos[i]) continue;
            ok = true;
            if (checkMove(i)) {
                myMove(i);
                relaxed = true;
                continue;
            }
        }
        /*for (auto i : order) {
            if (needPos[i] == nowPos[i]) continue;
            ok = true;
            if (checkMove(i)) {
                myMove(i);
                relaxed = true;
                continue;
            }
            //for (auto j : order) {
            for (auto j : myVm[needPos[i]]) {
                if (needPos[j] == nowPos[j]) continue;
                if (nowPos[j] != needPos[i]) continue;
                if (!checkSwap(i, j)) continue;
                mySwap(i, j);
                relaxed = true;
                break;
            }
        }*/
        if (relaxed) continue;
        for (auto i : order) {
            if (needPos[i] == nowPos[i]) continue;
            ok = true;
            //for (auto j : order) {
            for (auto j : myVm[needPos[i]]) {
                if (needPos[j] != nowPos[i]) continue;
                if (needPos[j] == nowPos[j]) continue;
                if (nowPos[j] != needPos[i]) continue;
                for (int pos = 0; pos < n; ++pos) {
                    if (nowPos[i] == pos || nowPos[j] == pos) continue;
                    if (!checkSmartSwap(i, j, pos)) continue;
                    smartSwap(i, j, pos);
                    relaxed = true;
                    break;
                }
                if (relaxed) break;
            }
        }
        if (relaxed) continue;
        for (auto i : order) {
            if (needPos[i] == nowPos[i]) continue;
            ok = true;
            //for (auto j : order) {
            for (auto j : myVm[needPos[i]]) {
                if (needPos[j] != nowPos[i]) continue;
                if (needPos[j] == nowPos[j]) continue;
                if (nowPos[j] != needPos[i]) continue;
                for (int pos = 0; pos < n; ++pos) {
                    if (nowPos[i] == pos || nowPos[j] == pos) continue;
                    if (!checkSmartSwap(i, j, pos)) continue;
                    smartSwap(i, j, pos);
                    cntSmart++;
                    relaxed = true;
                    break;
                }
                if (relaxed) break;
            }
        }
        if (relaxed) continue;
        for (auto i : order) {
            if (needPos[i] == nowPos[i]) continue;
            ok = true;
            //for (auto j : order) {
            for (auto j : myVm[needPos[i]]) {
                if (needPos[j] == nowPos[j]) continue;
                if (nowPos[j] != needPos[i]) continue;
                for (int pos = 0; pos < n; ++pos) {
                    if (nowPos[i] == pos || nowPos[j] == pos) continue;
                    if (!checkSmartSwap(i, j, pos)) continue;
                    smartSwap(i, j, pos);
                    cntSmart++;
                    relaxed = true;
                    break;
                }
                if (relaxed) break;
            }
        }
        if (!ok) break;
        if (!relaxed) return;
        //assert(relaxed);
    }
    //cerr << "puhh" << endl;
    mergeMoves();
    //assert(cntSmart <= 100);
    relax();
}
void run() {
    solve(1);
    //return;
    double t = clock() / CLOCKS_PER_SEC;
    while ((double)clock() / CLOCKS_PER_SEC < 6 - t) {
    //for (int it = 0; it < 10; ++it) {
    //    cerr << "it = " << it << endl;
        solve(1);
    }
}

void write() {
    cout << realAns.size() << '\n';
    for (auto i : realAns) {
        cout << i.size() << '\n';
        for (auto x : i) {
            for (auto k : x) {
                cout << k << ' ';
            }
            cout << '\n';
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
    read();
    run();
    write();
    return 0;
}