#ifndef DuLieu_H
#define DuLieu_H
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#define KichThuocBang 10

// Cấu trúc hàng đợi mượn sách
typedef struct HangDoi {
    char MaThanhVien[13], TieuDe[200], TacGia[200];
    struct tm ThoiGianAnDinh; // Thời gian sách đã về và ấn định cho người này
    bool UuTien; // Trạng thái ưu tiên
    struct HangDoi *TiepTheo; // Con trỏ next để lưu trữ thông tin hàng đợi
} HangDoi;

// Cấu trúc sách
typedef struct Sach {
    char TieuDe[200], TacGia[200];
    int SoLuong;
    HangDoi* HangDoiUuTien;
    HangDoi* HangDoiBinhThuong;
} Sach;

// Cấu trúc thành viên
typedef struct ThanhVien {
    char MaThanhVien[13], HoTen[100];
    int SoLuongDangMuon;
} ThanhVien;

// Cấu trúc phiếu mượn
typedef struct PhieuMuon {
    char MaPhieu[7], MaThanhVien[13], TieuDe[200], TacGia[200];
    struct tm ThoiGianMuon;
} PhieuMuon;

/*----------------------------------------------------------------------------------------*/

// Cấu trúc cây AVL tổng quát
typedef struct AVLNode {
    void *Khoa; // Khóa của nút tự định nghĩa kiểu dữ liệu
    void *DuLieu; // Dữ liệu của nút tự định nghĩa kiểu dữ liệu
    struct AVLNode *Trai, *Phai; // Con trái và con phải của nút
    int ChieuCao; // Chiều cao của nút
} AVLNode;

// Khai báo biến toàn cục cho bảng băm, được định nghĩa ở main.c
extern AVLNode *BangBamSach[KichThuocBang];        // Bảng băm cho sách
extern AVLNode *BangBamThanhVien[KichThuocBang];   // Bảng băm cho thành viên
extern AVLNode *BangBamPhieuMuon[KichThuocBang];   // Bảng băm cho thông tin mượn sách

#endif