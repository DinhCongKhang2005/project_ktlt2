#include "hash.h"
#include "AVL_Tree.h"
#include "Data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Hàm băm cho khoá
unsigned int BamChuoi(char *chuoi) {
    unsigned long long bam = 0;
    while (*chuoi) {
        bam = (bam << 5) + *chuoi++;
    }
    return bam % KichThuocBang;
}

// Hàm so sánh xâu
int SoSanhChuoi(void *a, void *b) {
    return strcmp((char *)a, (char *)b);
}

