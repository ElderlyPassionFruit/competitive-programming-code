#include <iostream>
#include <iterator>
#include <vector>

class Model {
public:
    std::vector<int> data;

    void save(std::ostream& out) const;
    void load(std::istream& in);
};

void Model::save(std::ostream& out) const {
    int n = data.size();
    out.write(reinterpret_cast<char*>(&n), sizeof n);
    for (auto i : data) {
        out.write(reinterpret_cast<char*>(&i), sizeof i);
    }
}

void Model::load(std::istream& in) {
    data.clear();
    int n;
    in.read(reinterpret_cast<char*>(&n), sizeof n);
    data.resize(n);
    for (auto& i : data) {
        in.read(reinterpret_cast<char*>(&i), sizeof i);
    }
}