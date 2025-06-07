#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Member.h"
#include "AVL_Tree.h"
#include "hash.h"



// Hàm in thông tin một thành viên
void InThanhVien(ThanhVien *thanhVien) {
    if (thanhVien)
        printf("ID: %s, Ten: %s, Sach muon: %d\n", thanhVien->MaThanhVien, thanhVien->HoTen, thanhVien->SoLuongDangMuon);
    else
        printf("Thanh vien NULL\n");
}

// Hàm duyệt cây AVL theo thứ tự giữa để in thành viên
void DuyetGiuaThanhVien(AVLNode* goc) {
    if (goc == NULL) return;
    DuyetGiuaThanhVien(goc->Trai);
    InThanhVien((ThanhVien*)goc->DuLieu);
    DuyetGiuaThanhVien(goc->Phai);
}

// In toàn bộ bảng băm
void InTatCaThanhVien() {
    printf("=== Danh sach thanh vien hien tai ===\n");
    for (int i = 0; i < KichThuocBang; ++i) {
        if (BangBamThanhVien[i]) {
            printf("Bucket %d:\n", i);
            DuyetGiuaThanhVien(BangBamThanhVien[i]);
        }
    }
}

// Kiểm thử thêm thành viên
void test_ThemThanhVien() {
    printf("=== KIEM THU THEM THANH VIEN ===\n");
    ThanhVien *m1 = (ThanhVien*)malloc(sizeof(ThanhVien));
    strcpy(m1->MaThanhVien, "20237300");
    strcpy(m1->HoTen, "Nguyen Van An");
    m1->SoLuongDangMuon = 0;
    ThemThanhVien(m1);

    ThanhVien *m2 = (ThanhVien*)malloc(sizeof(ThanhVien));
    strcpy(m2->MaThanhVien, "20237301");
    strcpy(m2->HoTen, "Tran Thi Binh");
    m2->SoLuongDangMuon = 2;
    ThemThanhVien(m2);

    InTatCaThanhVien();
}

// Kiểm thử tìm kiếm thành viên
void test_TimThanhVien() {
    printf("=== KIEM THU TIM KIEM THANH VIEN ===\n");
    ThanhVien *ketQua = TimThanhVien("20237300");
    printf("Tim kiem ID 20237300:\n");
    InThanhVien(ketQua);

    ketQua = TimThanhVien("20237399");
    printf("Tim kiem ID 20237399:\n");
    InThanhVien(ketQua);
}

// Kiểm thử xóa thành viên không dùng scanf
void test_XoaThanhVien_auto(char *id) {
    printf("=== KIEM THU XOA THANH VIEN ID %s ===\n", id);
    unsigned int chiSo = BamChuoi(id);
    AVLNode *ketQua = TimKiemCayAvl(BangBamThanhVien[chiSo], id, SoSanhChuoi);
    if (ketQua != NULL) {
        ThanhVien *thanhVien = (ThanhVien *)ketQua->DuLieu;
        if (thanhVien->SoLuongDangMuon > 0) {
            printf("Khong the xoa thanh vien, vi con sach muon\n");
        } else {
            BangBamThanhVien[chiSo] = XoaKhoiCayAvl(BangBamThanhVien[chiSo], thanhVien->MaThanhVien, SoSanhChuoi);
            printf("Da xoa thanh vien\n");
        }
    } else {
        printf("Khong tim thay thanh vien\n");
    }
    InTatCaThanhVien();
}

int main() {
    for (int i = 0; i < KichThuocBang; ++i) BangBamThanhVien[i] = NULL;

    test_ThemThanhVien();
    test_TimThanhVien();
    test_XoaThanhVien_auto("20237301"); // Có sách mượn, không xóa được
    test_XoaThanhVien_auto("20237300"); // Xóa được
    test_XoaThanhVien_auto("20237399"); // Không tồn tại
    system("PAUSE");
    return 0;
}