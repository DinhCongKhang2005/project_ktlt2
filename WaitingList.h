#ifndef WAITINGLIST_H
#define WAITINGLIST_H

#include "Data.h"
#include <stdbool.h>
#include <time.h>

void ThemYeuCauCho(const char *MaSinhVien, const char *MaSach, bool UuTien);
void XoaYeuCauCho(const char *MaSinhVien, const char *MaSach);
DanhSachCho* TimKiemYeuCauCho(const char *MaSinhVien, const char *MaSach);
void HienThiDanhSachCho(const char *MaSach);
DanhSachCho* LayYeuCauChoDauTien(const char *MaSach);
void DocDanhSachCho(const char *TenFile);
void GhiDanhSachCho(const char *TenFile);

#endif