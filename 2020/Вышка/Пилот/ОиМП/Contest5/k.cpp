#include <iostream>
using namespace std;

class Writer {
public:
    virtual void Write(const char * data, size_t len) {
        // Какой-то вывод в файл, на экран или в память
        for (int i = 0; i < len; ++i) {
            cout << data[i];
        }
        cout << endl;
    }
};

class BufferedWriter: public Writer{
private:
    size_t buffSize;
    char* buff;
    size_t pos;

public:
    BufferedWriter(size_t _buffSize)
        : buffSize(_buffSize)
        , pos(0) {
        buff = new char[buffSize];
    }

    void Write(const char * data, size_t len) override {
        for (size_t i = 0; i < len; ++i) {
            if (pos == buffSize) {
                Writer::Write(buff, pos);
                pos = 0;
            }
            buff[pos++] = data[i];
        }
    }

    ~BufferedWriter() {
        Writer::Write(buff, pos);
        delete []buff;
    }
};

int main() {
    BufferedWriter a(5);
    char b[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    a.Write(b, 6);
    a.Write(b, 6);
    return 0;
}