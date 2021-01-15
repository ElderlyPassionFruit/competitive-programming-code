#include <unordered_map>

class Counter {
private:
    std::unordered_map<int, int> data;

public:
    void increaseNumberOf(int id) {
        data[id]++;
    }

    void decreaseNumberOf(int id) {
        if (data[id] <= 0) {
            return;
        }
        data[id]--;
    }

    size_t getNumberOf(int id) const {
        auto it = data.find(id);
        if (it == data.end()) {
            return 0;
        }
        return it->second;
    }
};
