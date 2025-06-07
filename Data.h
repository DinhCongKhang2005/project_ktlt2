#ifndef DATA_H
#define DATA_H

#include <time.h>
#include <stdbool.h>

typedef struct Sach {
    char MaSach[21];
    char TenSach[101];
    char TacGia[51];
    char TheLoai[31];
    int TongSoLuong;
    int SoLuongConLai;
    struct DanhSachCho *DanhSachChoDau;
} Sach;

typedef struct BanDoc {
    char MaSinhVien[13];
    char TenBanDoc[51];
    int SoSachDangMuon;
} BanDoc;

typedef struct GiaoDich {
    char MaPhieuMuon[21];
    char MaSinhVien[13];
    char MaSach[21];
    struct tm NgayMuon;
    struct tm NgayHenTra;
    struct tm NgayTra;
    bool DaTra;
} GiaoDich;

typedef struct DanhSachCho {
    char MaSinhVien[13];
    char MaSach[21];
    time_t NgayDangKy;
    bool UuTien;
    struct DanhSachCho *TiepTheo;
} DanhSachCho;

#endif