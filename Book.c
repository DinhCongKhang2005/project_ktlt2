#include "Book.h"
#include "AVL_Tree.h"
#include "hash.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

AVLNode *BangBamSach[KichThuocBang] = {NULL}; // <-- Định nghĩa duy nhất ở đây

// Chuẩn hóa chuỗi về chữ thường
void ChuyenChuoiVeThuong(char *chuoi) {
    for (; *chuoi; ++chuoi) *chuoi = tolower(*chuoi);
}

// Hàm trim chuẩn hóa chuỗi (xóa khoảng trắng đầu/cuối)
void ChuanHoaChuoi(char *chuoi) {
    char *batDau = chuoi;
    while (isspace((unsigned char)*batDau)) batDau++;
    if (batDau != chuoi) memmove(chuoi, batDau, strlen(batDau) + 1);

    char *ketThuc = chuoi + strlen(chuoi) - 1;
    while (ketThuc >= chuoi && isspace((unsigned char)*ketThuc)) ketThuc--;
    *(ketThuc + 1) = '\0';
}

// Sinh key từ tiêu đề và tác giả
void SinhKhoa(char *khoa, const char *tieuDe, const char *tacGia) {
    char t[100], a[100];
    strncpy(t, tieuDe, sizeof(t) - 1); t[sizeof(t) - 1] = '\0';
    strncpy(a, tacGia, sizeof(a) - 1); a[sizeof(a) - 1] = '\0';
    ChuanHoaChuoi(t); ChuanHoaChuoi(a);
    ChuyenChuoiVeThuong(t); ChuyenChuoiVeThuong(a);
    snprintf(khoa, 201, "%s_%s", t, a);
}

// So sánh key dạng chuỗi


// Đọc dữ liệu sách từ file
void DocSachTuFile(const char *tenFile) {
    FILE *f = fopen(tenFile, "r");
    if (!f) {
        printf("Không thể mở file %s\n", tenFile);
        return;
    }
    char dong[256];
    while (fgets(dong, sizeof(dong), f)) {
        if (strcmp(dong, "\n") == 0)
            continue;
        dong[strcspn(dong, "\n")] = '\0';
        Sach sach;
        char *token = strtok(dong, ";");
        if (!token) continue;
        strncpy(sach.TieuDe, token, sizeof(sach.TieuDe) - 1); sach.TieuDe[sizeof(sach.TieuDe) - 1] = '\0';

        token = strtok(NULL, ";");
        if (!token) continue;
        strncpy(sach.TacGia, token, sizeof(sach.TacGia) - 1); sach.TacGia[sizeof(sach.TacGia) - 1] = '\0';

        token = strtok(NULL, ";");
        if (!token) continue;
        sach.SoLuong = atoi(token);
        sach.HangDoiUuTien = NULL;
        sach.HangDoiBinhThuong = NULL;
        ChenSach(sach);
    }
    fclose(f);
}

// Chèn thủ công
void ChenSach(Sach sach) {
    ChuanHoaChuoi(sach.TieuDe);
    ChuanHoaChuoi(sach.TacGia);
    ChuyenChuoiVeThuong(sach.TieuDe);
    ChuyenChuoiVeThuong(sach.TacGia);

    char khoa[201];
    SinhKhoa(khoa, sach.TieuDe, sach.TacGia);
    int chiSo = BamChuoi(khoa);

    AVLNode *timThay = TimKiemCayAvl(BangBamSach[chiSo], khoa, SoSanhChuoi);
    if (!timThay) {
        Sach *sachMoi = (Sach *)malloc(sizeof(Sach));
        if (sachMoi) {
            *sachMoi = sach;
            char *khoaCopy = strdup(khoa);
            BangBamSach[chiSo] = ChenVaoCayAvl(BangBamSach[chiSo], sachMoi, khoaCopy, SoSanhChuoi);
        }
    } else {
        Sach *daCo = (Sach *)timThay->DuLieu;
        daCo->SoLuong += sach.SoLuong;
    }
}

// Tìm kiếm sách
Sach* TimSach(const char* tieuDe, const char* tacGia) {
    char khoa[201];
    SinhKhoa(khoa, tieuDe, tacGia);
    int chiSo = BamChuoi(khoa);

    AVLNode *timThay = TimKiemCayAvl(BangBamSach[chiSo], khoa, SoSanhChuoi);
    if (timThay) return (Sach *)timThay->DuLieu;
    return NULL;
}

// Xóa sách
void XoaSach(const char* tieuDe, const char* tacGia) {
    char khoa[201];
    SinhKhoa(khoa, tieuDe, tacGia);
    int chiSo = BamChuoi(khoa);
    BangBamSach[chiSo] = XoaKhoiCayAvl(BangBamSach[chiSo], khoa, SoSanhChuoi);
}

// Hàm duyệt AVL để hiển thị sách
void InSach(Sach *sach) {
    printf("%-30s | %-20s | %d\n", sach->TieuDe, sach->TacGia, sach->SoLuong);
}

void DuyetAvlSach(AVLNode *goc, void (*tham)(Sach *)) {
    if (!goc) return;
    DuyetAvlSach(goc->Trai, tham);
    tham((Sach *)goc->DuLieu);
    DuyetAvlSach(goc->Phai, tham);
}

// Hiển thị toàn bộ thông tin sách trong thư viện
void HienThiTatCaSach() {
    printf("%-30s | %-20s | %s\n", "Tieu de", "Tac gia", "So luong");
    printf("--------------------------------------------------------------\n");
    for (int i = 0; i < KichThuocBang; ++i) {
        DuyetAvlSach(BangBamSach[i], InSach);
    }
}

// Lưu vào file
typedef struct HangDoiGhiFile {
    AVLNode* Nut;
    struct HangDoiGhiFile *TiepTheo;
} HangDoiGhiFile;

HangDoiGhiFile* TaoNutHangDoiGhiFile(AVLNode *nut){
    HangDoiGhiFile* nutMoi = (HangDoiGhiFile*)malloc(sizeof(HangDoiGhiFile));
    nutMoi->Nut = nut;
    nutMoi->TiepTheo = NULL;
    return nutMoi;
}

// Ghi dữ liệu theo chiều rộng 
void LuuSachVaoFileHelper(AVLNode *nut, FILE *file) {
    if (nut == NULL) return;

    HangDoiGhiFile* dau = TaoNutHangDoiGhiFile(nut);
    HangDoiGhiFile* duoi = dau;

    while (dau != NULL) {
        if (dau->Nut->Trai != NULL) {
            duoi->TiepTheo = TaoNutHangDoiGhiFile(dau->Nut->Trai);
            duoi = duoi->TiepTheo;
        }
        if (dau->Nut->Phai != NULL) {
            duoi->TiepTheo = TaoNutHangDoiGhiFile(dau->Nut->Phai);
            duoi = duoi->TiepTheo;
        }

        Sach* sach = dau->Nut->DuLieu;
        fprintf(file, "%s;%s;%d\n", sach->TieuDe, sach->TacGia, sach->SoLuong);

        HangDoiGhiFile* tmp = dau;
        dau = dau->TiepTheo;
        free(tmp);
    }
}

void LuuSachVaoFile(const char *tenFile) {
    FILE *f = fopen(tenFile, "w");
    if (!f) {
        printf("Không thể mở file %s để ghi!\n", tenFile);
        return;
    }
    for (int i = 0; i < KichThuocBang; ++i) {
        LuuSachVaoFileHelper(BangBamSach[i], f);
    }
    fclose(f);
}