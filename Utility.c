#include "Utility.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

void ChuyenChuThuong(char *chuoi) {
    for (; *chuoi; ++chuoi) *chuoi = tolower(*chuoi);
}

void ChuanHoaChuoi(char *chuoi) {
    char *start = chuoi;
    while (isspace((unsigned char)*start)) start++;
    if (start != chuoi) memmove(chuoi, start, strlen(start) + 1);

    char *end = chuoi + strlen(chuoi) - 1;
    while (end >= chuoi && isspace((unsigned char)*end)) end--;
    *(end + 1) = '\0';
}

bool KiemTraSoNguyenDuong(const char *chuoi) {
    if (!chuoi || !*chuoi) return false;
    for (const char *p = chuoi; *p; ++p)
        if (!isdigit(*p)) return false;
    return true;
}

int SoSanhChuoi(const void *a, const void *b) {
    if (!a || !b) return 0;
    return strcmp((const char *)a, (const char *)b);
}

void DocDong(char *buff, int buffSize) {
    if (fgets(buff, buffSize, stdin)) {
        buff[strcspn(buff, "\n")] = '\0';
    }
}