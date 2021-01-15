#include <cstddef>

struct Node {
    int value;
    Node* left;
    Node* right;
    Node()
        : value(0)
        , left(nullptr)
        , right(nullptr) {
    }

    bool operator==(const Node& other) {
        return value == other.value && left == other.left && right == other.right;
    }
};

class Iterator{
private:
    Node* data;

public:
    Iterator(Node* _data)
        : data(_data) {
    }

    Iterator& operator++() {
        this->data = data->right;
        return *this;
    }

    Iterator& operator--() {
        this->data = data->left;
        return *this;
    }

    int& operator*() {
        return data->value;
    }

    const int& operator*() const {
        return data->value;
    }

    bool operator==(const Iterator& other) {
        return data == other.data;
    }

    bool operator!=(const Iterator& other) {
        return !((*this) == other);
    }
};

class List{
private:
    size_t sz = 0;
    Node* beforeBegin = nullptr;
    Node* afterEnd = nullptr;

public:
    void clear() {
        while (this->size() > 0) {
            this->pop_back();
        }
    }

    List()
        : sz(0)
        , beforeBegin(new Node())
        , afterEnd(new Node()) {
        beforeBegin->right = afterEnd;
        afterEnd->left = beforeBegin;
    }

    List(const List& other)
        : sz(0)
        , beforeBegin(new Node())
        , afterEnd(new Node()) {
        beforeBegin->right = afterEnd;
        afterEnd->left = beforeBegin;
        for (auto it = other.begin(); it != other.end(); ++it) {
            this->push_back(*it);
        }
    }

    List& operator=(const List& other) {
        clear();
        for (auto it = other.begin(); it != other.end(); ++it) {
            this->push_back(*it);
        }
        return *this;
    }

    ~List() {
        clear();
        delete beforeBegin;
        delete afterEnd;
    }

    void push_back(int value) {
        Node* newAfterEnd = new Node();
        afterEnd->value = value;
        afterEnd->right = newAfterEnd;
        newAfterEnd->left = afterEnd;
        afterEnd = newAfterEnd;
        ++sz;
    }

    void pop_back() {
        afterEnd = afterEnd->left;
        delete afterEnd->right;
        --sz;
    }

    void push_front(int value) {
        Node* newBeforeBegin = new Node();
        beforeBegin->value = value;
        beforeBegin->left = newBeforeBegin;
        newBeforeBegin->right = beforeBegin;
        beforeBegin = newBeforeBegin;
        ++sz;
    }

    void pop_front() {
        beforeBegin = beforeBegin->right;
        delete beforeBegin->left;
        --sz;
    }

    size_t size() const {
        return sz;
    }

    Iterator begin() const {
        Iterator ans(beforeBegin);
        ++ans;
        return ans;
    }

    Iterator end() const {
        Iterator ans(afterEnd);
        return ans;
    }
};
