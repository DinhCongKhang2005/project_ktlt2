#ifndef PhieuMuon_H
#define PhieuMuon_H

#include <time.h>
#include <stdbool.h>
#include "Data.h"
#include "AVL_Tree.h"

// Biến toàn cục
extern char MaPhieuMuonHienTai[6];

// Hàm thêm phiếu mượn vào bảng băm
void ThemPhieuMuon(PhieuMuon *phieuMoi);

// Đọc từ file csv và thêm vào bảng băm
void DocPhieuMuonTuFile(const char *tenFile);

// Tạo mã phiếu mượn
void SinhMaPhieuMuon(char* ma);

// Tạo nút phiếu mượn mới 
PhieuMuon* TaoPhieuMuonMoi(char* MaBanDoc, char* TieuDe, char* TacGia, struct tm ThoiGianMuon);

// Tạo phiếu mượn
void TaoPhieuMuon(char* MaBanDoc, char* TieuDe, char* TacGia, struct tm ThoiGianMuon);

// Tìm phiếu mượn theo mã
AVLNode* TimPhieuMuon(char* ma);

// Kiểm tra phiếu mượn có quá hạn không (hạn mượn 3 tháng)
bool KiemTraQuaHan(struct AVLNode* nut);

// Ghi vào file tra.csv
void GhiPhieuTra(const char *tenFile, PhieuMuon* phieu);

// Xóa phiếu mượn và thêm vào file da_tra.csv
void XoaPhieuMuon(char* ma);

// Duyệt và ghi dữ liệu bảng băm vào file phieumuon.csv
void DuyetGhiPhieuMuon(FILE *file, AVLNode *nut);

// Ghi dữ liệu bảng băm vào file phieumuon.csv
void LuuPhieuMuonVaoFile(const char *tenFile);

// Hàm hiển thị tất cả phiếu mượn 
void HienThiTatCaPhieuMuon();

#endif