#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <math.h>
#include <iomanip>
#include <fstream>
#include <set>
#include <map>
#define ll long long
#define ld long double

using namespace std;

vector<int> all;
vector<char> let;
string s;
string t;
vector<string> answer;

struct node {
    int go[26];
    bool term = 0;
    string word;
    node() {
        for (int i = 0; i < 26; ++i)
            go[i] = -1;
    }
};

const int MAXN = 3e6;

node pool[MAXN];
int pt = 1;

void add(string& s) {
    int root = 0;
    for (int i = 0; i < s.size(); ++i) {
        int c = s[i] - 'A';
        if (pool[root].go[c] == -1) {
            pool[root].go[c] = pt;
            pt++;
        }
        root = pool[root].go[c];
    }
    pool[root].term = 1;
    pool[root].word = s;
}

void go_trie(int root, int pos, vector<char>& real, vector<bool> &used, vector<int>& dig) {
    cerr << root << "\n";
    if (pos == dig.size() && pool[root].term) {
        answer.push_back(pool[root].word);
        return;
    }
    if (pos == dig.size()) {
        return;
    }
    int c = dig[pos];
    for (auto elem : real)
        cerr << elem;
    cerr << "\n";
    if (real[c] != '#') {
        //cerr << real[c] << "\n";
        //cerr << c << "@@" << real[c] << "\n";
        int nex = pool[root].go[real[c] - 'A'];
        if (nex == -1)
            return;
        go_trie(nex, pos + 1, real, used, dig);
        return;
    }
    for (int i = 0; i < 26; ++i) {
        cerr << used[i] << "#" << pool[root].go[i] << " ";
        if (used[i] == 0 && pool[root].go[i] != -1) {
            cerr << "here\n";
            used[i] = 1;
            real[dig[pos]] = (char)('A' + i);
            go_trie(pool[root].go[i], pos + 1, real, used, dig);
            real[dig[pos]] = '#';
            used[i] = 0;
        }
        cerr << "/";
    }
    cerr << "\n";
}

void check(vector<int> &now) {
    //for (auto elem : now)
    //    cerr << elem << " ";
    //cerr << "\n";
    int a = 0;
    for (int i = 0; i < s.size(); ++i){
        for (int j = 0; j < now.size(); ++j) {
            if (s[i] == let[j]) {
                //cerr << "here\n";
                if (i == 0 && now[j] == 0)
                    return;
                a = a * 10 + now[j];
                break;
            }
        }
    }
    int b = 0;
    for (int i = 0; i < t.size(); ++i) {
        for (int j = 0; j < now.size(); ++j) {
            if (t[i] == let[j]) {
                if (i == 0 && now[j] == 0)
                    return;
                b = b * 10 + now[j];
                break;
            }
        }
    }
    //cerr << a << " " << b << "\n";
    int c = a + b;
    //cerr << c << "\n";
    vector<char> real(10);
    vector<bool> used(26);
    for (int i = 0; i < 10; ++i) {
        real[i] = '#';
    }
    for (int i = 0; i < now.size(); ++i) {
        real[now[i]] = let[i];
        used[let[i] - 'A'] = 1;
    }
    vector<int> dig;
    //cerr << c << "\n";
    while (c > 0) {
        dig.push_back(c % 10);
        c /= 10;
    }
    reverse(dig.begin(), dig.end());
    

    //IMPORTANT
    for (auto elem : dig)
        cerr << elem << "/";
    cerr << "\n";
    go_trie(0, 0, real, used, dig);
}

void gen(int need, vector<int> &now, vector<bool> &used) {
    if (now.size() == need) {
        check(now);
        return;
    }
    for (int i = 0; i < 10; ++i) {
        if (!used[i]) {
            used[i] = 1;
            now.push_back(i);
            gen(need, now, used);
            used[i] = 0;
            now.pop_back();
        }
    }
}

int main() {
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> s;
    cin >> t;
    set<char> let2;
    for (auto elem : s)
        let2.insert(elem);
    for (auto elem : t)
        let2.insert(elem);
    for (auto elem : let2) {
        let.push_back(elem);
    }
    int m = let.size();
    //for (auto elem : let)
    //    cerr << elem << "/";
    //cerr << "\n";
    int N;
    cin >> N;
    for (int i = 0; i < N; ++i) {
        string word;
        cin >> word;
        add(word);
    }
    for (int i = 0; i < pt; ++i) {
        cerr << i << ": ";
        for (int j = 0; j < 3; ++j) {
            cerr << pool[i].go[j] << "/";
        }
        cerr << "\n";
    }
    vector<int> arr;
    vector<bool> used(10);
    gen(m, arr, used);
    sort(answer.begin(), answer.end());
    cout << answer.size() << "\n";
    for (auto elem : answer) {
        cout << elem << "\n";
    }
}
//*/