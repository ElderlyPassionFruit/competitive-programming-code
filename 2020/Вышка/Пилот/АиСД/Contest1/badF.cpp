#include <iostream>

using namespace std;

const int SZ = 1e5 + 10;

int n, m;
int dsu[SZ];
pair<int, long long> anc[SZ];
long long sum = 0;

void build() {
    for (int i = 1; i <= n; i++) {
        dsu[i] = i;
        anc[i] = { -1, 0 };
    }
}

int get(int x) {
    if (dsu[x] != x)
        dsu[x] = get(dsu[x]);
    return dsu[x];
}

void unite(int x, int y) {
    x = get(x);
    y = get(y);
    if (rand() & 1)
        swap(x, y);
    dsu[x] = y;
}

void upd_root(int v) {
    int root = v;
    int now = anc[v].first;
    for (int u = now; u != -1; u = now) {
        now = anc[u].first;
        anc[u] = { v, anc[v].second };
        v = u;
    }
    anc[root] = { -1, 0 };
}

void print_struct() {
    cout << "START PRINT\n";
    for (int i = 1; i <= n; i++) {
        cout << i << " : " << anc[i].first << ' ' << anc[i].second << "\n";
    }
    cout << "FINISH PRINT\n";
}

void do_query(int a, int b, long long w) {
    if (get(a) == get(b)) {
        upd_root(a);
        int c = b;
        for (int now = b; now != a; now = anc[now].first) {
            if (anc[now].second > anc[c].second) {
                c = now;
            }
        }
        if (anc[c].second <= w) {
            return;
        }
        sum -= anc[c].second;
        anc[c] = { -1, 0 };
    }
    
    upd_root(a);
    upd_root(b);
    unite(a, b);
    anc[a] = { b, w };
    sum += w;
}

int main()
{
    cin >> n >> m;
    build();
    for (int i = 0; i < m; i++) {
        long long a, b, w;
        cin >> a >> b >> w;
        if (a != b)
            do_query(a, b, w);
        cout << sum << "\n";
    }
    return 0;
}
