#ifndef BOOK_H
#define BOOK_H

#include "Data.h"

void ThemSach(Sach sach);
void XoaSach(const char *TenSach, const char *TacGia);
void CapNhatSach(const char *TenSach, const char *TacGia, Sach sachMoi);
Sach* TimKiemSach(const char *TenSach, const char *TacGia);
Sach* TimKiemSachBangMa(const char *MaSach);
void HienThiThongTinSach(const Sach *sach);
void HienThiDanhSachSach();
void DocDuLieuSach(const char *TenFile);
void GhiDuLieuSach(const char *TenFile);

#endif