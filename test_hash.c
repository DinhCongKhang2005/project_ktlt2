#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

// Kiem thu ham bam
void test_hash() {
    printf("=== KIEM THU HAM BAM ===\n");
    char *test1 = "hello";
    char *test2 = "world";
    char *test3 = "hash";
    printf("Chuoi: %s, Gia tri bam: %u\n", test1, BamChuoi(test1));
    printf("Chuoi: %s, Gia tri bam: %u\n", test2, BamChuoi(test2));
    printf("Chuoi: %s, Gia tri bam: %u\n", test3, BamChuoi(test3));
    // Kiem thu hai chuoi giong nhau
    if (BamChuoi("abc") == BamChuoi("abc"))
        printf("Bam hai chuoi giong nhau: PASSED\n");
    else
        printf("Bam hai chuoi giong nhau: FAILED\n");
    // Kiem thu hai chuoi khac nhau
    if (BamChuoi("abc") != BamChuoi("abd"))
        printf("Bam hai chuoi khac nhau: PASSED\n");
    else
        printf("Bam hai chuoi khac nhau: FAILED\n");
}

// Kiem thu ham so sanh chuoi
void test_compareString() {
    printf("=== KIEM THU SO SANH CHUOI ===\n");
    char *a = "abc";
    char *b = "abc";
    char *c = "abd";
    char *d = "aaa";
    printf("So sanh '%s' va '%s': %d\n", a, b, SoSanhChuoi(a, b));
    printf("So sanh '%s' va '%s': %d\n", a, c, SoSanhChuoi(a, c));
    printf("So sanh '%s' va '%s': %d\n", a, d, SoSanhChuoi(a, d));
    if (SoSanhChuoi(a, b) == 0)
        printf("So sanh hai chuoi giong nhau: PASSED\n");
    else
        printf("So sanh hai chuoi giong nhau: FAILED\n");
    if (SoSanhChuoi(a, c) < 0)
        printf("So sanh abc < abd: PASSED\n");
    else
        printf("So sanh abc < abd: FAILED\n");
    if (SoSanhChuoi(a, d) > 0)
        printf("So sanh abc > aaa: PASSED\n");
    else
        printf("So sanh abc > aaa: FAILED\n");
}

int main() {
    test_hash();
    test_compareString();
    system("PAUSE");
    return 0;
}