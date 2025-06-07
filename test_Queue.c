#include "Queue.h"
#include "Book.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include "Data.h"

// Hàm hỗ trợ tạo struct tm
struct tm tao_ngay(int d, int m, int y) {
    struct tm date = {0};
    date.tm_mday = d;
    date.tm_mon = m;
    date.tm_year = y;
    return date;
}

// Test tạo node hàng đợi
void test_TaoNutHangDoi() {
    printf("Test: Tao node hang doi\n");
    printf("Dau vao: ID = \"20237300\", Title = \"Lap trinh C co ban\", Author = \"Nguyen Van A\", Ngay = 1/6/2024, UuTien = 1\n");
    struct tm date = tao_ngay(1, 5, 124); // 1/6/2024
    HangDoi *node = TaoNutHangDoi("20237300", "Lap trinh C co ban", "Nguyen Van A", 1);
    node->ThoiGianAnDinh = date;
    assert(strcmp(node->MaThanhVien, "20237300") == 0);
    assert(strcmp(node->TieuDe, "Lap trinh C co ban") == 0);
    assert(strcmp(node->TacGia, "Nguyen Van A") == 0);
    assert(node->UuTien == 1);
    assert(node->ThoiGianAnDinh.tm_mday == 1 && node->ThoiGianAnDinh.tm_mon == 5 && node->ThoiGianAnDinh.tm_year == 124);
    free(node);
}

// Test ChenNutHangDoi và LayNguoiDauTien
void test_ChenNutHangDoi_LayNguoiDauTien() {
    printf("Test: Them node vao hang doi va lay nguoi dau hang\n");
    printf("Tao sach: TieuDe = \"Lap trinh C co ban\", TacGia = \"Nguyen Van A\", SoLuong = 1\n");
    Sach sach;
    strcpy(sach.TieuDe, "Lap trinh C co ban");
    strcpy(sach.TacGia, "Nguyen Van A");
    sach.SoLuong = 1;
    sach.HangDoiUuTien = NULL; sach.HangDoiBinhThuong = NULL;
    ChenSach(sach);

    printf("Them node uu tien: ID = \"20237301\", UuTien = 1\n");
    struct tm date1 = tao_ngay(2, 5, 124);
    ChenNutHangDoi("20237301", "Lap trinh C co ban", "Nguyen Van A", 1);

    printf("Them node thuong: ID = \"20237302\", UuTien = 0\n");
    struct tm date2 = tao_ngay(3, 5, 124);
    ChenNutHangDoi("20237302", "Lap trinh C co ban", "Nguyen Van A", 0);

    Sach *b = TimSach("Lap trinh C co ban", "Nguyen Van A");
    HangDoi *front = LayNguoiDauTien(b);
    printf("Nguoi dau hang: ID = %s (20237301 la uu tien)\n", front ? front->MaThanhVien : "NULL");
    assert(front && strcmp(front->MaThanhVien, "20237301") == 0);
}

// Test XoaNguoiDauTien
void test_XoaNguoiDauTien() {
    printf("Test: Xoa nguoi dau hang doi (uu tien truoc)\n");
    Sach *b = TimSach("Lap trinh C co ban", "Nguyen Van A");
    printf("Xoa lan 1 (uu tien):\n");
    XoaNguoiDauTien(b);
    HangDoi *front = LayNguoiDauTien(b);
    printf("Sau khi xoa: Nguoi dau hang la: %s (phai la 20237302)\n", front ? front->MaThanhVien : "NULL");
    assert(front && strcmp(front->MaThanhVien, "20237302") == 0);

    printf("Xoa lan 2 (thuong):\n");
    XoaNguoiDauTien(b);
    front = LayNguoiDauTien(b);
    printf("Sau khi xoa: Nguoi dau hang la: %s (phai la NULL)\n", front ? front->MaThanhVien : "NULL");
    assert(front == NULL);
}

// Test TimNguoiTrongHangDoi
void test_TimNguoiTrongHangDoi() {
    printf("Test: Tim kiem nguoi trong hang doi theo ID\n");
    Sach *b = TimSach("Lap trinh C co ban", "Nguyen Van A");
    printf("Them nguoi moi: ID = \"20237303\", UuTien = 1\n");
    struct tm date = tao_ngay(4, 5, 124);
    ChenNutHangDoi("20237303", "Lap trinh C co ban", "Nguyen Van A", 1);
    HangDoi *found = TimNguoiTrongHangDoi(b, "20237303");
    printf("Ket qua tim kiem: %s\n", found ? found->MaThanhVien : "NULL");
    assert(found && strcmp(found->MaThanhVien, "20237303") == 0);
}

// Test DuyetHangDoi (in hang doi)
void test_DuyetHangDoi() {
    printf("Test: Duyet va in hang doi cho sach \"Lap trinh C co ban\"\n");
    printf("Dau vao: TieuDe = \"Lap trinh C co ban\", TacGia = \"Nguyen Van A\"\n");
    DuyetHangDoi("Lap trinh C co ban", "Nguyen Van A");
}

// Test luu va doc hang doi tu file
void test_Luu_Doc_HangDoi_File() {
    printf("Test: Luu va doc hang doi tu file\n");
    printf("Luu hang doi ra file test_queue_out.txt\n");
    LuuTatCaHangDoiVaoFile("test_queue_out.txt");

    printf("Doc hang doi tu file test_queue_out.txt\n");
    DocHangDoiTuFile("test_queue_out.txt");

    // Co the in lai hang doi de kiem tra
    printf("Noi dung hang doi sau khi doc file:\n");
    DuyetHangDoi("Lap trinh C co ban", "Nguyen Van A");
}

int main() {
    printf("===== BAT DAU CHAY CAC TEST CHO Queue.c =====\n\n");
    test_TaoNutHangDoi();
    printf("\n");
    test_ChenNutHangDoi_LayNguoiDauTien();
    printf("\n");
    test_XoaNguoiDauTien();
    printf("\n");
    test_TimNguoiTrongHangDoi();
    printf("\n");
    test_DuyetHangDoi();
    printf("\n");
    test_Luu_Doc_HangDoi_File();
    printf("\n===== TAT CA CAC TEST DA CHAY XONG! =====\n");
    system("PAUSE");
    return 0;
}
