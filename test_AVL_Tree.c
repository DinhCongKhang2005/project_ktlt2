#include <stdio.h>
#include <stdlib.h>
#include "AVL_Tree.h"

// Hàm so sánh cho số nguyên
int SoSanhSoNguyen(void *a, void *b) {
    return (*(int*)a) - (*(int*)b);
}

// Hàm duyệt giữa để in các giá trị trong cây AVL
void DuyetGiua(AVLNode* goc) {
    if (goc == NULL) return;
    DuyetGiua(goc->Trai);
    printf("%d ", *(int*)goc->DuLieu);
    DuyetGiua(goc->Phai);
}

// Kiểm thử thêm phần tử vào cây
void KiemThuChen() {
    printf("=== KIEM THU CHEN ===\n");
    AVLNode* goc = NULL;
    int a = 10, b = 20, c = 5;
    goc = ChenVaoCayAvl(goc, &a, &a, SoSanhSoNguyen);
    goc = ChenVaoCayAvl(goc, &b, &b, SoSanhSoNguyen);
    goc = ChenVaoCayAvl(goc, &c, &c, SoSanhSoNguyen);

    printf("Cay AVL sau khi chen 10, 20, 5 (duyet giua): ");
    DuyetGiua(goc);
    printf("\n");
}

// Kiểm thử tìm kiếm phần tử trong cây
void KiemThuTimKiem() {
    printf("=== KIEM THU TIM KIEM ===\n");
    AVLNode* goc = NULL;
    int v[3] = {10, 20, 5};
    for (int i = 0; i < 3; ++i)
        goc = ChenVaoCayAvl(goc, &v[i], &v[i], SoSanhSoNguyen);

    printf("Cay AVL hien tai (duyet giua): ");
    DuyetGiua(goc);
    printf("\n");

    int giaTriTim = 20;
    AVLNode* timThay = TimKiemCayAvl(goc, &giaTriTim, SoSanhSoNguyen);
    if (timThay)
        printf("Tim thay nut co gia tri %d\n", *(int*)timThay->DuLieu);
    else
        printf("Khong tim thay nut co gia tri %d\n", giaTriTim);

    giaTriTim = 99;
    timThay = TimKiemCayAvl(goc, &giaTriTim, SoSanhSoNguyen);
    if (timThay)
        printf("Tim thay nut co gia tri %d\n", *(int*)timThay->DuLieu);
    else
        printf("Khong tim thay nut co gia tri %d\n", giaTriTim);
}

// Kiểm thử xóa phần tử trong cây
void KiemThuXoa() {
    printf("=== KIEM THU XOA ===\n");
    AVLNode* goc = NULL;
    int v[5] = {10, 20, 5, 15, 25};
    for (int i = 0; i < 5; ++i)
        goc = ChenVaoCayAvl(goc, &v[i], &v[i], SoSanhSoNguyen);

    printf("Cay AVL truoc khi xoa (duyet giua): ");
    DuyetGiua(goc);
    printf("\n");

    int xoa = 20;
    goc = XoaKhoiCayAvl(goc, &xoa, SoSanhSoNguyen);
    printf("Cay AVL sau khi xoa 20 (duyet giua): ");
    DuyetGiua(goc);
    printf("\n");

    xoa = 99;
    goc = XoaKhoiCayAvl(goc, &xoa, SoSanhSoNguyen);
    printf("Cay AVL sau khi xoa 99 (khong ton tai) (duyet giua): ");
    DuyetGiua(goc);
    printf("\n");
}

int main() {
    KiemThuChen();
    KiemThuTimKiem();
    KiemThuXoa();
    system("PAUSE");
    return 0;
}