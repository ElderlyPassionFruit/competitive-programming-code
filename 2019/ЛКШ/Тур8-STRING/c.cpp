#include <bits/stdc++.h>

using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct node {
    int lett[26], go[26];
    vector<int> ed;
    int suff;
    vector<int> term;
    bool used;
    node() {
        used = false;
        for (int i = 0; i < 26; i++) {
            lett[i] = go[i] = -1;
        }
    }
};

const int MAXN = 1e6 + 10;
int have = 1;
node tree[MAXN];

void add(int ind, string & s, int x) {
    int n = s.size();
    for (int i = 0; i < n; i++) {
        if (tree[ind].lett[s[i] - 'a'] == -1)
            tree[ind].lett[s[i] - 'a'] = have++;
        ind = tree[ind].lett[s[i] - 'a'];
    }
    tree[ind].term.push_back(x);
}

struct event{
    int tree;
    int parent;
    int type;
    int x;
    event(int a, int b, int c, int d) {
        tree = a, parent = b, type = c, x = d;
    }
};

void bfs(int ind) {
    deque <event> q;
    q.push_back({ind, ind, 0, 0});
    while (!q.empty()) {
        int v = q[0].tree;
        int par = q[0].parent;
        int type = q[0].type;
        int x = q[0].x;
        q.pop_front();

        if (type == 0) {
            for (int i = 0; i < 26; i++) {
                if (tree[par].lett[i] != -1)
                    tree[v].go[i] = tree[par].lett[i];
                else
                    tree[v].go[i] = par;
            }
            tree[v].suff = v;
        }
        else if (type == 1) {
            tree[v].suff = par;
            tree[par].ed.push_back(v);
            for (int i = 0; i < 26; i++) {
                if (tree[v].lett[i] == -1)
                    tree[v].go[i] = tree[tree[v].suff].go[i];
                else
                    tree[v].go[i] = tree[v].lett[i];
            }
        }
        else {
            tree[v].suff = tree[tree[par].suff].go[x];
            tree[tree[tree[par].suff].go[x]].ed.push_back(v);
            for (int i = 0; i < 26; i++) {
                if (tree[v].lett[i] == -1)
                    tree[v].go[i] = tree[tree[v].suff].go[i];
                else
                    tree[v].go[i] = tree[v].lett[i];
            }
        }

        for (int i = 0; i < 26; i++) {
            if (tree[v].lett[i] != -1)
                q.push_back({tree[v].lett[i], v, type + 1, i});
        }
    }
}

void make_path(int ind, string & s) {
    int n = s.size();
    for (int i = 0; i < n; i++) {
        ind = tree[ind].go[s[i] - 'a'];
        tree[ind].used = true;
    }
}   

vector<bool> ans;

bool dfs(int ind) {
    bool flag = false;
    for (auto i : tree[ind].ed)
        flag |= dfs(i);

    flag |= tree[ind].used;
    
    for (auto i : tree[ind].term) {
        ans[i] = flag;
    }

    return flag;
}

int n;
void read() {
    for (int i = 0; i < MAXN; i++)
        tree[i] = node();

    cin >> n;
    ans.assign(n, false);
    for (int i = 0; i < n; i++) {
        string x;
        cin >> x;
        add(0, x, i);
    }
    bfs(0);
}

void run() {
    string t;
    cin >> t;
    make_path(0, t);
    dfs(0);
}

void write() {
    for (auto i : ans) {
        if (i)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
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