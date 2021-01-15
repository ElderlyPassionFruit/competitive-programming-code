#include <iostream>
#include <string>
#include <vector>

class Serializer{
public:
    virtual ~Serializer() {}
    virtual void BeginArray() = 0;
    virtual void AddArrayItem(const std::string &) = 0;
    virtual void EndArray() = 0;
};

class JsonSerializer: public Serializer{
private:
    std::vector<int> first;

public:
    JsonSerializer() {
        first = {};
    }
    void BeginArray() override {
        if (!first.empty() && first.back() > 0) {
            std::cout << ',';
        }
        if (!first.empty()) {
            first[first.size() - 1]++;
        }
        first.push_back(0);
        std::cout << '[';
    }
    void AddArrayItem(const std::string& a) override {
        if (!first.empty() && first.back() > 0) {
            std::cout << ',';
        }
        if (!first.empty()) {
            first[first.size() - 1]++;
        }
        std::cout << '\"' << a << '\"';
    }
    void EndArray() override {
        std::cout << ']';
        first.pop_back();
    }
};

int main () {
    Serializer* a = new JsonSerializer();
    a->BeginArray();
    a->BeginArray();
    a->AddArrayItem("a");
    a->EndArray();
    a->EndArray();
    return 0;
}