#pragma GCC optimize("O3")
#include <bits/stdc++.h>
 
using namespace std;
const int MAXN = 5*1e5 + 10;

int fans[MAXN];
set <int> g[MAXN];
stack <int> ans, st;
bool used[MAXN];
int n, m, first = 0, pos = 0;

void read() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int v, u;
        cin >> v >> u;
        v--;
        u--;
        g[v].insert(u);
        g[u].insert(v);
    }
}
 
set <int> ed[MAXN];
void run2() {
    st.push (first);

    while (!st.empty())
    {
    	/*int v = st.top();
    	cout << "v = " << v << endl;
    	

    	for (auto u : g[v]) {
    		if(ed[v].count(u) == 0) {
    			st.push(u);
    			ed[v].insert(u);
    			ed[u].insert(v);
    		}
    	}

    	fans[pos++] = v;
    	st.pop();
*/

        int v = st.top();
        if (g[v].size() == 0)
        {
            fans[pos++] = v;
            st.pop();
        }
        else
        {
            int u = *g[v].begin();
            g[v].erase(u);
            g[u].erase(v);
            st.push (u);
        }
    }
}

void run() {
	run2();
	/*for (int i = 0; i < pos; i++)
		cout << fans[i] + 1 << " ";
	cout << endl;
    */for (int i = 0; i < pos; i++) {
        int new_v = fans[i];
        if (!used[new_v]) {
           	used[new_v] = true;
            ans.push(new_v);
        }
        else {
            while (ans.top() != new_v) {
                cout << ans.top() + 1 << " ";
                used[ans.top()] = false;
                ans.pop();
            }
            cout << new_v + 1 << '\n';
        }
    }
}
 
 
signed main() {
    freopen("postmen.in", "r", stdin);
    freopen("postmen.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    read();
    run();
    return 0;
}