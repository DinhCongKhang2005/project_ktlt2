#include "Borrowing.h"
#include "Book.h"
#include "Member.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include "Data.h"
#include "AVL_Tree.h"

// Hàm hỗ trợ tạo struct tm
struct tm tao_ngay(int d, int m, int y) {
    struct tm date = {0};
    date.tm_mday = d;
    date.tm_mon = m;
    date.tm_year = y;
    return date;
}

// Test sinh mã tự động
void test_SinhMaPhieuMuon() {
    printf("Test: Sinh ma phieu muon tu dong\n");
    char ma[7] = "";
    SinhMaPhieuMuon(ma);
    printf("Ma moi duoc sinh ra: %s\n", ma);
    assert(strlen(ma) == 6);
}

// Test tạo node phiếu mượn
void test_TaoPhieuMuonMoi() {
    printf("Test: Tao node phieu muon\n");
    printf("Dau vao: ID = \"20237300\", Title = \"Lap trinh C co ban\", Author = \"Nguyen Van A\", Ngay = 1/1/2024\n");
    struct tm date = tao_ngay(1, 0, 124); // Tháng 0 là tháng 1 (theo struct tm)
    PhieuMuon *node = TaoPhieuMuonMoi("20237300", "Lap trinh C co ban", "Nguyen Van A", date);
    printf("Node duoc tao: ID = %s, Title = %s, Author = %s, Code = %s, Ngay muon: %d/%d/%d\n",
        node->MaThanhVien, node->TieuDe, node->TacGia, node->MaPhieu,
        node->ThoiGianMuon.tm_mday, node->ThoiGianMuon.tm_mon + 1, node->ThoiGianMuon.tm_year + 1900);
    assert(strcmp(node->MaThanhVien, "20237300") == 0);
    assert(strcmp(node->TieuDe, "Lap trinh C co ban") == 0);
    assert(strcmp(node->TacGia, "Nguyen Van A") == 0);
    assert(strlen(node->MaPhieu) == 6);
    free(node);
}

// Test thêm phiếu mượn vào bảng băm
void test_ThemPhieuMuon() {
    printf("Test: Them phieu muon vao bang bam\n");
    struct tm date = tao_ngay(2, 1, 124); // 2/2/2024
    PhieuMuon *node = TaoPhieuMuonMoi("20237301", "Cau truc du lieu va giai thuat", "Tran Thi B", date);
    ThemPhieuMuon(node);
    AVLNode *found = TimPhieuMuon(node->MaPhieu);
    printf("Them xong, kiem tra tim kiem theo ma: %s\n", found ? "Tim thay" : "Khong thay");
    assert(found != NULL);
}

// Test tạo phiếu mượn và cập nhật số lượng sách, bạn đọc
void test_TaoPhieuMuon() {
    printf("Test: Tao phieu muon va cap nhat so luong sach, so luong muon cua ban doc\n");
    ThanhVien mem;
    strcpy(mem.MaThanhVien, "20237300");
    mem.SoLuongDangMuon = 0;
    ThemThanhVien(&mem);

    Sach book;
    strcpy(book.TieuDe, "Lap trinh C co ban");
    strcpy(book.TacGia, "Nguyen Van A");
    book.SoLuong = 2;
    book.HangDoiUuTien = NULL;
    book.HangDoiBinhThuong = NULL;
    ChenSach(book);

    struct tm date = tao_ngay(1, 0, 124);
    TaoPhieuMuon("20237300", "Lap trinh C co ban", "Nguyen Van A", date);

    Sach *b = TimSach("Lap trinh C co ban", "Nguyen Van A");
    ThanhVien *m = TimThanhVien("20237300");
    printf("So luong sach con lai: %d, So luong dang muon cua ban doc: %d\n", b->SoLuong, m->SoLuongDangMuon);
    assert(b->SoLuong == 1);
    assert(m->SoLuongDangMuon == 1);
}

// Test kiểm tra quá hạn
void test_KiemTraQuaHan() {
    printf("Test: Kiem tra phieu muon co qua han khong\n");
    struct tm date = tao_ngay(1, 0, 120); // Nam 2020, da qua han
    PhieuMuon *node = TaoPhieuMuonMoi("20237302", "Toan roi rac", "Le Thi C", date);
    ThemPhieuMuon(node);
    AVLNode *found = TimPhieuMuon(node->MaPhieu);
    printf("Kiem tra qua han voi ngay muon cach day nhieu nam\n");
    int overdue = KiemTraQuaHan(found);
    printf("Ket qua: %s\n", overdue ? "QUA HAN" : "KHONG QUA HAN");
    assert(overdue == 1);
}

// Test xóa phiếu mượn và cập nhật số lượng sách, bạn đọc
void test_XoaPhieuMuon() {
    printf("Test: Xoa phieu muon va cap nhat so luong sach, ban doc\n");
    // Tạo phiếu mượn mới
    struct tm date = tao_ngay(5, 5, 124);
    PhieuMuon *node = TaoPhieuMuonMoi("20237303", "Giai tich 1", "Pham Van D", date);
    ThemPhieuMuon(node);

    Sach *b = TimSach("Giai tich 1", "Pham Van D");
    if (!b) {
        Sach book;
        strcpy(book.TieuDe, "Giai tich 1");
        strcpy(book.TacGia, "Pham Van D");
        book.SoLuong = 1;
        book.HangDoiUuTien = NULL;
        book.HangDoiBinhThuong = NULL;
        ChenSach(book);
        b = TimSach("Giai tich 1", "Pham Van D");
    }
    ThanhVien *m = TimThanhVien("20237303");
    if (!m) {
        ThanhVien mem;
        strcpy(mem.MaThanhVien, "20237303");
        mem.SoLuongDangMuon = 1;
        ThemThanhVien(&mem);
    }

    printf("Xoa phieu muon co ma: %s\n", node->MaPhieu);
    XoaPhieuMuon(node->MaPhieu);
    AVLNode *found = TimPhieuMuon(node->MaPhieu);
    printf("Sau khi xoa, kiem tra lai: %s\n", found ? "Con ton tai" : "Da bi xoa");
    assert(found == NULL);
}

// Test đọc và ghi file borrowing.csv
void test_DocGhiPhieuMuonFile() {
    printf("Test: Ghi file borrowing.csv va doc lai\n");
    LuuPhieuMuonVaoFile("borrowing.csv");
    printf("Doc file borrowing.csv\n");
    DocPhieuMuonTuFile("borrowing.csv");
    // Có thể kiểm tra lại bảng băm bằng TimPhieuMuon với một mã cụ thể
}

int main() {
    printf("===== BAT DAU CHAY CAC TEST CHO Borrowing.c =====\n\n");
    test_SinhMaPhieuMuon();
    printf("\n");
    test_TaoPhieuMuonMoi();
    printf("\n");
    test_ThemPhieuMuon();
    printf("\n");
    test_TaoPhieuMuon();
    printf("\n");
    test_KiemTraQuaHan();
    printf("\n");
    test_XoaPhieuMuon();
    printf("\n");
    test_DocGhiPhieuMuonFile();
    printf("\n===== TAT CA CAC TEST DA CHAY XONG! =====\n");
    system("PAUSE");
    return 0;
}