//#pragma GCC optimize("-Os")
#include <algorithm>
#include <cstddef>
#include <utility>

template<typename T>
struct Node {
    T* value;
    Node<T>* left;
    Node<T>* right;
    Node()
        : value(nullptr)
        , left(nullptr)
        , right(nullptr) {
    }

    Node(T* _value, Node<T>* _left, Node<T>* _right)
        : value(_value)
        , left(_left)
        , right(_right) {
    }

    bool operator==(const Node& other) {
        return value == other.value && left == other.left && right == other.right;
    }
};

template<typename T>
class Iterator{
private:
    Node<T>* data;

public:
    Iterator(Node<T>* _data)
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

    T& operator*() {
        return *(data->value);
    }

    const T& operator*() const {
        return *(data->value);
    }

    bool operator==(const Iterator& other) {
        return data == other.data;
    }

    bool operator!=(const Iterator& other) {
        return !((*this) == other);
    }
};

template<typename T>
class List{
private:
    size_t sz = 0;
    Node<T>* beforeBegin = nullptr;
    Node<T>* afterEnd = nullptr;

public:
    List()
        : sz(0)
        , beforeBegin(new Node<T>())
        , afterEnd(new Node<T>()) {
        beforeBegin->right = afterEnd;
        afterEnd->left = beforeBegin;
    }

    List(const List& other)
        : sz(0)
        , beforeBegin(new Node<T>())
        , afterEnd(new Node<T>()) {
        beforeBegin->right = afterEnd;
        afterEnd->left = beforeBegin;
        for (auto it = other.begin(); it != other.end(); ++it) {
            this->push_back(*it);
        }
    }

    List& operator=(const List& other) {
        size_t minSize = std::min(this->size(), other.size());
        auto myIt = this->begin();
        auto otherIt = other.begin();
        for (size_t i = 0; i < minSize; ++i) {
            *myIt = *otherIt;
            ++myIt;
            ++otherIt;
        }

        while (this->size() > other.size()) {
            this->pop_back();
        }
        while (this->size() < other.size()) {
            this->push_back(*otherIt);
            ++otherIt;
        }
        return *this;
    }

    ~List() {
        Node<T>* now;
        while (beforeBegin != nullptr) {
            now = beforeBegin->right;
            delete beforeBegin->value;
            delete beforeBegin;
            beforeBegin = now;
        }
    }

    void push_back(const T& value) {
        Node<T>* newAfterEnd = new Node<T>(nullptr, afterEnd, nullptr);
        afterEnd->value = new T(value);
        afterEnd->right = newAfterEnd;
        afterEnd = newAfterEnd;
        ++sz;
    }

    void push_back(T&& value) {
        Node<T>* newAfterEnd = new Node<T>(nullptr, afterEnd, nullptr);
        afterEnd->value = new T(std::move(value));
        afterEnd->right = newAfterEnd;
        afterEnd = newAfterEnd;
        ++sz;
    }

    void pop_back() {
        afterEnd = afterEnd->left;
        delete afterEnd->right;
        afterEnd->right = nullptr;
        delete afterEnd->value;
        afterEnd->value = nullptr;
        --sz;
    }

    void push_front(const T& value) {
        Node<T>* newBeforeBegin = new Node<T>(nullptr, nullptr, beforeBegin);
        beforeBegin->value = new T(value);
        beforeBegin->left = newBeforeBegin;
        beforeBegin = newBeforeBegin;
        ++sz;
    }

    void push_front(T&& value) {
        Node<T>* newBeforeBegin = new Node<T>(nullptr, nullptr, beforeBegin);
        beforeBegin->value = new T(std::move(value));
        beforeBegin->left = newBeforeBegin;
        beforeBegin = newBeforeBegin;
        ++sz;
    }

    void pop_front() {
        beforeBegin = beforeBegin->right;
        delete beforeBegin->left;
        beforeBegin->left = nullptr;
        delete beforeBegin->value;
        beforeBegin->value = nullptr;
        --sz;
    }

    size_t size() const {
        return sz;
    }

    Iterator<T> begin() const {
        Iterator<T> ans(beforeBegin);
        ++ans;
        return ans;
    }

    Iterator<T> end() const {
        Iterator<T> ans(afterEnd);
        return ans;
    }
};


#include <bits/stdc++.h>

using namespace std;

mt19937 rnd(time(0));

string gen() {
    string a = "";
    int n = rnd() % 3 + 1;
    for (int i = 0; i < n; ++i) {
        a += 'a' + rnd() % 26;
    }
    return a;
}

template<typename T>
void check(const List<T>& a, const list<T>& b) {
    assert(a.size() == b.size());
    auto itA = a.begin();
    auto itB = b.begin();
    for (int i = 0; i < a.size(); ++i) {
        assert((*itA) == (*itB));
        ++itA;
        ++itB;
    }
}

template<typename T>
void write(const List<T>& a) {
    for (auto it = a.begin(); it != a.end(); ++it) {
        cout << "!" << *it << "!";
    }
    cout << endl;
}

int main() {
    List<string> a;
    /*a.push_back("1");
    write(a);
    a.push_back("2");
    
    write(a);
    a.pop_back();
    write(a);
    exit(0);
    
    //auto x = a;
    List<string> x;
    x = a;
    return 0;*/
    //a = x;
    //return 0;
    //a.push_back("1");
    //auto b = a;
    //b.pop_front();
    list<string> b;
    //while (true) {
    for (int it = 0; it < 10000000; ++it) {
        int t = rnd() % 2;
        if (b.size() < 2) {
            t = rnd() % 2;
        }
        if (t == 0) {
            auto x = gen();
            a.push_back(x);
            b.push_back(x);
            cout << "push_back(x) = " << x << endl;
        } else if (t == 1) {
            auto x = gen();
            a.push_front(x);
            b.push_front(x);
            cout << "push_front(x) = " << x << endl;
        } else if (t == 2) {
            a.pop_back();
            b.pop_back();
            cout << "pop_back()" << endl;
        } else {
            a.pop_front();
            b.pop_front();
            cout << "pop_front()" << endl;
        }
        cout << "a.size() = " << a.size() << endl;
        //cerr << "it = " << it << endl;
        auto x = a;
        check(x, b);
        auto y = x;
        check(y, b);
        a = x;
        check(a, b);
    }
    return 0;
}