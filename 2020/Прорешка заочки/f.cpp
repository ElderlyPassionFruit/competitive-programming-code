#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

namespace fast {
    /** Fast input-output */
     
    template <class T = int> inline T readInt();                        
    inline double readDouble();
    inline int readUInt();                   
    inline int readChar(); // first non-blank character
    inline void readWord(char *s); 
    inline bool readLine(char *s); // do not save '\n'
    inline bool isEof();
    inline int getChar(); 
    inline int peekChar();
    inline bool seekEof();
    inline void skipBlanks();
     
    template <class T> inline void writeInt(T x, char end = 0, int len = -1);
    inline void writeChar(int x); 
    inline void writeWord(const char *s);
    inline void writeDouble(double x, int len = 0);
    inline void flush();
     
    static struct buffer_flusher_t {
        ~buffer_flusher_t() {
            flush();
        }
    } buffer_flusher;
     
    /** Read */
     
    static const int buf_size = 4096;
     
    static unsigned char buf[buf_size];
    static int buf_len = 0, buf_pos = 0;
     
    inline bool isEof() {
        if (buf_pos == buf_len) {
            buf_pos = 0, buf_len = fread(buf, 1, buf_size, stdin);
            if (buf_pos == buf_len)
                return 1;
        }
        return 0;
    }
     
    inline int getChar() { 
        return isEof() ? -1 : buf[buf_pos++];
    }
     
    inline int peekChar() { 
        return isEof() ? -1 : buf[buf_pos];
    }
     
    inline bool seekEof() { 
        int c;
        while ((c = peekChar()) != -1 && c <= 32)
            buf_pos++;
        return c == -1;
    }
     
    inline void skipBlanks() {
        while (!isEof() && buf[buf_pos] <= 32U)
            buf_pos++;
    }
     
    inline int readChar() {
        int c = getChar();
        while (c != -1 && c <= 32)
            c = getChar();
        return c;
    }
     
    inline int readUInt() {
        int c = readChar(), x = 0;
        while ('0' <= c && c <= '9')
            x = x * 10 + c - '0', c = getChar();
        return x;
    }
     
    template <class T>
    inline T readInt() {
        int s = 1, c = readChar();
        T x = 0;
        if (c == '-')
            s = -1, c = getChar();
        else if (c == '+')
            c = getChar();
        while ('0' <= c && c <= '9')
            x = x * 10 + c - '0', c = getChar();
        return s == 1 ? x : -x;
    }
     
    inline double readDouble() {
        int s = 1, c = readChar();
        double x = 0;
        if (c == '-')
            s = -1, c = getChar();
        while ('0' <= c && c <= '9')
            x = x * 10 + c - '0', c = getChar();
        if (c == '.') {
            c = getChar();
            double coef = 1;
            while ('0' <= c && c <= '9')
                x += (c - '0') * (coef *= 1e-1), c = getChar();
        }
        return s == 1 ? x : -x;
    }
     
    inline void readWord(char *s) { 
        int c = readChar();
        while (c > 32)
            *s++ = c, c = getChar();
        *s = 0;
    }
     
    inline bool readLine(char *s) { 
        int c = getChar();
        while (c != '\n' && c != -1)
            *s++ = c, c = getChar();
        *s = 0;
        return c != -1;
    }
     
    /** Write */
     
    static int write_buf_pos = 0;
    static char write_buf[buf_size];
     
    inline void writeChar(int x) {
        if (write_buf_pos == buf_size)
            fwrite(write_buf, 1, buf_size, stdout), write_buf_pos = 0;
        write_buf[write_buf_pos++] = x;
    }
     
    inline void flush() {
        if (write_buf_pos) {
            fwrite(write_buf, 1, write_buf_pos, stdout), write_buf_pos = 0;
            fflush(stdout);
        }
    }
     
    template <class T> 
    inline void writeInt(T x, char end, int output_len) {
        if (x < 0)
            writeChar('-'), x = -x;
     
        char s[24];
        int n = 0;
        while (x || !n)
            s[n++] = '0' + x % 10, x /= 10;
        while (n < output_len)
            s[n++] = '0';
        while (n--)
            writeChar(s[n]);
        if (end)
            writeChar(end);
    }
     
    inline void writeWord(const char *s) {
        while (*s)
            writeChar(*s++);
    }
     
    inline void writeDouble(double x, int output_len) {
        if (x < 0)
            writeChar('-'), x = -x;
        int t = (int)x;
        writeInt(t), x -= t;
        writeChar('.');
        for (int i = output_len - 1; i > 0; i--) {
            x *= 10;
            t = std::min(9, (int)x);
            writeChar('0' + t), x -= t;
        }
        x *= 10;
        t = std::min(9, (int)(x + 0.5));
        writeChar('0' + t);
    }
}

using namespace fast;

struct Point{
    int x, y;
};

const int N = 510;
int n, m;
Point a[N];
Point p[N];
int cnt[N];

void read() {
    n = readInt();
    m = readInt();
    for (int i = 0; i < n; ++i) {
        a[i].x = readInt();
        a[i].y = readInt();
    }
    for (int i = 0; i < m; ++i) {
        p[i].x = readInt();
        p[i].y = readInt();
        cnt[i] = readInt();
    }
}

struct Edge{
    int to, cap, flow;
    Edge() {}
    Edge(int _to, int _cap) {
        to = _to, cap = _cap, flow = 0;
    }
    int getCap() {
        return cap - flow;
    }
};

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

namespace maxFlow{
    const int INF = 1e9 + 228;
    int n, s, t;
    Edge edges[2 * N * N];
    int topEdges;
    vector<int> g[2 * N];
    int q[2 * N];
    int topQ;
    int dist[2 * N];
    int ptr[2 * N];
    void init(int _n, int _s, int _t) {
        n = _n;
        s = _s;
        t = _t;
        for (int i = 0; i < n; ++i) {
            g[i].clear();
        }
        topEdges = 0;
    }
    void addEdge(int u, int v, int cap) {
        g[u].push_back(topEdges);
        edges[topEdges++] = {v, cap};
        g[v].push_back(topEdges);
        edges[topEdges++] = {u, 0};
    }
    bool bfs() {
        fill(dist, dist + n, -1);
        topQ = 0;
        q[topQ++] = s;
        dist[s] = 0;
        for (int i = 0; i < topQ; ++i) {
            int v = q[i];
            for (auto ind : g[v]) {
                if (edges[ind].getCap() < 1) continue;
                int to = edges[ind].to;
                if (dist[to] != -1) continue;
                dist[to] = dist[v] + 1;
                q[topQ++] = to;
            }
        }
        return dist[t] != -1;
    }
    int dfs(int v, int flow) {
        if (flow == 0) return 0;
        if (v == t) return flow;
        for (; ptr[v] < g[v].size(); ++ptr[v]) {
            int ind = g[v][ptr[v]];
            if (edges[ind].getCap() < 1) continue;
            int to = edges[ind].to;
            if (dist[to] != dist[v] + 1) continue;
            int ans = dfs(to, min(flow, edges[ind].getCap()));
            if (ans) {
                edges[ind].flow += ans;
                edges[ind ^ 1].flow -= ans;
                return ans;    
            }
        }
        return 0;
    }
    int getMaxFlow() {
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            shuffle(all(g[i]), rnd);
        }
        while (bfs()) {
            fill(ptr, ptr + n, 0);
            int x;
            do {
                x = dfs(s, INF);
                ans += x;
            } while (x > 0);
        }
        return ans;
    }
};

ll sq(ll x) {
    return x * x;
}

ld getDist(int i, int j) {
    return sqrt(sq(a[i].x - p[j].x) + sq(a[i].y - p[j].y));
}

const ld EPS = 1e-9;
ld dist[N][N];

void build() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            dist[i][j] = getDist(i, j);
        }
    }
    for (int i = 0; i < n; ++i) {
        maxFlow::g[i].reserve(1 + m);
    }
    for (int i = 0; i < m; ++i) {
        maxFlow::g[i + n].reserve(1 + n);
    }
    maxFlow::g[n + m].reserve(n);
    maxFlow::g[n + m + 1].reserve(m);
}

bool check(ld len) {
    maxFlow::init(n + m + 2, n + m, n + m + 1);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (dist[i][j] - EPS <= len) {
                maxFlow::addEdge(i, n + j, 1);
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        maxFlow::addEdge(maxFlow::s, i, 1);
    }
    for (int i = 0; i < m; ++i) {
        maxFlow::addEdge(n + i, maxFlow::t, cnt[i]);
    }
    int fans = maxFlow::getMaxFlow();
    return fans == n;
}

ld ans;

void run() {
    build();
    ld l = 0, r = 1e6 * sqrt(2) + 228;
    for (int it = 0; it < 42; ++it) {
        ld mid = (l + r) / 2;
        if (check(mid)) {
            r = mid;
        } else {
            l = mid;
        }
    }
    ans = r;
}

void write() {
    writeDouble(ans, 10);
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
    read();
    run();
    write();
    return 0;
}