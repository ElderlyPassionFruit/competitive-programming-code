#include <set>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <climits>

struct BoxCompare {
    bool operator()(const std::pair<int, int> a, const std::pair<int, int> b) const {
        return std::tie(a.first, b.second) < std::tie(b.first, a.second);
    }
};

class Stock {
 public:
    void add(int w, int v) {
        ++_lastId;
        _boxesByVolume.emplace(v, _lastId);
        _boxesByWeight.emplace(w, _lastId);
        _boxes[_lastId] = {w, v};
    }

    int get_by_w(int min_w) {
        auto iterWeight = _boxesByWeight.lower_bound({min_w, INT_MAX});
        if (iterWeight == _boxesByWeight.end()) {
            return -1;
        }
        int ans = iterWeight->second;
        auto box = _boxes.find(ans);
        _boxesByWeight.erase(iterWeight);
        _boxesByVolume.erase({box->second.volume, ans});
        _boxes.erase(box);
        return ans;
    }

    int get_by_v(int min_v) {
        auto iterVolume = _boxesByVolume.lower_bound({min_v, INT_MAX});
        if (iterVolume == _boxesByVolume.end()) {
            return -1;
        }
        int ans = iterVolume->second;
        auto box = _boxes.find(ans);
        _boxesByWeight.erase({box->second.weight, ans});
        _boxesByVolume.erase(iterVolume);
        _boxes.erase(box);
        return ans;
    }

 private:
    struct Box {
        int weight;
        int volume;
    };
    int _lastId = -1;
    std::multiset<std::pair<int, int>, BoxCompare> _boxesByWeight;
    std::multiset<std::pair<int, int>, BoxCompare> _boxesByVolume;
    std::unordered_map<int, Box> _boxes;
};


#include <bits/stdc++.h>
using namespace std;

int main() {
    Stock a;
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int t;
        cin >> t;
        if (t == 1) {
            int w, v;
            cin >> w >> v;
            a.add(w, v);
        } else if (t == 2) {
            int w;
            cin >> w;
            cout << a.get_by_w(w) << endl;
        } else if (t == 3) {
            int v;
            cin >> v;
            cout << a.get_by_v(v) << endl;
        }
    }
}