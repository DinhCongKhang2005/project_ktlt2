#include "Member.h"
#include <string.h>
#include "AVL_Tree.h"
#include "Data.h"
#include "hash.h"
AVLNode *BangBamThanhVien[KichThuocBang] = {NULL};
// Thêm thành viên
void ThemThanhVien(ThanhVien *thanhVienMoi) {
    char *khoa = thanhVienMoi->MaThanhVien; // Lấy MaThanhVien làm khóa
    unsigned int chiSo = BamChuoi(khoa);
    BangBamThanhVien[chiSo] = ChenVaoCayAvl(BangBamThanhVien[chiSo], thanhVienMoi, khoa, SoSanhChuoi);
}

// Đọc từ file csv
void DocThanhVienTuFile(const char *tenFile) {
    FILE *file = fopen(tenFile, "r");
    if (file == NULL) {
        printf("Khong the mo file! %s\n", tenFile);
        return;
    }
    char dong[256];
    while (fgets(dong, sizeof(dong), file)){
        if (strcmp(dong, "\n") == 0)
            continue;
        dong[strcspn(dong, "\n")] = '\0';
        ThanhVien *thanhVienMoi = (ThanhVien*)malloc(sizeof(ThanhVien));
        sscanf(dong, "%[^,],%[^,],%d", thanhVienMoi->MaThanhVien, thanhVienMoi->HoTen, &thanhVienMoi->SoLuongDangMuon);
        ThemThanhVien(thanhVienMoi);
    }
    fclose(file);
}

// Tìm kiếm thành viên
ThanhVien* TimThanhVien(char *maThanhVien) {
    unsigned int chiSo = BamChuoi(maThanhVien);
    AVLNode *ketQua = TimKiemCayAvl(BangBamThanhVien[chiSo], maThanhVien, SoSanhChuoi);
    if (ketQua != NULL) {
        ThanhVien *thanhVien = (ThanhVien *)ketQua->DuLieu;
        return thanhVien;
    } else {
        return NULL;
    }
}

// Xóa thành viên
void XoaThanhVien() {
    char maThanhVien[13];
    printf("Nhap Can cuoc cong dan: ");
    scanf("%s", maThanhVien);
    unsigned int chiSo = BamChuoi(maThanhVien);
    AVLNode *ketQua = TimKiemCayAvl(BangBamThanhVien[chiSo], maThanhVien, SoSanhChuoi);
    if (ketQua != NULL) {
        ThanhVien *thanhVien = (ThanhVien *)ketQua->DuLieu;
        if (thanhVien->SoLuongDangMuon > 0) {
            printf("Khong the xoa thanh vien, vi con sach muon\n");
        }
        else {
            BangBamThanhVien[chiSo] = XoaKhoiCayAvl(BangBamThanhVien[chiSo], thanhVien->MaThanhVien, SoSanhChuoi);
            printf("Da xoa thanh vien\n");
        }
    } else {
        printf("Khong tim thay thanh vien\n");
    }
}

// Hàm duyệt cây AVL ghi ra file CSV
typedef struct HangDoiThanhVien {
    AVLNode* Nut;
    struct HangDoiThanhVien *TiepTheo;
} HangDoiThanhVien;

HangDoiThanhVien* TaoNutHangDoiThanhVien(AVLNode *nut){
    HangDoiThanhVien* nutMoi = (HangDoiThanhVien*)malloc(sizeof(HangDoiThanhVien));
    nutMoi->Nut = nut;
    nutMoi->TiepTheo = NULL;
    return nutMoi;
}

void DuyetGhiThanhVien(FILE *file, AVLNode *nut) {
    if (nut == NULL) return;

    HangDoiThanhVien* dau = TaoNutHangDoiThanhVien(nut);
    HangDoiThanhVien* duoi = dau;

    while (dau != NULL) {
        if (dau->Nut->Trai != NULL) {
            duoi->TiepTheo = TaoNutHangDoiThanhVien(dau->Nut->Trai);
            duoi = duoi->TiepTheo;
        }
        if (dau->Nut->Phai != NULL) {
            duoi->TiepTheo = TaoNutHangDoiThanhVien(dau->Nut->Phai);
            duoi = duoi->TiepTheo;
        }

        ThanhVien* thanhVien = dau->Nut->DuLieu;
        fprintf(file, "%s,%s,%d\n", thanhVien->MaThanhVien, thanhVien->HoTen, thanhVien->SoLuongDangMuon);

        HangDoiThanhVien* tmp = dau;
        dau = dau->TiepTheo;
        free(tmp);
    }
}

void LuuThanhVienVaoFile(const char *tenFile) {
    FILE *file = fopen(tenFile, "w");
    if (file == NULL) {
        printf("Khong the mo file!\n");
        return;
    }

    for (int i = 0; i < KichThuocBang; i++) {
        AVLNode *nut = BangBamThanhVien[i];
        DuyetGhiThanhVien(file, nut);
    }
    fclose(file);
}