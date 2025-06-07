#ifndef HangDoi_H
#define HangDoi_H

#include "Data.h"

// Tạo nút hàng đợi
HangDoi* TaoNutHangDoi(char* MaThanhVien, char* TieuDe, char* TacGia, bool UuTien);
// Thêm nút vào hàng đợi
void ChenNutHangDoi(char *MaThanhVien, char *TieuDe, char *TacGia, bool UuTien);
// Lấy thông tin người đầu tiên
HangDoi* LayNguoiDauTien(Sach *sach);
// Xoá node đầu tiên của cả hai hàng đợi (ưu tiên trước)
void XoaNguoiDauTien(Sach *sach);
// Duyệt in cả hai hàng đợi
void DuyetHangDoi(char* TieuDe, char* TacGia);
// Tìm người trong hàng đợi ưu tiên hoặc thường của một cuốn sách
HangDoi* TimNguoiTrongHangDoi(Sach* sach, char* MaThanhVien);
// Lưu từng nhánh hàng đợi vào file
void LuuHangDoiVaoFileHelper(FILE *f, HangDoi *q);
// Lưu hàng đợi của một sách vào file
void LuuHangDoiSachVaoFile(Sach *sach, void *filePtr);
// Dùng cho hàm LuuTatCaHangDoiVaoFile
void DuyetAvlVoiThamSo(AVLNode *goc, void (*tham)(Sach *, void *), void *thamSo);
// Duyệt toàn bộ sách để lưu hàng đợi
void LuuTatCaHangDoiVaoFile(const char *tenFile);
// Đọc từ file ra
void DocHangDoiTuFile(const char *tenFile);
// Thêm nút vào hàng đợi
void ChenNutHangDoiVaoSach(Sach *sach, HangDoi *nut);

#endif