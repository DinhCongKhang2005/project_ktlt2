#include "Transaction.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TRANSACTIONS 2000

static GiaoDich danhSachGiaoDich[MAX_TRANSACTIONS];
static int soLuongGiaoDich = 0;

void TaoPhieuMuon(const char *MaSinhVien, const char *MaSach, struct tm NgayMuon, struct tm NgayHenTra) {
    if (soLuongGiaoDich >= MAX_TRANSACTIONS) {
        printf("Khong the tao phieu muon moi, da day bo nho!\n");
        return;
    }
    GiaoDich gd;
    snprintf(gd.MaPhieuMuon, sizeof(gd.MaPhieuMuon), "%s_%s_%ld", MaSinhVien, MaSach, time(NULL));
    strncpy(gd.MaSinhVien, MaSinhVien, sizeof(gd.MaSinhVien));
    strncpy(gd.MaSach, MaSach, sizeof(gd.MaSach));
    gd.NgayMuon = NgayMuon;
    gd.NgayHenTra = NgayHenTra;
    gd.DaTra = false;
    danhSachGiaoDich[soLuongGiaoDich++] = gd;
    printf("Tao phieu muon thanh cong!\n");
}

void GhiNhanTraSach(const char *MaPhieuMuon, struct tm NgayTra) {
    for (int i = 0; i < soLuongGiaoDich; ++i) {
        if (strcmp(danhSachGiaoDich[i].MaPhieuMuon, MaPhieuMuon) == 0 && !danhSachGiaoDich[i].DaTra) {
            danhSachGiaoDich[i].NgayTra = NgayTra;
            danhSachGiaoDich[i].DaTra = true;
            printf("Ghi nhan tra sach thanh cong!\n");
            return;
        }
    }
    printf("Khong tim thay phieu muon phu hop de ghi nhan tra sach!\n");
}

void HienThiThongTinGiaoDich(const GiaoDich *giaoDich) {
    if (!giaoDich) return;
    printf("Ma phieu muon: %s\n", giaoDich->MaPhieuMuon);
    printf("Ma sinh vien: %s\n", giaoDich->MaSinhVien);
    printf("Ma sach: %s\n", giaoDich->MaSach);
    printf("Ngay muon: %02d/%02d/%04d\n", giaoDich->NgayMuon.tm_mday, giaoDich->NgayMuon.tm_mon + 1, giaoDich->NgayMuon.tm_year + 1900);
    printf("Ngay hen tra: %02d/%02d/%04d\n", giaoDich->NgayHenTra.tm_mday, giaoDich->NgayHenTra.tm_mon + 1, giaoDich->NgayHenTra.tm_year + 1900);
    if (giaoDich->DaTra)
        printf("Ngay tra: %02d/%02d/%04d\n", giaoDich->NgayTra.tm_mday, giaoDich->NgayTra.tm_mon + 1, giaoDich->NgayTra.tm_year + 1900);
    else
        printf("Chua tra sach\n");
}

void HienThiDanhSachGiaoDich() {
    printf("=== DANH SACH GIAO DICH ===\n");
    for (int i = 0; i < soLuongGiaoDich; ++i) {
        printf("----- Giao dich %d -----\n", i + 1);
        HienThiThongTinGiaoDich(&danhSachGiaoDich[i]);
    }
    if (soLuongGiaoDich == 0)
        printf("Khong co giao dich nao trong he thong!\n");
}

void DocDuLieuGiaoDich(const char *TenFile) {
    FILE *f = fopen(TenFile, "r");
    if (!f) {
        printf("Khong the mo file giao dich: %s\n", TenFile);
        return;
    }
    soLuongGiaoDich = 0;
    while (!feof(f)) {
        GiaoDich gd;
        int tra, nm, nh, nt, nhtr, nht, ntr;
        if (fscanf(f, "%20[^,],%12[^,],%20[^,],%d/%d/%d,%d/%d/%d,%d,%d/%d/%d\n",
            gd.MaPhieuMuon, gd.MaSinhVien, gd.MaSach,
            &gd.NgayMuon.tm_mday, &gd.NgayMuon.tm_mon, &gd.NgayMuon.tm_year,
            &gd.NgayHenTra.tm_mday, &gd.NgayHenTra.tm_mon, &gd.NgayHenTra.tm_year,
            &tra, &gd.NgayTra.tm_mday, &gd.NgayTra.tm_mon, &gd.NgayTra.tm_year) >= 10) {
            gd.NgayMuon.tm_mon -= 1; gd.NgayMuon.tm_year -= 1900;
            gd.NgayHenTra.tm_mon -= 1; gd.NgayHenTra.tm_year -= 1900;
            gd.DaTra = tra ? true : false;
            if (gd.DaTra) {
                gd.NgayTra.tm_mon -= 1; gd.NgayTra.tm_year -= 1900;
            }
            danhSachGiaoDich[soLuongGiaoDich++] = gd;
        }
    }
    fclose(f);
}

void GhiDuLieuGiaoDich(const char *TenFile) {
    FILE *f = fopen(TenFile, "w");
    if (!f) {
        printf("Khong the mo file de ghi giao dich: %s\n", TenFile);
        return;
    }
    for (int i = 0; i < soLuongGiaoDich; ++i) {
        fprintf(f, "%s,%s,%s,%02d/%02d/%04d,%02d/%02d/%04d,%d",
                danhSachGiaoDich[i].MaPhieuMuon,
                danhSachGiaoDich[i].MaSinhVien,
                danhSachGiaoDich[i].MaSach,
                danhSachGiaoDich[i].NgayMuon.tm_mday, danhSachGiaoDich[i].NgayMuon.tm_mon + 1, danhSachGiaoDich[i].NgayMuon.tm_year + 1900,
                danhSachGiaoDich[i].NgayHenTra.tm_mday, danhSachGiaoDich[i].NgayHenTra.tm_mon + 1, danhSachGiaoDich[i].NgayHenTra.tm_year + 1900,
                danhSachGiaoDich[i].DaTra ? 1 : 0);
        if (danhSachGiaoDich[i].DaTra) {
            fprintf(f, ",%02d/%02d/%04d",
                danhSachGiaoDich[i].NgayTra.tm_mday, danhSachGiaoDich[i].NgayTra.tm_mon + 1, danhSachGiaoDich[i].NgayTra.tm_year + 1900);
        }
        fprintf(f, "\n");
    }
    fclose(f);
}