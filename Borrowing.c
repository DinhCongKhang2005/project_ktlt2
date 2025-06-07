#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include "Borrowing.h"
#include "AVL_Tree.h"
#include "hash.h"
#include "Book.h"
#include "Member.h"
#include "Data.h"

AVLNode *BangBamPhieuMuon[KichThuocBang] = {NULL}; // Định nghĩa duy nhất ở đây

// Biến toàn cục để lưu mã phiếu mượn hiện tại với giá trị mặc định
char MaPhieuMuonHienTai[6] = "000000";

// Hàm thêm phiếu mượn vào bảng băm bằng cách tạo nút và chèn vào AVL
void ThemPhieuMuon(PhieuMuon *phieuMoi) {
    char *khoa = phieuMoi->MaPhieu; // Lấy MaPhieu làm khóa
    unsigned int chiSo = BamChuoi(khoa);
    BangBamPhieuMuon[chiSo] = ChenVaoCayAvl(BangBamPhieuMuon[chiSo], phieuMoi, khoa, SoSanhChuoi);
}

// Đọc từ file csv và thêm vào bảng băm
void DocPhieuMuonTuFile(const char *tenFile) {
    FILE *file = fopen(tenFile, "r");
    if (file == NULL) {
        printf("Khong the mo file! %s\n", tenFile);
        return;
    }
    char dong[256];
    // Đọc dòng đầu tiên để lấy mã hiện tại
    if (fgets(dong, sizeof(dong), file)) 
        sscanf(dong, "%6s", MaPhieuMuonHienTai);

    // Đọc các dòng dữ liệu của phiếu mượn
    while (fgets(dong, sizeof(dong), file)) {
        if (strcmp(dong, "\n") == 0)
            continue;
        dong[strcspn(dong, "\n")] = '\0';
        PhieuMuon *phieuMoi = (PhieuMuon*)malloc(sizeof(PhieuMuon));
        if (phieuMoi == NULL) {
            printf("Khong du bo nho de cap phat!\n");
            fclose(file);
            return;
        }
        // Đọc các trường
        sscanf(dong, "%[^,];%[^,];%[^,];%[^,];%d/%d/%d",
            phieuMoi->MaPhieu, phieuMoi->MaThanhVien,
            phieuMoi->TieuDe, phieuMoi->TacGia,
            &phieuMoi->ThoiGianMuon.tm_mday,
            &phieuMoi->ThoiGianMuon.tm_mon,
            &phieuMoi->ThoiGianMuon.tm_year);
        phieuMoi->ThoiGianMuon.tm_mon -= 1;
        phieuMoi->ThoiGianMuon.tm_year -= 1900;
        ThemPhieuMuon(phieuMoi);
    }
    fclose(file);
}

// Hàm tạo mã phiếu mượn mới
void SinhMaPhieuMuon(char* ma) {
    int num;
    sscanf(MaPhieuMuonHienTai, "%d", &num);
    num++;
    sprintf(MaPhieuMuonHienTai, "%06d", num);
    strcpy(ma, MaPhieuMuonHienTai);
}

// Tạo nút phiếu mượn mới 
PhieuMuon* TaoPhieuMuonMoi(char* MaThanhVien, char* TieuDe, char* TacGia, struct tm ThoiGianMuon) {
    PhieuMuon *phieuMoi = (PhieuMuon*)malloc(sizeof(PhieuMuon));
    if (phieuMoi == NULL) {
        printf("Khong du bo nho de cap phat!\n");
        return NULL;
    }
    strcpy(phieuMoi->MaThanhVien, MaThanhVien);
    strcpy(phieuMoi->TieuDe, TieuDe);
    strcpy(phieuMoi->TacGia, TacGia);
    SinhMaPhieuMuon(phieuMoi->MaPhieu); // Tạo mã mới
    phieuMoi->ThoiGianMuon = ThoiGianMuon;
    return phieuMoi;
}

// Tạo phiếu mượn
void TaoPhieuMuon(char* MaThanhVien, char* TieuDe, char* TacGia, struct tm ThoiGianMuon) {
    ThanhVien *thanhVien = TimThanhVien(MaThanhVien);
    Sach *sach = TimSach(TieuDe, TacGia);

    if (!thanhVien || !sach) {
        printf("Khong tim thay thanh vien hoac sach!\n");
        return;
    }

    PhieuMuon *phieuMoi = TaoPhieuMuonMoi(MaThanhVien, TieuDe, TacGia, ThoiGianMuon);
    ThemPhieuMuon(phieuMoi);

    // Trừ số lượng sách trong thư viện
    sach->SoLuong--;

    // Tăng số lượng sách mượn của bạn đọc
    thanhVien->SoLuongDangMuon++;
}

// Tìm phiếu mượn theo mã
AVLNode* TimPhieuMuon(char* ma) {
    unsigned int chiSo = BamChuoi(ma);
    return TimKiemCayAvl(BangBamPhieuMuon[chiSo], ma, SoSanhChuoi);
}

// Kiểm tra phiếu mượn có quá hạn không (hạn mượn 3 tháng)
bool KiemTraQuaHan(AVLNode* nut) {
    if (nut == NULL) return false;
    PhieuMuon* phieu = (PhieuMuon*)nut->DuLieu;
    time_t hienTai = time(NULL);
    double giay = difftime(hienTai, mktime(&phieu->ThoiGianMuon));
    double thang = giay / (30 * 24 * 60 * 60); // Ước lượng 1 tháng = 30 ngày
    return (thang > 3);
}

// Ghi vào file tra.csv
void GhiPhieuTra(const char *tenFile, PhieuMuon* phieu) {
    time_t hienTai = time(NULL);
    struct tm ngayTra = *localtime(&hienTai);
    FILE* file = fopen(tenFile, "a");
    if (file) {
        fprintf(file, "%s;%s;%s;%s;%d/%d/%d;%d/%d/%d\n",
            phieu->MaPhieu, phieu->MaThanhVien, phieu->TieuDe, phieu->TacGia,
            phieu->ThoiGianMuon.tm_mday, phieu->ThoiGianMuon.tm_mon + 1, phieu->ThoiGianMuon.tm_year + 1900,
            ngayTra.tm_mday, ngayTra.tm_mon + 1, ngayTra.tm_year + 1900);
        fclose(file);
    } else {
        printf("Loi khong mo duoc file %s\n", tenFile);
    }
}

// Xóa phiếu mượn và thêm vào file da_tra.csv
void XoaPhieuMuon(char* ma) {
    unsigned int chiSo = BamChuoi(ma);
    AVLNode* nut = TimPhieuMuon(ma);
    if (nut == NULL) {
        printf("Khong tim thay phieu muon!\n");
        return;
    }

    PhieuMuon* phieu = (PhieuMuon*)nut->DuLieu;
    bool quaHan = KiemTraQuaHan(nut);
    if (quaHan) {
        printf("Muon qua han, xin hay nop tien phat\n");
        system("PAUSE");
    }
    // Ghi vào file da_tra.csv
    GhiPhieuTra("data/da_tra.csv", phieu);

    // Cập nhật số lượng sách trong thư viện
    Sach* sach = TimSach(phieu->TieuDe, phieu->TacGia);
    if (sach) sach->SoLuong++;

    // Cập nhật số lượng sách đang mượn của bạn đọc
    ThanhVien* thanhVien = TimThanhVien(phieu->MaThanhVien);
    if (thanhVien) thanhVien->SoLuongDangMuon--;

    // Xóa khỏi cây AVL
    BangBamPhieuMuon[chiSo] = XoaKhoiCayAvl(BangBamPhieuMuon[chiSo], ma, SoSanhChuoi);
    printf("Tra sach thanh cong\n");
}

// In thông tin phiếu mượn
void InPhieuMuon(PhieuMuon* phieu) {
    printf("%-7s | %-13s | %-40s | %-40s | %02d/%02d/%d\n",
        phieu->MaPhieu, phieu->MaThanhVien, phieu->TieuDe, phieu->TacGia,
        phieu->ThoiGianMuon.tm_mday, phieu->ThoiGianMuon.tm_mon + 1, phieu->ThoiGianMuon.tm_year + 1900);
}


// Duyệt cây AVL để thực hiện một hành động với từng phiếu mượn
void DuyetAvlPhieuMuon(AVLNode *goc, void (*tham)(PhieuMuon *)) {
    if (!goc) return;
    DuyetAvlPhieuMuon(goc->Trai, tham);
    tham((PhieuMuon *)goc->DuLieu);
    DuyetAvlPhieuMuon(goc->Phai, tham);
}
// Hàm hiển thị tất cả phiếu mượn 
void HienThiTatCaPhieuMuon() {
    printf("%-7s | %-13s | %-40s | %-40s | %-13s\n", "Code", "MSSV", "Tieu de", "Tac gia", "Ngay muon");
    printf("----------------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < KichThuocBang; ++i) {
        DuyetAvlPhieuMuon(BangBamPhieuMuon[i],  InPhieuMuon);
    }
}
// Duyệt và ghi dữ liệu bảng băm vào file borrowing.csv theo chiều rộng 
typedef struct HangDoiPhieuMuon {
    AVLNode* Nut;
    struct HangDoiPhieuMuon *TiepTheo;
} HangDoiPhieuMuon;

HangDoiPhieuMuon* TaoNutHangDoiPhieuMuon(AVLNode *nut) {
    HangDoiPhieuMuon* nutMoi = (HangDoiPhieuMuon*)malloc(sizeof(HangDoiPhieuMuon));
    nutMoi->Nut = nut;
    nutMoi->TiepTheo = NULL;
    return nutMoi;
}
// Ghi dữ liệu theo chiều rộng 
void DuyetGhiPhieuMuon(FILE *file, AVLNode *nut) {
    if (nut == NULL) return;

    HangDoiPhieuMuon* dau = TaoNutHangDoiPhieuMuon(nut);
    HangDoiPhieuMuon* duoi = dau;

    while (dau != NULL) {
        if (dau->Nut->Trai != NULL) {
            duoi->TiepTheo = TaoNutHangDoiPhieuMuon(dau->Nut->Trai);
            duoi = duoi->TiepTheo;
        }
        if (dau->Nut->Phai != NULL) {
            duoi->TiepTheo = TaoNutHangDoiPhieuMuon(dau->Nut->Phai);
            duoi = duoi->TiepTheo;
        }

        PhieuMuon* phieu = dau->Nut->DuLieu;
        fprintf(file, "%s;%s;%s;%s;%d/%d/%d\n",
            phieu->MaPhieu, phieu->MaThanhVien, phieu->TieuDe, phieu->TacGia,
            phieu->ThoiGianMuon.tm_mday, phieu->ThoiGianMuon.tm_mon + 1, phieu->ThoiGianMuon.tm_year + 1900);

        HangDoiPhieuMuon* tmp = dau;
        dau = dau->TiepTheo;
        free(tmp);
    }
}

// Ghi toàn bộ dữ liệu bảng băm phiếu mượn vào file phieumuon.csv
void LuuPhieuMuonVaoFile(const char *tenFile) {
    FILE *file = fopen(tenFile, "w");
    if (file == NULL) {
        printf("Khong the mo file %s de ghi!\n", tenFile);
        return;
    }
    // Ghi mã phiếu mượn hiện tại ở dòng đầu
    fprintf(file, "%s\n", MaPhieuMuonHienTai);
    for (int i = 0; i < KichThuocBang; i++) {
        DuyetGhiPhieuMuon(file, BangBamPhieuMuon[i]);
    }
    fclose(file);
}
