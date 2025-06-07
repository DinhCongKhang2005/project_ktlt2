#include "Book.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "Data.h"



// Test chuyển chuỗi về chữ thường
void test_ChuyenChuoiVeThuong() {
    printf("Test: Chuyen chuoi ve chu thuong\n");
    printf("Dau vao: \"HeLLo\"\n");
    char s1[] = "HeLLo";
    ChuyenChuoiVeThuong(s1);
    printf("Sau khi xu ly: \"%s\"\n", s1);
    assert(strcmp(s1, "hello") == 0);
}

// Test trim (chuẩn hóa chuỗi)
void test_ChuanHoaChuoi() {
    printf("Test: Xoa khoang trang dau/cuoi chuoi\n");
    printf("Dau vao: \"   hello   \"\n");
    char s1[] = "   hello   ";
    ChuanHoaChuoi(s1);
    printf("Sau khi xu ly: \"%s\"\n", s1);
    assert(strcmp(s1, "hello") == 0);
}

// Test sinh key từ tiêu đề và tác giả
void test_SinhKhoa() {
    printf("Test: Tao key tu title va author\n");
    printf("Dau vao: title = \"   HeLLo\", author = \"   WorLD   \"\n");
    char khoa[201];
    SinhKhoa(khoa, "   HeLLo", "   WorLD   ");
    printf("Key sinh ra: \"%s\"\n", khoa);
    assert(strcmp(khoa, "hello_world") == 0);
}

// Test chèn và tìm kiếm sách
void test_ChenVaTimSach() {
    printf("Test: Them sach va tim sach\n");
    printf("Dau vao: TieuDe = \"Lap trinh C co ban\", TacGia = \"Nguyen Van A\", SoLuong = 5\n");
    Sach sach;
    strcpy(sach.TieuDe, "Lap trinh C co ban");
    strcpy(sach.TacGia, "Nguyen Van A");
    sach.SoLuong = 5;
    sach.HangDoiUuTien = NULL;
    sach.HangDoiBinhThuong = NULL;

    ChenSach(sach);

    Sach *timThay = TimSach("Lap trinh C co ban", "Nguyen Van A");
    if (timThay) {
        printf("Tim thay sach: TieuDe = \"%s\", TacGia = \"%s\", SoLuong = %d\n", timThay->TieuDe, timThay->TacGia, timThay->SoLuong);
    } else {
        printf("Khong tim thay sach!\n");
    }
    assert(timThay != NULL);
    assert(strcmp(timThay->TieuDe, "lap trinh c co ban") == 0 || strcmp(timThay->TieuDe, "Lap trinh C co ban") == 0);
    assert(strcmp(timThay->TacGia, "nguyen van a") == 0 || strcmp(timThay->TacGia, "Nguyen Van A") == 0);
    assert(timThay->SoLuong == 5);
}

// Test cộng dồn số lượng khi thêm sách trùng
void test_ChenSachTrung() {
    printf("Test: Them sach trung va kiem tra SoLuong\n");
    printf("Dau vao lan 1: TieuDe = \"Lap trinh Spin\", TacGia = \"Nguyen Van BT\", SoLuong = 7\n");
    Sach sach;
    strcpy(sach.TieuDe, "Lap trinh Spin");
    strcpy(sach.TacGia, "Nguyen Van BT");
    sach.SoLuong = 7;
    sach.HangDoiUuTien = NULL;
    sach.HangDoiBinhThuong = NULL;
    ChenSach(sach);

    printf("Dau vao lan 2: TieuDe = \"Lap trinh Spin\", TacGia = \"Nguyen Van BT\", SoLuong = 3\n");
    sach.SoLuong = 3;
    ChenSach(sach);

    Sach *timThay = TimSach("Lap trinh Spin", "Nguyen Van BT");
    if (timThay) {
        printf("Sau khi them 2 lan, so luong la: %d\n", timThay->SoLuong);
    }
    assert(timThay && timThay->SoLuong == 10);
}

// Test xóa sách
void test_XoaSach() {
    printf("Test: Xoa sach\n");
    printf("Dau vao: TieuDe = \"DelBook\", TacGia = \"DelAuthor\", SoLuong = 1\n");
    Sach sach;
    strcpy(sach.TieuDe, "DelBook");
    strcpy(sach.TacGia, "DelAuthor");
    sach.SoLuong = 1;
    sach.HangDoiUuTien = NULL;
    sach.HangDoiBinhThuong = NULL;
    ChenSach(sach);

    printf("Xoa sach: TieuDe = \"DelBook\", TacGia = \"DelAuthor\"\n");
    XoaSach("DelBook", "DelAuthor");
    Sach *timThay = TimSach("DelBook", "DelAuthor");
    if (timThay) {
        printf("Xoa khong thanh cong!\n");
    } else {
        printf("Sach da duoc xoa khoi he thong.\n");
    }
    assert(timThay == NULL);
}

// Test đọc và lưu file
void test_DocVaLuuFile() {
    printf("Test: Doc sach tu file va luu sach ra file\n");
    printf("Tao file test_books.txt voi noi dung mau\n");
    FILE *f = fopen("test_books.txt", "w");
    fprintf(f, "Lap trinh C co ban;Nguyen Van A;5\nLap trinh Spin;Nguyen Van BT;7\n");
    fclose(f);

    printf("Doc sach tu file test_books.txt\n");
    DocSachTuFile("test_books.txt");
    Sach *b1 = TimSach("Lap trinh C co ban", "Nguyen Van A");
    Sach *b2 = TimSach("Lap trinh Spin", "Nguyen Van BT");
    if (b1) printf("Tim duoc Lap trinh C co ban: SoLuong = %d\n", b1->SoLuong);
    if (b2) printf("Tim duoc Lap trinh Spin: SoLuong = %d\n", b2->SoLuong);
    if (b1) printf("b1->SoLuong = %d\n", b1->SoLuong);
    assert(b1 && b1->SoLuong == 5);
    assert(b2 && b2->SoLuong == 7);
     printf("b1 = %p\n", b1);

    printf("Luu du lieu sach ra file test_out.txt\n");
    LuuSachVaoFile("test_out.txt");
    printf("Ban co the mo test_out.txt de kiem tra ket qua.\n");
}

int main() {
    printf("===== BAT DAU CHAY CAC TEST CHO Book.c =====\n\n");
    test_ChuyenChuoiVeThuong();
    printf("\n");
    test_ChuanHoaChuoi();
    printf("\n");
    test_SinhKhoa();
    printf("\n");
    test_ChenVaTimSach();
    printf("\n");
    test_ChenSachTrung();
    printf("\n");
    test_XoaSach();
    printf("\n");
    test_DocVaLuuFile();
    printf("\n===== TAT CA CAC TEST DA CHAY XONG! =====\n");
    system("PAUSE");
    return 0;
}