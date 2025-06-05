#include "WaitingList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_WAITING 1000

static DanhSachCho danhSachCho[MAX_WAITING];
static int soLuongCho = 0;

void ThemYeuCauCho(const char *MaSinhVien, const char *MaSach, bool UuTien) {
    if (soLuongCho >= MAX_WAITING) {
        printf("Danh sach cho da day, khong the them moi!\n");
        return;
    }
    DanhSachCho yc;
    strncpy(yc.MaSinhVien, MaSinhVien, sizeof(yc.MaSinhVien));
    strncpy(yc.MaSach, MaSach, sizeof(yc.MaSach));
    yc.NgayDangKy = time(NULL);
    yc.UuTien = UuTien;
    danhSachCho[soLuongCho++] = yc;
    printf("Them yeu cau cho thanh cong!\n");
}

void XoaYeuCauCho(const char *MaSinhVien, const char *MaSach) {
    for (int i = 0; i < soLuongCho; ++i) {
        if (strcmp(danhSachCho[i].MaSinhVien, MaSinhVien) == 0 &&
            strcmp(danhSachCho[i].MaSach, MaSach) == 0) {
            for (int j = i; j < soLuongCho - 1; ++j) {
                danhSachCho[j] = danhSachCho[j + 1];
            }
            --soLuongCho;
            printf("Da xoa yeu cau cho!\n");
            return;
        }
    }
    printf("Khong tim thay yeu cau cho de xoa!\n");
}

DanhSachCho* TimKiemYeuCauCho(const char *MaSinhVien, const char *MaSach) {
    for (int i = 0; i < soLuongCho; ++i) {
        if (strcmp(danhSachCho[i].MaSinhVien, MaSinhVien) == 0 &&
            strcmp(danhSachCho[i].MaSach, MaSach) == 0) {
            return &danhSachCho[i];
        }
    }
    return NULL;
}

void HienThiDanhSachCho(const char *MaSach) {
    printf("=== DANH SACH CHO CUA SACH %s ===\n", MaSach);
    int dem = 0;
    for (int i = 0; i < soLuongCho; ++i) {
        if (strcmp(danhSachCho[i].MaSach, MaSach) == 0) {
            printf("STT %d:\n", ++dem);
            printf("  Ma sinh vien: %s\n", danhSachCho[i].MaSinhVien);
            printf("  Ngay dang ky: %s", ctime(&danhSachCho[i].NgayDangKy));
            printf("  Uu tien: %s\n", danhSachCho[i].UuTien ? "Co" : "Khong");
        }
    }
    if (dem == 0) printf("Khong co ban doc nao dang cho sach nay!\n");
}

DanhSachCho* LayYeuCauChoDauTien(const char *MaSach) {
    for (int i = 0; i < soLuongCho; ++i) {
        if (strcmp(danhSachCho[i].MaSach, MaSach) == 0) {
            return &danhSachCho[i];
        }
    }
    return NULL;
}

void DocDanhSachCho(const char *TenFile) {
    FILE *f = fopen(TenFile, "r");
    if (!f) {
        printf("Khong the mo file danh sach cho: %s\n", TenFile);
        return;
    }
    soLuongCho = 0;
    while (!feof(f)) {
        DanhSachCho yc;
        int uu;
        long tg;
        if (fscanf(f, "%12[^,],%20[^,],%ld,%d\n",
            yc.MaSinhVien, yc.MaSach, &tg, &uu) == 4) {
            yc.NgayDangKy = (time_t)tg;
            yc.UuTien = uu ? true : false;
            danhSachCho[soLuongCho++] = yc;
        }
    }
    fclose(f);
}

void GhiDanhSachCho(const char *TenFile) {
    FILE *f = fopen(TenFile, "w");
    if (!f) {
        printf("Khong the mo file de ghi danh sach cho: %s\n", TenFile);
        return;
    }
    for (int i = 0; i < soLuongCho; ++i) {
        fprintf(f, "%s,%s,%ld,%d\n",
            danhSachCho[i].MaSinhVien,
            danhSachCho[i].MaSach,
            (long)danhSachCho[i].NgayDangKy,
            danhSachCho[i].UuTien ? 1 : 0);
    }
    fclose(f);
}