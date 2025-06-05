#ifndef MEMBER_H
#define MEMBER_H

#include "Data.h"

void ThemBanDoc(BanDoc *banDoc);
void XoaBanDoc(const char *MaSinhVien);
void CapNhatBanDoc(const char *MaSinhVien, BanDoc banDocMoi);
BanDoc* TimKiemBanDoc(const char *MaSinhVien);
void HienThiThongTinBanDoc(const BanDoc *banDoc);
void HienThiDanhSachBanDoc();
void DocDuLieuBanDoc(const char *TenFile);
void GhiDuLieuBanDoc(const char *TenFile);

#endif