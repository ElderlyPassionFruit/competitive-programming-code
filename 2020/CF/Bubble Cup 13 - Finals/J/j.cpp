#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

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

const int MOD = 1e9 + 7;
const int LOG = 61, BUBEN = 7;
int dp[LOG][BUBEN];

void clear() {
    for (int i = 0; i < LOG; ++i) {
        for (int j = 0; j < BUBEN; ++j) {
            dp[i][j] = 0;
        }
    } 
}

vector<int> g[BUBEN][2];

void initG() {
    for (int x = 0; x < 2; ++x) {
        for (int prev = 0; prev < BUBEN; ++prev) {
            for (int val = 0; val <= 7; ++val) {
                int nxtAdd = (-x + prev + val);
                if (nxtAdd < 0 || (nxtAdd & 1)) continue;
                nxtAdd /= 2;
                g[prev][x].push_back(nxtAdd);
            }
        }
    }
}

void solve() {
    clear();
    ll n;
    //cin >> n;
    n = readInt();
    dp[0][0] = 1;
    for (int bit = 0; bit < LOG; ++bit) {
        for (int prev = 0; prev < BUBEN; ++prev) {
            if (!dp[bit][prev]) continue;
            for (auto nxtAdd : g[prev][(n >> bit) & 1]) {
                dp[bit + 1][nxtAdd] += dp[bit][prev];
                if (dp[bit + 1][nxtAdd] >= MOD) {
                    dp[bit + 1][nxtAdd] -= MOD;
                }
            }
            /*int x = -((n >> bit) & 1);
            for (int val = 0; val <= 7; ++val) {
                int nxtAdd = x;
                nxtAdd += prev + val;
                if (nxtAdd < 0) continue;
                if (nxtAdd & 1) continue;
                nxtAdd /= 2;
                dp[bit + 1][nxtAdd] += dp[bit][prev];
                if (dp[bit + 1][nxtAdd] >= MOD) {
                    dp[bit + 1][nxtAdd] -= MOD;
                }
            }*/
        }
    }
    /*cout << "dp = " << endl;
    for (int i = 0; i < LOG; ++i) {
        for (int j = 0; j < BUBEN; ++j) {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }*/
    cout << dp[LOG - 1][0] << "\n";
    //writeInt(dp[LOG - 1][0]);
    //writeChar('\n');
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	initG();
    //cout.precision(20);
    int t;
    //cin >> t;
    t = readInt();
    while (t--) {
        solve();
    }
	return 0;
}