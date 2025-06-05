#include "Menu.h"
#include "Book.h"
#include "Member.h"
#include "Transaction.h"
#include "WaitingList.h"
#include "Utility.h"
#include <stdio.h>
#include <stdlib.h>

int HienThiMenuChinh() {
    printf("\n=========== QUAN LY THU VIEN ===========\n");
    printf("1. Quan ly Sach\n");
    printf("2. Quan ly Ban doc\n");
    printf("3. Quan ly Muon/Tra Sach\n");
    printf("4. Quan ly Danh sach cho\n");
    printf("0. Thoat\n");
    printf("=========================================\n");
    printf("Nhap lua chon: ");
    char buff[10];
    DocDong(buff, sizeof(buff));
    return atoi(buff);
}

void MenuQuanLySach() {
    int chon;
    do {
        printf("\n----- Quan ly Sach -----\n");
        printf("1. Them sach\n");
        printf("2. Xoa sach\n");
        printf("3. Cap nhat thong tin sach\n");
        printf("4. Tim kiem sach\n");
        printf("5. Hien thi danh sach sach\n");
        printf("0. Quay lai\n");
        printf("Nhap lua chon: ");
        char buff[10];
        DocDong(buff, sizeof(buff));
        chon = atoi(buff);
        if (chon == 1) {
            Sach sach;
            printf("Nhap ma sach: "); DocDong(sach.MaSach, sizeof(sach.MaSach));
            printf("Nhap ten sach: "); DocDong(sach.TenSach, sizeof(sach.TenSach));
            printf("Nhap tac gia: "); DocDong(sach.TacGia, sizeof(sach.TacGia));
            printf("Nhap the loai: "); DocDong(sach.TheLoai, sizeof(sach.TheLoai));
            printf("Nhap tong so luong: "); DocDong(buff, sizeof(buff)); sach.TongSoLuong = atoi(buff);
            sach.SoLuongConLai = sach.TongSoLuong;
            ThemSach(sach);
        } else if (chon == 2) {
            char tenSach[101], tacGia[51];
            printf("Nhap ten sach can xoa: "); DocDong(tenSach, sizeof(tenSach));
            printf("Nhap tac gia: "); DocDong(tacGia, sizeof(tacGia));
            XoaSach(tenSach, tacGia);
        } else if (chon == 3) {
            char tenSach[101], tacGia[51];
            Sach sachMoi;
            printf("Nhap ten sach can cap nhat: "); DocDong(tenSach, sizeof(tenSach));
            printf("Nhap tac gia: "); DocDong(tacGia, sizeof(tacGia));
            printf("Nhap ma sach moi: "); DocDong(sachMoi.MaSach, sizeof(sachMoi.MaSach));
            printf("Nhap ten sach moi: "); DocDong(sachMoi.TenSach, sizeof(sachMoi.TenSach));
            printf("Nhap tac gia moi: "); DocDong(sachMoi.TacGia, sizeof(sachMoi.TacGia));
            printf("Nhap the loai moi: "); DocDong(sachMoi.TheLoai, sizeof(sachMoi.TheLoai));
            printf("Nhap tong so luong moi: "); DocDong(buff, sizeof(buff)); sachMoi.TongSoLuong = atoi(buff);
            sachMoi.SoLuongConLai = sachMoi.TongSoLuong;
            CapNhatSach(tenSach, tacGia, sachMoi);
        } else if (chon == 4) {
            char tenSach[101], tacGia[51];
            printf("Nhap ten sach can tim: "); DocDong(tenSach, sizeof(tenSach));
            printf("Nhap tac gia: "); DocDong(tacGia, sizeof(tacGia));
            Sach *sach = TimKiemSach(tenSach, tacGia);
            if (sach) HienThiThongTinSach(sach);
            else printf("Khong tim thay sach!\n");
        } else if (chon == 5) {
            HienThiDanhSachSach();
        }
    } while (chon != 0);
}

void MenuQuanLyBanDoc() {
    int chon;
    do {
        printf("\n----- Quan ly Ban doc -----\n");
        printf("1. Them ban doc\n");
        printf("2. Xoa ban doc\n");
        printf("3. Cap nhat thong tin ban doc\n");
        printf("4. Tim kiem ban doc\n");
        printf("5. Hien thi danh sach ban doc\n");
        printf("0. Quay lai\n");
        printf("Nhap lua chon: ");
        char buff[10];
        DocDong(buff, sizeof(buff));
        chon = atoi(buff);
        if (chon == 1) {
            BanDoc banDoc;
            printf("Nhap ma sinh vien: "); DocDong(banDoc.MaSinhVien, sizeof(banDoc.MaSinhVien));
            printf("Nhap ten ban doc: "); DocDong(banDoc.TenBanDoc, sizeof(banDoc.TenBanDoc));
            banDoc.SoSachDangMuon = 0;
            ThemBanDoc(&banDoc);
        } else if (chon == 2) {
            char maSV[13];
            printf("Nhap ma sinh vien can xoa: "); DocDong(maSV, sizeof(maSV));
            XoaBanDoc(maSV);
        } else if (chon == 3) {
            char maSV[13];
            BanDoc bdMoi;
            printf("Nhap ma sinh vien can cap nhat: "); DocDong(maSV, sizeof(maSV));
            printf("Nhap ten ban doc moi: "); DocDong(bdMoi.TenBanDoc, sizeof(bdMoi.TenBanDoc));
            bdMoi.SoSachDangMuon = 0;
            strncpy(bdMoi.MaSinhVien, maSV, sizeof(bdMoi.MaSinhVien));
            CapNhatBanDoc(maSV, bdMoi);
        } else if (chon == 4) {
            char maSV[13];
            printf("Nhap ma sinh vien can tim: "); DocDong(maSV, sizeof(maSV));
            BanDoc *bd = TimKiemBanDoc(maSV);
            if (bd) HienThiThongTinBanDoc(bd);
            else printf("Khong tim thay ban doc!\n");
        } else if (chon == 5) {
            HienThiDanhSachBanDoc();
        }
    } while (chon != 0);
}

void MenuQuanLyMuonTra() {
    int chon;
    do {
        printf("\n----- Quan ly Muon/Tra Sach -----\n");
        printf("1. Lap phieu muon sach\n");
        printf("2. Ghi nhan tra sach\n");
        printf("3. Hien thi tat ca giao dich\n");
        printf("0. Quay lai\n");
        printf("Nhap lua chon: ");
        char buff[10];
        DocDong(buff, sizeof(buff));
        chon = atoi(buff);
        if (chon == 1) {
            char maSV[13], maSach[21];
            struct tm ngayMuon = {0}, ngayHenTra = {0};
            printf("Nhap ma sinh vien: "); DocDong(maSV, sizeof(maSV));
            printf("Nhap ma sach: "); DocDong(maSach, sizeof(maSach));
            printf("Nhap ngay muon (dd mm yyyy): ");
            scanf("%d %d %d", &ngayMuon.tm_mday, &ngayMuon.tm_mon, &ngayMuon.tm_year);
            ngayMuon.tm_mon -= 1; ngayMuon.tm_year -= 1900;
            printf("Nhap ngay hen tra (dd mm yyyy): ");
            scanf("%d %d %d", &ngayHenTra.tm_mday, &ngayHenTra.tm_mon, &ngayHenTra.tm_year);
            ngayHenTra.tm_mon -= 1; ngayHenTra.tm_year -= 1900;
            while(getchar() != '\n');
            TaoPhieuMuon(maSV, maSach, ngayMuon, ngayHenTra);
        } else if (chon == 2) {
            char maPhieu[21];
            struct tm ngayTra = {0};
            printf("Nhap ma phieu muon: "); DocDong(maPhieu, sizeof(maPhieu));
            printf("Nhap ngay tra (dd mm yyyy): ");
            scanf("%d %d %d", &ngayTra.tm_mday, &ngayTra.tm_mon, &ngayTra.tm_year);
            ngayTra.tm_mon -= 1; ngayTra.tm_year -= 1900;
            while(getchar() != '\n');
            GhiNhanTraSach(maPhieu, ngayTra);
        } else if (chon == 3) {
            HienThiDanhSachGiaoDich();
        }
    } while (chon != 0);
}

void MenuDanhSachCho() {
    int chon;
    do {
        printf("\n----- Quan ly Danh sach cho -----\n");
        printf("1. Them yeu cau cho\n");
        printf("2. Xoa yeu cau cho\n");
        printf("3. Hien thi danh sach cho cua sach\n");
        printf("0. Quay lai\n");
        printf("Nhap lua chon: ");
        char buff[10];
        DocDong(buff, sizeof(buff));
        chon = atoi(buff);
        if (chon == 1) {
            char maSV[13], maSach[21];
            printf("Nhap ma sinh vien: "); DocDong(maSV, sizeof(maSV));
            printf("Nhap ma sach: "); DocDong(maSach, sizeof(maSach));
            printf("Co uu tien khong (1-Co, 0-Khong): ");
            DocDong(buff, sizeof(buff));
            ThemYeuCauCho(maSV, maSach, atoi(buff) ? true : false);
        } else if (chon == 2) {
            char maSV[13], maSach[21];
            printf("Nhap ma sinh vien: "); DocDong(maSV, sizeof(maSV));
            printf("Nhap ma sach: "); DocDong(maSach, sizeof(maSach));
            XoaYeuCauCho(maSV, maSach);
        } else if (chon == 3) {
            char maSach[21];
            printf("Nhap ma sach: "); DocDong(maSach, sizeof(maSach));
            HienThiDanhSachCho(maSach);
        }
    } while (chon != 0);
}

void ChayMenuChinh() {
    int chon;
    do {
        chon = HienThiMenuChinh();
        switch (chon) {
            case 1:
                MenuQuanLySach();
                break;
            case 2:
                MenuQuanLyBanDoc();
                break;
            case 3:
                MenuQuanLyMuonTra();
                break;
            case 4:
                MenuDanhSachCho();
                break;
            case 0:
                printf("Tam biet!\n");
                break;
            default:
                printf("Lua chon khong hop le, vui long thu lai!\n");
        }
    } while (chon != 0);
}