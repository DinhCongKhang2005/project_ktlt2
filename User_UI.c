#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Member.h"
#include "Book.h"
#include "Borrowing.h"
#include "Queue.h"
#include "Library_Service.h"

/* KHAI BÁO HÀM */
void TraCuuSach(char* tieuDe, char* tacGia);
void MuonSach(char* maThanhVien, char* tieuDe, char* tacGia);
void TraCuuHangDoi(char* tieuDe, char* tacGia);
void DangKyHangDoi(char* maThanhVien, char* tieuDe, char* tacGia);
void DangKyThanhVien(char* maThanhVien);
void TraSach(char* maPhieu);

/* HÀM GIAO DIỆN NGƯỜI DÙNG */
void GiaoDienNguoiDung() {
    int luaChon;
    char maThanhVien[13], tieuDe[200], tacGia[200], maPhieu[7];
    time_t t = time(NULL);
    struct tm now = *localtime(&t);

    do {
        XoaManHinh();
        printf("========== NGUOI DUNG ==========\n");
        printf("1. Xem toan bo sach\n");
        printf("2. Tra cuu sach\n");
        printf("3. Dang ky muon sach\n");
        printf("4. Dang ky vao hang doi\n");
        printf("5. Tra cuu trang thai muon\n");
        printf("6. Xem hang doi muon sach\n");
        printf("7. Dang ky thanh vien\n");
        printf("8. Tra sach\n");
        printf("0. Quay lai\n");
        printf("Lua chon: ");
        scanf("%d", &luaChon);
        getchar();

        switch (luaChon) {
            case 1:
                HienThiTatCaSach();
                system("PAUSE");
                break;
            case 2: 
                TraCuuSach(tieuDe, tacGia);
                break;
            case 3:
                MuonSach(maThanhVien, tieuDe, tacGia);
                break;
            case 4:
                DangKyHangDoi(maThanhVien, tieuDe, tacGia);
                break;
            case 5:
                printf("Nhap ma phieu muon: ");
                fgets(maPhieu, 7, stdin); maPhieu[strcspn(maPhieu, "\n")] = '\0';
                AVLNode *nut = TimPhieuMuon(maPhieu);
                if (nut) {
                    PhieuMuon *phieu = (PhieuMuon *)nut->DuLieu;
                    printf("MSSV: %s | Sach: %s - %s | Ngay muon: %02d/%02d/%04d\n", 
                           phieu->MaThanhVien, phieu->TieuDe, phieu->TacGia,
                           phieu->ThoiGianMuon.tm_mday, phieu->ThoiGianMuon.tm_mon + 1, phieu->ThoiGianMuon.tm_year + 1900);
                } else {
                    printf("Khong tim thay phieu.\n");
                }
                system("PAUSE");
                break;
            case 6:
                TraCuuHangDoi(tieuDe, tacGia);
                break;
            case 7:
                DangKyThanhVien(maThanhVien);
                break;
            case 8:
                TraSach(maPhieu);
                break;
            case 0:
                return;
            default:
                printf("Lua chon khong hop le.\n");
        }
    } while (luaChon != 0);
}

/* TRA CỨU SÁCH */
void TraCuuSach(char* tieuDe, char* tacGia){
    char c = '\0';
    do{
        if (c != '\0')
            getchar();
        XoaManHinh();
        printf("========== TRA CUU SACH ==========\n");
        printf("Nhap tieu de sach: "); fgets(tieuDe, 200, stdin); tieuDe[strcspn(tieuDe, "\n")] = '\0';
        printf("Nhap ten tac gia: "); fgets(tacGia, 200, stdin); tacGia[strcspn(tacGia, "\n")] = '\0';
        Sach* sach = TimSach(tieuDe, tacGia);
        if (sach == NULL){
            printf("Khong tim thay sach\n");
        }
        else{
            printf("Da tim thay sach:\n");
            InSach(sach);
        }
        printf("Ban co muon tiep tuc Tra Cuu Sach ?\n(Nhap Y/y de tiep tuc, ky tu bat ky de thoat): ");
        scanf("%c",&c);
    }while(c == 'Y' || c == 'y');
}

/* ĐĂNG KÝ MƯỢN SÁCH */
void MuonSach(char* maThanhVien, char* tieuDe, char* tacGia) {
    XoaManHinh();
    printf("========== DANG KY MUON SACH ==========\n");
    printf("Nhap MSSV: "); fgets(maThanhVien, 13, stdin); maThanhVien[strcspn(maThanhVien, "\n")] = '\0';
    getchar();
    ThanhVien* thanhVien = TimThanhVien(maThanhVien);

    // Kiểm tra thành viên có tồn tại hay không 
    if (thanhVien == NULL){
        printf("Ban chua dang ky thanh vien, vui long dang ky thanh vien de co the muon sach\n");

        return;
    }
    // Kiểm tra số lượng sách đang mượn 
    if (thanhVien->SoLuongDangMuon == 10)
    {
        printf("So luong sach ban muon da toi muc cho phep (10 cuon)\nVui long tra sach de co the muon them\n");
        
        return;
    }
    
    printf("Nhap tieu de sach: "); fgets(tieuDe, 200, stdin); tieuDe[strcspn(tieuDe, "\n")] = '\0';
    printf("Nhap ten tac gia: "); fgets(tacGia, 200, stdin); tacGia[strcspn(tacGia, "\n")] = '\0';
    Sach* sach = TimSach(tieuDe, tacGia);

    // Kiểm tra sach có tồn tại hay không
    if (sach == NULL){
        printf("Sach ban dang tim khong ton tai, vui long tra cuu ky truoc khi muon\n");
    
        return;
    }
    // Kiểm tra số lượng sách còn lại
    if (sach->SoLuong == 0){
        printf("Hien thu vien da het dau sach nay\nNeu ban muon dang ky hang doi, vui long chọn 'Dang ky vao hang doi' o giao dien");
    
        return;
    }
    
    struct tm now;
    printf("Nhap ngay, thang, nam dang ky muon sach:\n(Yeu cau nhap dung theo cau truc ngay/thang/nam)\n");
    scanf("%d/%d/%d", &now.tm_mday, &now.tm_mon, &now.tm_year);
    now.tm_mon = now.tm_mon -1;
    now.tm_year = now.tm_year - 1900;
    TaoPhieuMuon(maThanhVien, tieuDe, tacGia, now);
    printf("Ban da muon sach thanh cong!!\n");
    printf("Ma muon sach cua ban la: %s\n", MaPhieuMuonHienTai);

    return;
}

/* TRA CỨU HÀNG ĐỢI */
void TraCuuHangDoi(char* tieuDe, char* tacGia){
    char c = '\0';
    do{
        if (c != '\0')
            getchar();
        XoaManHinh();
        printf("========== TRA CUU HANG DOI ==========\n");
        printf("Nhap tieu de sach: "); fgets(tieuDe, 200, stdin); tieuDe[strcspn(tieuDe, "\n")] = '\0';
        printf("Nhap ten tac gia: "); fgets(tacGia, 200, stdin); tacGia[strcspn(tacGia, "\n")] = '\0';
        Sach* sach = TimSach(tieuDe, tacGia);
        if (sach == NULL){
            printf("Khong tim thay sach\n");
        }
        else{
            printf("Da tim thay sach:\n");
            InSach(sach);
            // Có thể bổ sung hàm duyệt hàng đợi ở đây nếu cần
        }
        printf("Ban co muon tiep tuc Tra Cuu Hang Doi?\n(Nhap Y/y de tiep tuc, ky tu bat ky de thoat): ");
        scanf("%c",&c);
    }while(c == 'Y' || c == 'y');
}

/* ĐĂNG KÝ VAO HÀNG ĐỢI */
void DangKyHangDoi(char* maThanhVien, char* tieuDe, char* tacGia){
    XoaManHinh();
    printf("========== DANG KY HANG DOI ==========\n");
    printf("Nhap MSSV: "); fgets(maThanhVien, 13, stdin); maThanhVien[strcspn(maThanhVien, "\n")] = '\0';
    getchar();
    ThanhVien* thanhVien = TimThanhVien(maThanhVien);

    // Kiểm tra thành viên có tồn tại hay không 
    if (thanhVien == NULL){
        printf("Ban chua dang ky thanh vien, vui long dang ky thanh vien de co the muon sach\n");
    
        return;
    }

    printf("Nhap tieu de sach: "); fgets(tieuDe, 200, stdin); tieuDe[strcspn(tieuDe, "\n")] = '\0';
    printf("Nhap ten tac gia: "); fgets(tacGia, 200, stdin); tacGia[strcspn(tacGia, "\n")] = '\0';
    
    Sach* sach = TimSach(tieuDe, tacGia);
    if (sach == NULL){
        printf("Khong tim thay sach. Vui long tra cuu ky lai dau sach truoc ky dang ky\n");
      
        return;
    }
    if (sach->SoLuong > 0){
        printf("Sach van con, vui long chuyen qua dich vu muon sach\n");
      
        return;
    }
    printf("Ban co muon vao hang doi uu tien khong?\n");
    printf("(Nhap Y/y de xac nhan, ky tu bat ky de khong xac nhan)\n");
    char c;
    scanf("%c", &c);
    bool uuTien = (c == 'Y' || c == 'y');
    ChenNutHangDoi(maThanhVien, tieuDe, tacGia, uuTien);
    printf("Ban da duoc them vao hang doi thanh cong\n");
 
    return;
}

/* ĐĂNG KÝ THÀNH VIÊN */
void DangKyThanhVien(char* maThanhVien){
    XoaManHinh();
    printf("========== DANG KY THANH VIEN ==========\n");
    printf("Nhap MSSV: "); fgets(maThanhVien, 13, stdin); maThanhVien[strcspn(maThanhVien, "\n")] = '\0';
    getchar();
    ThanhVien* thanhVien = TimThanhVien(maThanhVien);

    // Kiểm tra thành viên có tồn tại hay không 
    if (thanhVien != NULL){
        printf("Ban da dang ky thanh vien, vui long chon dich vu khac\n");
       
        return;
    }
    ThanhVien tvMoi;
    strcpy(tvMoi.MaThanhVien, maThanhVien);
    printf("Nhap Ho va Ten: ");
    fgets(tvMoi.HoTen, 99, stdin); tvMoi.HoTen[strcspn(tvMoi.HoTen, "\n")] = '\0';
    tvMoi.SoLuongDangMuon = 0;
    ThemThanhVien(&tvMoi);
    printf("Da them thanh vien thanh cong\n");
    
    return;
}

/* TRẢ SÁCH */
void TraSach(char* maPhieu){
    XoaManHinh();
    printf("========== TRA SACH ==========\n");
    printf("Nhap ma phieu muon: ");
    fgets(maPhieu, 7, stdin); maPhieu[strcspn(maPhieu, "\n")] = '\0';
    XoaPhieuMuon(maPhieu);
    
}