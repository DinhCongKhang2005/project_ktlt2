#include <stdio.h>
#include <stdlib.h>
#include "Library_Service.h"

void XoaManHinh() {
    printf("\033[H\033[J");
}

void GiaoDienThuVien() {
    int luaChon;
    do {
        XoaManHinh();
        printf("=========== CHUONG TRINH QUAN LY THU VIEN ===========\n");
        printf("1. Dang nhap voi vai tro NGUOI DUNG\n");
        printf("2. Dang nhap voi vai tro QUAN LY\n");
        printf("0. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &luaChon);
        getchar(); // Clear newline

        switch (luaChon) {
            case 1:
                GiaoDienNguoiDung();
                break;
            case 2:
                GiaoDienQuanLy();
                break;
            case 0:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le. Vui long thu lai!\n");
                system("pause");
        }
    } while (luaChon != 0);
}
