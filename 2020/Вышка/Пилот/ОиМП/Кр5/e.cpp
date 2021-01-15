#include <string>

std::string DetectType(const unsigned char* data, size_t size) {
    if (size >= 4 && data[0] == 0x25 && data[1] == 0x50 && data[2] == 0x44 && data[3] == 0x46) {
        return "pdf";
    }
    if (size >= 3 && data[0] == 0xFF && data[1] == 0xD8 && data[2] == 0xFF) {
        return "jpg";
    }
    if (size >= 2 && data[0] == 0x50 && data[1] == 0x4B) {
        return "zip";
    }
    return "other";
}

int main() {

}