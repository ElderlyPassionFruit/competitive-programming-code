#include <cstddef>  // for size_t

class RangeError {
};

size_t CountValues(const char * data, size_t size) {
    size_t answer = 0;
    for (size_t i = 0; i != size;) {
        ++answer;
        size_t block = 0;
        for (size_t j = 0; j < 8; ++j) {
            if (i == size) {
                throw RangeError();
            }
            block += data[i] * (1 << j);
            ++i;
        }
        for (size_t j = 0; j < block; ++j) {
            if (i == size) {
                throw RangeError();
            }
            ++i;
        }
    }
    return answer;
}

#include <bits/stdc++.h>
using namespace std;


char arr[] = {
    0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  0x68, 0x65, 0x6c, 0x6c, 0x6f, 0x06, 0x00, 0x00,  
    0x00, 0x00, 0x00, 0x00, 0x00, 0x77, 0x6f, 0x72,  0x6c, 0x64, 0x21
};

int main() {
    cout << CountValues(arr, 27) << endl;
}