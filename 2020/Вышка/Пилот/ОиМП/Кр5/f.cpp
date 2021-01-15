#include <stdexcept>
#include <map>
#include <optional>
#include <utility>

template <typename Key1, typename Key2, typename Value>
class BiMap {
private:
    std::map<std::pair<std::optional<Key1>, std::optional<Key2>>, Value> data;
    std::map<Key1, std::pair<std::optional<Key1>, std::optional<Key2>>> first;
    std::map<Key2, std::pair<std::optional<Key1>, std::optional<Key2>>> second;

public:
    // Вставить значение, указав один или оба ключа.
    // Генерирует исключение std::invalid_argument("some text") в случае,
    // если оба ключа пусты, либо один из ключей уже имеется в хранилище.
    void Insert(
        const std::optional<Key1>& key1,
        const std::optional<Key2>& key2,
        const Value& value) {
        if ((!key1.has_value()) && (!key2.has_value())) {
            throw std::invalid_argument("some text");
        }
        if (key1.has_value() && first.find(key1.value()) != first.end()) {
            throw std::invalid_argument("some text");
        }
        if (key2.has_value() && second.find(key2.value()) != second.end()) {
            throw std::invalid_argument("some text");
        }
        if (key1.has_value()) {
            first[key1.value()] = std::make_pair(key1, key2);
        }
        if (key2.has_value()) {
            second[key2.value()] = std::make_pair(key1, key2);
        }
        data.insert(make_pair(make_pair(key1, key2), value));
    }

    // Получить значение по ключу первого типа.
    // Генерирует исключение std::out_of_range("some text")
    // в случае отсутствия ключа (как и функция at в std::map).
    Value& GetByPrimaryKey(const Key1& key) {
        auto it = first.find(key);
        if (it == first.end()) {
            throw std::out_of_range("some text");
        }
        auto it2 = data.find(it->second);
        return it2->second;
    }

    const Value& GetByPrimaryKey(const Key1& key) const {
        auto it = first.find(key);
        if (it == first.end()) {
            throw std::out_of_range("some text");
        }
        auto it2 = data.find(it->second);
        return it2->second;
    }

    // Аналогичная функция для ключа второго типа.
    Value& GetBySecondaryKey(const Key2& key) {
        auto it = second.find(key);
        if (it == second.end()) {
            throw std::out_of_range("some text");
        }
        auto it2 = data.find(it->second);
        return it2->second;
    }

    const Value& GetBySecondaryKey(const Key2& key) const {
        auto it = second.find(key);
        if (it == second.end()) {
            throw std::out_of_range("some text");
        }
        auto it2 = data.find(it->second);
        return it2->second;
    }
};


#include <iostream>
#include <string>

using namespace std;

struct Student {
    string Surname, Name;
};

ostream& operator << (ostream& out, const Student& s) {
    return out << s.Surname << " " << s.Name;
}

int main() {
    BiMap<int, string, Student> bimap;  // студента можно определить либо по номеру, либо по логину
    bimap.Insert(42, {}, {"Ivanov", "Ivan"});
    bimap.Insert({}, "cshse-ami-512", {"Petrov", "Petr"});
    bimap.Insert(13, "cshse-ami-999", {"Fedorov", "Fedor"});

    cout << bimap.GetByPrimaryKey(42) << "\n";  // Ivanov Ivan

    cout << bimap.GetBySecondaryKey("cshse-ami-512") << "\n";  // Petrov Petr

    cout << bimap.GetByPrimaryKey(13) << "\n";  // Fedorov Fedor
    cout << bimap.GetBySecondaryKey("cshse-ami-999") << "\n";  // Fedorov Fedor

    bimap.GetByPrimaryKey(13).Name = "Oleg";  // меняем значение по первичному ключу - по вторичному оно тоже должно измениться
    cout << bimap.GetByPrimaryKey(13) << "\n";  // Fedorov Oleg
    cout << bimap.GetBySecondaryKey("cshse-ami-999") << "\n";  // Fedorov Oleg
    return 0;
}