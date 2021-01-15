#include <map>
#include <iostream>
#include <string>
#include <vector>

template <typename T>
void Serialize(T pod, std::ostream& out);

void Serialize(const std::string& str, std::ostream& out);

template <typename T>
void Serialize(const std::vector<T>& data, std::ostream& out);

template <typename T1, typename T2>
void Serialize(const std::map<T1, T2>& data, std::ostream& out);

template <typename T>
void Deserialize(std::istream& in, T& pod);

void Deserialize(std::istream& in, std::string& str);

template <typename T>
void Deserialize(std::istream& in, std::vector<T>& data);

template <typename T1, typename T2>
void Deserialize(std::istream& in, std::map<T1, T2>& data);


template <typename T>
void Serialize(T pod, std::ostream& out) {
    out.write(reinterpret_cast<char*>(&pod), sizeof pod);
}

void Serialize(const std::string& str, std::ostream& out) {
    size_t n = str.size();
    Serialize(n, out);
    for (auto i : str) {
        Serialize(i, out);
    }
}

template <typename T>
void Serialize(const std::vector<T>& data, std::ostream& out) {
    size_t n = data.size();
    Serialize(n, out);
    for (auto i : data) {
        Serialize(i, out);
    }
}

template <typename T1, typename T2>
void Serialize(const std::map<T1, T2>& data, std::ostream& out) {
    size_t n = data.size();
    Serialize(n, out);
    for (auto i : data) {
        Serialize(i.first, out);
        Serialize(i.second, out);
    }
}

template <typename T>
void Deserialize(std::istream& in, T& pod) {
    in.read(reinterpret_cast<char*>(&pod), sizeof pod);
}

void Deserialize(std::istream& in, std::string& str) {
    size_t n;
    Deserialize(in, n);
    str = "";
    for (size_t i = 0; i < n; ++i) {
        char x;
        Deserialize(in, x);
        str += x;
    }
}

template <typename T>
void Deserialize(std::istream& in, std::vector<T>& data) {
    size_t n;
    Deserialize(in, n);
    data.resize(n);
    for (auto& i : data) {
        Deserialize(in, i);
    }
}

template <typename T1, typename T2>
void Deserialize(std::istream& in, std::map<T1, T2>& data) {
    size_t n;
    Deserialize(in, n);
    for (size_t i = 0; i < n; ++i) {
        T1 x;
        T2 y;
        Deserialize(in, x);
        Deserialize(in, y);
        data[x] = y;
    }
}
