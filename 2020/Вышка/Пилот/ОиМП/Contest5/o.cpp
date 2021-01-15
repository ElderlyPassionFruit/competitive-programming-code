#include <map>
#include <unordered_map>
#include <set>
#include <tuple>
#include <utility>
#include <vector>

struct BoxW{
    int w, ind;
};

bool operator<(const BoxW& a, const BoxW& b) {
    return std::tie(a.w, b.ind) < std::tie(b.w, a.ind);
}

struct BoxV{
    int v, ind;
};

bool operator<(const BoxV& a, const BoxV& b) {
    return std::tie(a.v, b.ind) < std::tie(b.v, a.ind);
}

class Stock{
private:
    int ind;
    std::set<BoxW> myW;
    std::set<BoxV> myV;
    std::unordered_map<int, std::pair<int, int>> boxes;

public:
    Stock() {
        ind = 0;
        myW = {};
        myV = {};
        boxes = {};
    }
    void add(int w, int v);   // — добавить коробку на склад
    int get_by_w(int min_w);  // — вернуть номер коробки грузоподъемности хотя бы min_w
    int get_by_v(int min_v);  // — вернуть номер коробки объема хотя бы min_v.
};

void Stock::add(int w, int v) {
    int myInd = ind++;
    myW.insert({w, myInd});
    myV.insert({v, myInd});
    boxes[myInd] = {w, v};
}

int Stock::get_by_w(int min_w) {
    auto it = myW.lower_bound({min_w, ind});
    if (it == myW.end()) {
        return -1;
    }
    int ans = it->ind;
    auto box = boxes.find(ans);
    myW.erase(it);
    myV.erase({box->second.second, ans});
    boxes.erase(box);
    return ans;
}

int Stock::get_by_v(int min_v) {
    auto it = myV.lower_bound({min_v, ind});
    if (it == myV.end()) {
        return -1;
    }
    int ans = it->ind;
    auto box = boxes.find(ans);
    myV.erase(it);
    myW.erase({box->second.first, ans});
    boxes.erase(box);
    return ans;
}
