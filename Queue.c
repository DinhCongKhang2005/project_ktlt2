#include "Queue.h"
#include "Book.h"
#include <stdlib.h>
#include <string.h>

// Tạo nút hàng đợi
HangDoi* TaoNutHangDoi(char* MaThanhVien, char* TieuDe, char* TacGia, bool UuTien) {
    HangDoi *nutMoi = (HangDoi*)malloc(sizeof(HangDoi));
    strcpy(nutMoi->MaThanhVien, MaThanhVien);
    strcpy(nutMoi->TieuDe, TieuDe);
    strcpy(nutMoi->TacGia, TacGia);
    nutMoi->UuTien = UuTien;
    memset(&nutMoi->ThoiGianAnDinh, 0, sizeof(struct tm));
    nutMoi->TiepTheo = NULL;
    return nutMoi;
}

// Thêm nút vào hàng đợi
void ChenNutHangDoi(char *MaThanhVien, char *TieuDe, char *TacGia, bool UuTien) {
    Sach *sach = TimSach(TieuDe, TacGia);
    if (sach == NULL) {
        printf("Khong tim thay sach: %s - %s\n", TieuDe, TacGia);
        return;
    }

    HangDoi *nutMoi = TaoNutHangDoi(MaThanhVien, TieuDe, TacGia, UuTien);

    if (UuTien) {
        if (sach->HangDoiUuTien == NULL) {
            sach->HangDoiUuTien = nutMoi;
        } else {
            HangDoi *temp = sach->HangDoiUuTien;
            while (temp->TiepTheo != NULL)
                temp = temp->TiepTheo;
            temp->TiepTheo = nutMoi;
        }
    } else {
        if (sach->HangDoiBinhThuong == NULL) {
            sach->HangDoiBinhThuong = nutMoi;
        } else {
            HangDoi *temp = sach->HangDoiBinhThuong;
            while (temp->TiepTheo != NULL)
                temp = temp->TiepTheo;
            temp->TiepTheo = nutMoi;
        }
    }
}

// Lấy thông tin người đầu tiên
HangDoi* LayNguoiDauTien(Sach *sach) {
    if (sach->HangDoiUuTien) {
        return sach->HangDoiUuTien;
    } else if (sach->HangDoiBinhThuong) {
        return sach->HangDoiBinhThuong;
    } else {
        return NULL;
    }
}

// Xoá node đầu tiên của cả hai hàng đợi (ưu tiên trước)
void XoaNguoiDauTien(Sach *sach) {
    HangDoi *temp;
    if (sach->HangDoiUuTien) {
        temp = sach->HangDoiUuTien;
        sach->HangDoiUuTien = sach->HangDoiUuTien->TiepTheo;
        free(temp);
        printf("Da xoa nguoi muon trong hang uu tien.\n");
    } else if (sach->HangDoiBinhThuong) {
        temp = sach->HangDoiBinhThuong;
        sach->HangDoiBinhThuong = sach->HangDoiBinhThuong->TiepTheo;
        free(temp);
        printf("Da xoa nguoi muon trong hang thuong.\n");
    } else {
        printf("Hang doi rong, khong co ai de xoa.\n");
    }
}

// Duyệt in cả hai hàng đợi
void DuyetHangDoi(char* TieuDe, char* TacGia) {
    Sach* sach = TimSach(TieuDe, TacGia);
    if (!sach) return;

    printf("Hang doi uu tien:\n");
    HangDoi* p = sach->HangDoiUuTien;
    while (p) {
        printf("%s (ID: %s)\n", p->TieuDe, p->MaThanhVien);
        p = p->TiepTheo;
    }

    printf("Hang doi thuong:\n");
    p = sach->HangDoiBinhThuong;
    while (p) {
        printf("%s (ID: %s)\n", p->TieuDe, p->MaThanhVien);
        p = p->TiepTheo;
    }
}

// Tìm người trong hàng đợi ưu tiên hoặc thường của một cuốn sách
HangDoi* TimNguoiTrongHangDoi(Sach* sach, char* MaThanhVien) {
    HangDoi* p = sach->HangDoiUuTien;
    while (p) {
        if (strcmp(p->MaThanhVien, MaThanhVien) == 0) return p;
        p = p->TiepTheo;
    }

    p = sach->HangDoiBinhThuong;
    while (p) {
        if (strcmp(p->MaThanhVien, MaThanhVien) == 0) return p;
        p = p->TiepTheo;
    }

    return NULL;
}

// Lưu từng nhánh hàng đợi vào file
void LuuHangDoiVaoFileHelper(FILE *f, HangDoi *q) {
    while (q) {
        const char *id = (q->MaThanhVien[0]) ? q->MaThanhVien : "NULL";
        const char *tieuDe = (q->TieuDe[0]) ? q->TieuDe : "NULL";
        const char *tacGia = (q->TacGia[0]) ? q->TacGia : "NULL";
        fprintf(f, "%s;%s;%s;%d/%d/%d;%d\n",
            id, tieuDe, tacGia,
            q->ThoiGianAnDinh.tm_mday,
            q->ThoiGianAnDinh.tm_mon + 1,
            q->ThoiGianAnDinh.tm_year + 1900,
            q->UuTien);
        q = q->TiepTheo;
    }
}

// Lưu hàng đợi của một sách vào file
void LuuHangDoiSachVaoFile(Sach *sach, void *filePtr) {
    FILE *f = (FILE *)filePtr;
    if (!sach || !f) return;
    LuuHangDoiVaoFileHelper(f, sach->HangDoiUuTien);
    LuuHangDoiVaoFileHelper(f, sach->HangDoiBinhThuong);
}

// Dùng cho hàm LuuTatCaHangDoiVaoFile
void DuyetAvlVoiThamSo(AVLNode *goc, void (*tham)(Sach *, void *), void *thamSo) {
    if (!goc) return;
    DuyetAvlVoiThamSo(goc->Trai, tham, thamSo);
    if (goc->DuLieu == NULL) {
        printf("LỖI: goc->DuLieu == NULL\n");
        return;
    }
    tham((Sach *)goc->DuLieu, thamSo);
    DuyetAvlVoiThamSo(goc->Phai, tham, thamSo);
}

// Duyệt toàn bộ sách để lưu hàng đợi
void LuuTatCaHangDoiVaoFile(const char *tenFile) {
    FILE *f = fopen(tenFile, "w");
    if (!f) {
        printf("Khong the mo file %s de ghi!\n", tenFile);
        return;
    }
    for (int i = 0; i < KichThuocBang; ++i)
        if(BangBamSach[i]){
            DuyetAvlVoiThamSo(BangBamSach[i], LuuHangDoiSachVaoFile, f);
        }
    fclose(f);
}

// Đọc từ file ra
void DocHangDoiTuFile(const char *tenFile) {
    FILE *f = fopen(tenFile, "r");
    if (!f) {
        printf("Khong the mo file %s de doc!\n", tenFile);
        return;
    }

    char dong[300];
    while (fgets(dong, sizeof(dong), f)) {
        if (strcmp(dong, "\n") == 0)
            continue;
        dong[strcspn(dong, "\n")] = '\0';
        HangDoi *nutMoi = (HangDoi *)malloc(sizeof(HangDoi));

        sscanf(dong, "%12[^;];%199[^;];%199[^;];%d/%d/%d;%d",
                nutMoi->MaThanhVien, nutMoi->TieuDe, nutMoi->TacGia,
                &nutMoi->ThoiGianAnDinh.tm_mday, &nutMoi->ThoiGianAnDinh.tm_mon,
                &nutMoi->ThoiGianAnDinh.tm_year, &nutMoi->UuTien);

        nutMoi->TiepTheo = NULL;

        Sach *sach = TimSach(nutMoi->TieuDe, nutMoi->TacGia);
        if (sach) {
            ChenNutHangDoiVaoSach(sach, nutMoi);
        } else {
            free(nutMoi);
        }
    }

    fclose(f);
}

// Thêm nút vào hàng đợi cho sách
void ChenNutHangDoiVaoSach(Sach *sach, HangDoi *nut) {
    HangDoi **dau = nut->UuTien ? &sach->HangDoiUuTien : &sach->HangDoiBinhThuong;

    if (!*dau) {
        *dau = nut;
    } else {
        HangDoi *cur = *dau;
        while (cur->TiepTheo) cur = cur->TiepTheo;
        cur->TiepTheo = nut;
    }
}