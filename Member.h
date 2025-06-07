#ifndef ThanhVien_H
#define ThanhVien_H
#include "Data.h"
extern AVLNode *BangBamThanhVien[KichThuocBang];
// Thêm thành viên
void ThemThanhVien(ThanhVien *thanhVienMoi);
// Đọc từ file csv
void DocThanhVienTuFile(const char *tenFile);
// Tìm kiếm thành viên
ThanhVien* TimThanhVien(char *maThanhVien);
// Xóa thành viên
void XoaThanhVien();
// Ghi vào file CSV 
void LuuThanhVienVaoFile(const char *tenFile);
// Hàm duyệt cây AVL 
void DuyetGhiThanhVien(FILE *file, AVLNode *nut);

#endif