#ifndef UTILITY_H
#define UTILITY_H

#include <stdbool.h>

void ChuyenChuThuong(char *chuoi);
void ChuanHoaChuoi(char *chuoi);
bool KiemTraSoNguyenDuong(const char *chuoi);
int SoSanhChuoi(const void *a, const void *b);
void DocDong(char *buff, int buffSize);

#endif