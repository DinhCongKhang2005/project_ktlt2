#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Library_Service.h"
#include "Book.h"
#include "Member.h"
#include "Borrowing.h"

void MenuSach();
void MenuThanhVien();
void MenuPhieuMuon();

void GiaoDienQuanLy() {
    int luaChon;
    do {
        XoaManHinh();
        printf("=========== CHUONG TRINH QUAN LY THU VIEN CHO QUAN LY ===========\n");
        printf("1. Quan ly sach\n");
        printf("2. Quan ly thanh vien\n");
        printf("3. Quan ly muon/tra sach\n");
        printf("0. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &luaChon);
        getchar();

        switch (luaChon) {
            case 1:
                MenuSach();
                break;
            case 2:
                MenuThanhVien();
                break;
            case 3:
                MenuPhieuMuon();
                break;
            case 0:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le. Vui long thu lai!\n");
        }
    } while (luaChon != 0);
}

/* QUẢN LÝ SÁCH */
void MenuSach() {
    int luaChon;
    char tieuDe[200], tacGia[200];
    Sach sach;

    do {
        XoaManHinh();
        printf("========== QUAN LY SACH ==========\n");
        printf("1. Them sach\n");
        printf("2. Tim sach\n");
        printf("3. Xoa sach\n");
        printf("4. Hien thi toan bo sach\n");
        printf("0. Quay lai\n");
        printf("Lua chon: ");
        scanf("%d", &luaChon);
        getchar();

        switch (luaChon) {
            case 1:
                printf("Nhap tieu de: "); fgets(sach.TieuDe, 200, stdin); sach.TieuDe[strcspn(sach.TieuDe, "\n")] = '\0';
                printf("Nhap tac gia: "); fgets(sach.TacGia, 200, stdin); sach.TacGia[strcspn(sach.TacGia, "\n")] = '\0';
                printf("Nhap so luong: "); scanf("%d", &sach.SoLuong); getchar();
                sach.HangDoiBinhThuong = sach.HangDoiUuTien = NULL;
                ChenSach(sach);
                printf("Da them sach.\n");
                break;
            case 2:
                printf("Nhap tieu de: "); fgets(tieuDe, 200, stdin); tieuDe[strcspn(tieuDe, "\n")] = '\0';
                printf("Nhap tac gia: "); fgets(tacGia, 200, stdin); tacGia[strcspn(tacGia, "\n")] = '\0';
                Sach *timThay = TimSach(tieuDe, tacGia);
                if (timThay) InSach(timThay);
                else printf("Khong tim thay sach.\n");
                break;
            case 3:
                printf("Nhap tieu de: "); fgets(tieuDe, 200, stdin); tieuDe[strcspn(tieuDe, "\n")] = '\0';
                printf("Nhap tac gia: "); fgets(tacGia, 200, stdin); tacGia[strcspn(tacGia, "\n")] = '\0';
                Sach* sachXoa = TimSach(tieuDe, tacGia);
                if (sachXoa == NULL)
                    printf("Sach khong ton tai\n");
                else if (sachXoa->HangDoiBinhThuong != NULL || sachXoa->HangDoiUuTien != NULL)
                    printf("Hang doi van con nguoi, khong the xoa sach\n");
                else{
                    XoaSach(tieuDe, tacGia);
                    printf("Da xoa sach\n");
                }
                break;
            case 4:
                HienThiTatCaSach();
                break;
            case 0:
                return;
            default:
                printf("Lua chon khong hop le.\n");
        }
    } while (luaChon != 0);
}

/* QUẢN LÝ THÀNH VIÊN */
void MenuThanhVien() {
    int luaChon;
    ThanhVien thanhVien;

    do {
        XoaManHinh();
        printf("========== QUAN LY THANH VIEN ==========\n");
        printf("1. Them thanh vien\n");
        printf("2. Tim thanh vien\n");
        printf("3. Xoa thanh vien\n");
        printf("0. Quay lai\n");
        printf("Lua chon: ");
        scanf("%d", &luaChon);
        getchar();

        switch (luaChon) {
            case 1:
                printf("Nhap MSSV: "); // Đã sửa từ CCCD thành MSSV
                fgets(thanhVien.MaThanhVien, 13, stdin); thanhVien.MaThanhVien[strcspn(thanhVien.MaThanhVien, "\n")] = '\0';
                printf("Nhap ten: "); fgets(thanhVien.HoTen, 100, stdin); thanhVien.HoTen[strcspn(thanhVien.HoTen, "\n")] = '\0';
                thanhVien.SoLuongDangMuon = 0;
                ThemThanhVien(&thanhVien);
                printf("Da them thanh vien.\n");
                break;
            case 2:
                printf("Nhap MSSV: "); // Đã sửa từ CCCD thành MSSV
                char id[13];
                fgets(id, 13, stdin); id[strcspn(id, "\n")] = '\0';
                ThanhVien *timThay = TimThanhVien(id);
                if (timThay)
                    printf("Ho ten: %s | So sach dang muon: %d\n", timThay->HoTen, timThay->SoLuongDangMuon);
                else
                    printf("Khong tim thay thanh vien.\n");
                break;
            case 3:
                XoaThanhVien();
                printf("Da xoa thanh vien (neu ton tai).\n");
                break;
            case 0:
                return;
            default:
                printf("Lua chon khong hop le.\n");
        }
    } while (luaChon != 0);
}

/* QUẢN LÝ MƯỢN SÁCH */
void MenuPhieuMuon() {
    int luaChon;
    char maPhieu[7], id[13], tieuDe[200], tacGia[200];
    time_t t = time(NULL);
    struct tm now = *localtime(&t);

    do {
        XoaManHinh();
        printf("========== QUAN LY MUON/TRA SACH ==========\n");
        printf("1. Danh sach muon\n");
        printf("2. Cac sach da duoc tra\n");
        printf("0. Quay lai\n");
        printf("Lua chon: ");
        scanf("%d", &luaChon);
        getchar();

        switch (luaChon) {
            case 1:
                HienThiTatCaPhieuMuon();
                break;
            case 2:
                FILE *f = fopen("data/returned.csv","r");
                if (!f) {
                    printf("Khong the mo file returned.csv de doc!\n");
                    return;
                }
                char dong[500];
                printf("%s | %s | %s | %s | %s | %s\n",
                "MaPhieu", "MSSV", "Tieu de", "Tac gia", "Ngay muon", "Ngay tra");
                while (fgets(dong, sizeof(dong), f)){
                    char *p = dong;
                    while (*p) {
                        if (*p == ';') *p = '|';
                        p++;
                    }
                    printf("%s\n", dong);
                }
                break;
            case 0:
                return;
            default:
                printf("Lua chon khong hop le.\n");
        }
    } while (luaChon != 0);
}
