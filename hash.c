// Định nghĩa các hàm băm và so sánh chuỗi
#include "hash.h"
#include <string.h>

unsigned int Bamh(const char *str, int kichThuocBang) {
    unsigned int hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    return hash % kichThuocBang;
}

int SoSanhChuoi(const void *a, const void *b) {
    return strcmp((const char *)a, (const char *)b);
}