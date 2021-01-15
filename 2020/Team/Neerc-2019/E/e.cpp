#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cassert>

using namespace std;

string let = "abcdefgh";

vector<pair<int, int>> all;

void init() {
    int x = 0;
    int y = 0;
    for (int i = 0; i < 48; ++i) {
        all.push_back({ x, y });
        if (x % 2 == 0) {
            if (y < 7) {
                y++;
            } else {
                x++;
            }
            continue;
        }
        if (y > 0) {
            y--;
        } else {
            x++;
        }
    }
    for (int i = 48; i < 60; ++i) {
        all.push_back({ x, y });
        if (y % 2 == 0) {
            if (x < 7) {
                x++;
            }
            else {
                y++;
            }
            continue;
        }
        if (x > 6) {
            x--;
        }
        else {
            y++;
        }
    }
    //for (auto elem : all) {
    //    cout << elem.first << "/" << elem.second << "\n";
    //}

}

bool check(int n, vector<pair<int, int>> ans) {
    assert(ans.size() == n);
    assert(ans[0] == make_pair(0, 0));
    assert(ans.back() == make_pair(7, 7));
    vector<vector<bool>> used(8, vector<bool>(8, false));
    for (int i = 0; i < ans.size(); ++i) {
        assert(!used[ans[i].first][ans[i].second]);
        used[ans[i].first][ans[i].second] = true;
        if (i == 0) continue;
        bool A = ans[i].first == ans[i - 1].first;
        bool B = ans[i].second == ans[i - 1].second;
        assert(A ^ B);
    }
    return true;
}

void print(vector<pair<int, int>> &ans) {
    for (auto elem : ans) {
        cout << (char)('a' + elem.first) << elem.second + 1 << " ";
    }
    cout << "\n";
}

int main() {
    init();
    int n;
    cin >> n;
    n += 1;
    vector<pair<int, int>> path;
    int x = 0;
    int y = 0;
    
    if (n <= 62) {
        int left = n;
        int pt = 0;
        while (left > 2) {
            path.push_back(all[pt]);
            x = all[pt].first;
            y = all[pt].second;
            pt++;
            left--;
        }
        if (x == 6) {
            path.push_back({ 6, 7 });
        } else if (x == 7) {
            path.push_back({ 7, 6 });
        } else if (y == 7) {
            path.push_back({ 6, 7 });
        } else {
            path.push_back({ 7, y });
        }
        path.push_back({7, 7});
    } else {
        if (n == 63) {
            path = all;
            path.push_back({ 6, 6 });
            path.push_back({ 6, 7 });
            path.push_back({ 7, 7 });
        }
        if (n == 64) {
            path = all;
            path.push_back({ 6, 7 });
            path.push_back({ 6, 6 });
            path.push_back({ 7, 6 });
            path.push_back({ 7, 7 });
        }
    }
    print(path);
    assert(check(n, path));
}