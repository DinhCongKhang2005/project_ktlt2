#include "Member.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MEMBERS 1000

static BanDoc danhSachBanDoc[MAX_MEMBERS];
static int soLuongBanDoc = 0;

void ThemBanDoc(BanDoc *banDoc) {
    if (soLuongBanDoc >= MAX_MEMBERS) {
        printf("Khong the them ban doc moi, da day bo nho!\n");
        return;
    }
    danhSachBanDoc[soLuongBanDoc++] = *banDoc;
    printf("Them ban doc thanh cong!\n");
}

void XoaBanDoc(const char *MaSinhVien) {
    for (int i = 0; i < soLuongBanDoc; ++i) {
        if (strcmp(danhSachBanDoc[i].MaSinhVien, MaSinhVien) == 0) {
            for (int j = i; j < soLuongBanDoc - 1; ++j) {
                danhSachBanDoc[j] = danhSachBanDoc[j + 1];
            }
            --soLuongBanDoc;
            printf("Da xoa ban doc thanh cong!\n");
            return;
        }
    }
    printf("Khong tim thay ban doc de xoa!\n");
}

void CapNhatBanDoc(const char *MaSinhVien, BanDoc banDocMoi) {
    for (int i = 0; i < soLuongBanDoc; ++i) {
        if (strcmp(danhSachBanDoc[i].MaSinhVien, MaSinhVien) == 0) {
            danhSachBanDoc[i] = banDocMoi;
            printf("Cap nhat thong tin ban doc thanh cong!\n");
            return;
        }
    }
    printf("Khong tim thay ban doc de cap nhat!\n");
}

BanDoc* TimKiemBanDoc(const char *MaSinhVien) {
    for (int i = 0; i < soLuongBanDoc; ++i) {
        if (strcmp(danhSachBanDoc[i].MaSinhVien, MaSinhVien) == 0) {
            return &danhSachBanDoc[i];
        }
    }
    return NULL;
}

void HienThiThongTinBanDoc(const BanDoc *banDoc) {
    if (!banDoc) return;
    printf("Ma sinh vien: %s\n", banDoc->MaSinhVien);
    printf("Ten ban doc: %s\n", banDoc->TenBanDoc);
    printf("So sach dang muon: %d\n", banDoc->SoSachDangMuon);
}

void HienThiDanhSachBanDoc() {
    printf("=== DANH SACH BAN DOC ===\n");
    for (int i = 0; i < soLuongBanDoc; ++i) {
        printf("----- Ban doc %d -----\n", i + 1);
        HienThiThongTinBanDoc(&danhSachBanDoc[i]);
    }
    if (soLuongBanDoc == 0)
        printf("Khong co ban doc nao trong thu vien!\n");
}

void DocDuLieuBanDoc(const char *TenFile) {
    FILE *f = fopen(TenFile, "r");
    if (!f) {
        printf("Khong the mo file ban doc: %s\n", TenFile);
        return;
    }
    soLuongBanDoc = 0;
    while (!feof(f)) {
        BanDoc bd;
        if (fscanf(f, "%12[^,],%50[^,],%d\n",
            bd.MaSinhVien, bd.TenBanDoc, &bd.SoSachDangMuon) == 3) {
            danhSachBanDoc[soLuongBanDoc++] = bd;
        }
    }
    fclose(f);
}

void GhiDuLieuBanDoc(const char *TenFile) {
    FILE *f = fopen(TenFile, "w");
    if (!f) {
        printf("Khong the mo file de ghi ban doc: %s\n", TenFile);
        return;
    }
    for (int i = 0; i < soLuongBanDoc; ++i) {
        fprintf(f, "%s,%s,%d\n",
                danhSachBanDoc[i].MaSinhVien,
                danhSachBanDoc[i].TenBanDoc,
                danhSachBanDoc[i].SoSachDangMuon);
    }
    fclose(f);
}