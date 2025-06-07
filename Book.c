#include "Book.h"
#include "Utility.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 1000

static Sach danhSachSach[MAX_BOOKS];
static int soLuongSach = 0;

void ThemSach(Sach sach) {
    if (soLuongSach >= MAX_BOOKS) {
        printf("Khong the them sach moi, da day bo nho!\n");
        return;
    }
    danhSachSach[soLuongSach++] = sach;
    printf("Them sach thanh cong!\n");
}

void XoaSach(const char *TenSach, const char *TacGia) {
    for (int i = 0; i < soLuongSach; ++i) {
        if (strcmp(danhSachSach[i].TenSach, TenSach) == 0 &&
            strcmp(danhSachSach[i].TacGia, TacGia) == 0) {
            for (int j = i; j < soLuongSach - 1; ++j) {
                danhSachSach[j] = danhSachSach[j + 1];
            }
            --soLuongSach;
            printf("Da xoa sach thanh cong!\n");
            return;
        }
    }
    printf("Khong tim thay sach de xoa!\n");
}

void CapNhatSach(const char *TenSach, const char *TacGia, Sach sachMoi) {
    for (int i = 0; i < soLuongSach; ++i) {
        if (strcmp(danhSachSach[i].TenSach, TenSach) == 0 &&
            strcmp(danhSachSach[i].TacGia, TacGia) == 0) {
            danhSachSach[i] = sachMoi;
            printf("Cap nhat thong tin sach thanh cong!\n");
            return;
        }
    }
    printf("Khong tim thay sach de cap nhat!\n");
}

Sach* TimKiemSach(const char *TenSach, const char *TacGia) {
    for (int i = 0; i < soLuongSach; ++i) {
        if (strcmp(danhSachSach[i].TenSach, TenSach) == 0 &&
            strcmp(danhSachSach[i].TacGia, TacGia) == 0) {
            return &danhSachSach[i];
        }
    }
    return NULL;
}

Sach* TimKiemSachBangMa(const char *MaSach) {
    for (int i = 0; i < soLuongSach; ++i) {
        if (strcmp(danhSachSach[i].MaSach, MaSach) == 0) {
            return &danhSachSach[i];
        }
    }
    return NULL;
}

void HienThiThongTinSach(const Sach *sach) {
    if (!sach) return;
    printf("Ma sach: %s\n", sach->MaSach);
    printf("Ten sach: %s\n", sach->TenSach);
    printf("Tac gia: %s\n", sach->TacGia);
    printf("The loai: %s\n", sach->TheLoai);
    printf("Tong so luong: %d\n", sach->TongSoLuong);
    printf("So luong con lai: %d\n", sach->SoLuongConLai);
}

void HienThiDanhSachSach() {
    printf("=== DANH SACH SACH ===\n");
    for (int i = 0; i < soLuongSach; ++i) {
        printf("----- Sach %d -----\n", i + 1);
        HienThiThongTinSach(&danhSachSach[i]);
    }
    if (soLuongSach == 0)
        printf("Khong co sach nao trong thu vien!\n");
}

void DocDuLieuSach(const char *TenFile) {
    FILE *f = fopen(TenFile, "r");
    if (!f) {
        printf("Khong the mo file sach: %s\n", TenFile);
        return;
    }
    soLuongSach = 0;
    while (!feof(f)) {
        Sach sach;
        if (fscanf(f, "%20[^,],%100[^,],%50[^,],%30[^,],%d,%d\n",
            sach.MaSach, sach.TenSach, sach.TacGia,
            sach.TheLoai, &sach.TongSoLuong, &sach.SoLuongConLai) == 6) {
            danhSachSach[soLuongSach++] = sach;
        }
    }
    fclose(f);
}

void GhiDuLieuSach(const char *TenFile) {
    FILE *f = fopen(TenFile, "w");
    if (!f) {
        printf("Khong the mo file de ghi sach: %s\n", TenFile);
        return;
    }
    for (int i = 0; i < soLuongSach; ++i) {
        fprintf(f, "%s,%s,%s,%s,%d,%d\n",
                danhSachSach[i].MaSach,
                danhSachSach[i].TenSach,
                danhSachSach[i].TacGia,
                danhSachSach[i].TheLoai,
                danhSachSach[i].TongSoLuong,
                danhSachSach[i].SoLuongConLai);
    }
    fclose(f);
}