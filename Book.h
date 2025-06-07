#ifndef SACH_H
#define SACH_H

#include "Data.h"
#include "hash.h"
extern AVLNode *BangBamSach[KichThuocBang]; // <-- chỉ khai báo extern

// Chuẩn hóa chuỗi
void ChuyenChuoiVeThuong(char *chuoi);
void ChuanHoaChuoi(char *chuoi);

// Sinh key từ tiêu đề và tác giả
void SinhKhoa(char *khoa, const char *tieuDe, const char *tacGia);

// So sánh key dạng chuỗi
int SoSanhChuoi(void *a, void *b);

// Đọc dữ liệu sách từ file
void DocSachTuFile(const char *tenFile);

// Chèn thủ công
void ChenSach(Sach sach);

// Tìm kiếm sách
Sach* TimSach(const char* tieuDe, const char* tacGia);

// Xóa sách
void XoaSach(const char* tieuDe, const char* tacGia);

// Hiển thị toàn bộ thông tin sách trong thư viện
void HienThiTatCaSach();

// Lưu vào file
void LuuSachVaoFile(const char *tenFile);

// Duyệt AVL để hiển thị sách
void DuyetAvlSach(AVLNode *goc, void (*tham)(Sach *));
void InSach(Sach *sach);

#endif
