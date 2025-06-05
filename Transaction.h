#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "Data.h"
#include <time.h>

void TaoPhieuMuon(const char *MaSinhVien, const char *MaSach, struct tm NgayMuon, struct tm NgayHenTra);
void GhiNhanTraSach(const char *MaPhieuMuon, struct tm NgayTra);
void HienThiThongTinGiaoDich(const GiaoDich *giaoDich);
void HienThiDanhSachGiaoDich();
void DocDuLieuGiaoDich(const char *TenFile);
void GhiDuLieuGiaoDich(const char *TenFile);

#endif