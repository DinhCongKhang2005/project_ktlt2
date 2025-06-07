#include "AVL_Tree.h"

// Hàm lấy chiều cao của nút
int LayChieuCao(AVLNode* nut) {
    if (nut == NULL) {
        return 0;
    }
    return nut->ChieuCao;
}

// Hàm lấy giá trị lớn nhất
int GiaTriLonNhat(int a, int b) {
    return (a > b) ? a : b;
}

// Tạo nút mới cho cây AVL
AVLNode* TaoNut(void *duLieu, void *khoa) {
    AVLNode* nutMoi = (AVLNode*)malloc(sizeof(AVLNode));
    nutMoi->DuLieu = duLieu;
    nutMoi->Khoa = khoa;
    nutMoi->Trai = NULL;
    nutMoi->Phai = NULL;
    nutMoi->ChieuCao = 1; // Mới thêm vào nên chiều cao là 1
    return nutMoi;
}

// Hàm quay phải để cân bằng lại cây AVL
AVLNode* QuayPhai(AVLNode* y) {
    AVLNode* x = y->Trai;
    AVLNode* T2 = x->Phai;

    // Thực hiện quay phải
    x->Phai = y;
    y->Trai = T2;

    // Cập nhật chiều cao của các nút
    y->ChieuCao = 1 + GiaTriLonNhat(LayChieuCao(y->Trai), LayChieuCao(y->Phai));
    x->ChieuCao = 1 + GiaTriLonNhat(LayChieuCao(x->Trai), LayChieuCao(x->Phai));

    // Trả về nút mới làm gốc
    return x;
}

// Hàm quay trái để cân bằng lại cây AVL
AVLNode* QuayTrai(AVLNode* x) {
    AVLNode* y = x->Phai;
    AVLNode* T2 = y->Trai;

    // Thực hiện quay trái
    y->Trai = x;
    x->Phai = T2;

    // Cập nhật chiều cao của các nút
    x->ChieuCao = 1 + GiaTriLonNhat(LayChieuCao(x->Trai), LayChieuCao(x->Phai));
    y->ChieuCao = 1 + GiaTriLonNhat(LayChieuCao(y->Trai), LayChieuCao(y->Phai));

    // Trả về nút mới làm gốc
    return y;
}

// Hàm lấy độ cân bằng của nút
int DoCanBang(AVLNode* nut) {
    if (nut == NULL) {
        return 0;
    }
    return LayChieuCao(nut->Trai) - LayChieuCao(nut->Phai);
}

AVLNode* CanBangCay(AVLNode* nut) {
    // Cập nhật chiều cao của nút
    nut->ChieuCao = 1 + GiaTriLonNhat(LayChieuCao(nut->Trai), LayChieuCao(nut->Phai));

    // Tính toán độ cân bằng của nút
    int canBang = DoCanBang(nut);

    // Nếu nút mất cân bằng, có 4 trường hợp

    // Trường hợp Trái-Trái
    if (canBang > 1 && DoCanBang(nut->Trai) >= 0) {
        return QuayPhai(nut);
    }

    // Trường hợp Phải-Phải
    if (canBang < -1 && DoCanBang(nut->Phai) <= 0) {
        return QuayTrai(nut);
    }

    // Trường hợp Trái-Phải
    if (canBang > 1 && DoCanBang(nut->Trai) < 0) {
        nut->Trai = QuayTrai(nut->Trai);
        return QuayPhai(nut);
    }

    // Trường hợp Phải-Trái
    if (canBang < -1 && DoCanBang(nut->Phai) > 0) {
        nut->Phai = QuayPhai(nut->Phai);
        return QuayTrai(nut);
    }

    return nut; // Trả về con trỏ gốc của cây đã được cân bằng
}

AVLNode* ChenVaoCayAvl(AVLNode* goc, void *duLieu, void *khoa, HamSoSanh soSanh){
    // Kiểm tra xem cây có nút chưa
    if (goc == NULL) 
        return TaoNut(duLieu, khoa); // Tạo nút mới nếu cây rỗng

    // Đưa cây vào đúng vị trí dựa trên giá trị của dữ liệu
    if (soSanh(khoa, goc->Khoa) < 0)
        goc->Trai = ChenVaoCayAvl(goc->Trai, duLieu, khoa, soSanh);
    else if (soSanh(khoa, goc->Khoa) > 0) 
        goc->Phai = ChenVaoCayAvl(goc->Phai, duLieu, khoa, soSanh);
    else // Nếu dữ liệu đã tồn tại trong cây => không làm gì cả
        return goc;
    return CanBangCay(goc); // Cân bằng lại cây sau khi đã thêm nút mới
}

AVLNode* TimKiemCayAvl(AVLNode* goc, void *khoa, HamSoSanh soSanh){
    if (goc == NULL || soSanh(khoa, goc->Khoa) == 0) {
        return goc; // Nếu tìm thấy hoặc cây rỗng
    }

    // Nếu dữ liệu nhỏ hơn nút hiện tại, tìm kiếm trong cây con bên trái
    if (soSanh(khoa, goc->Khoa) < 0) {
        return TimKiemCayAvl(goc->Trai, khoa, soSanh);
    }

    // Nếu dữ liệu lớn hơn nút hiện tại, tìm kiếm trong cây con bên phải
    return TimKiemCayAvl(goc->Phai, khoa, soSanh);
}

AVLNode* NutGiaTriNhoNhat(AVLNode* nut) {
    AVLNode* hienTai = nut;

    // Tìm nút có giá trị nhỏ nhất trong cây con bên trái
    while (hienTai->Trai != NULL) {
        hienTai = hienTai->Trai;
    }
    return hienTai;
}

AVLNode* XoaKhoiCayAvl(AVLNode* goc, void *khoa, HamSoSanh soSanh) {
    // Nếu cây rỗng, trả về NULL
    if (goc == NULL) {
        return goc;
    }

    // Tìm vị trí của nút cần xóa
    if (soSanh(khoa, goc->Khoa) < 0) {
        goc->Trai = XoaKhoiCayAvl(goc->Trai, khoa, soSanh);
    } else if (soSanh(khoa, goc->Khoa) > 0) {
        goc->Phai = XoaKhoiCayAvl(goc->Phai, khoa, soSanh);
    } else {
        // Nút cần xóa được tìm thấy
        if ((goc->Trai == NULL) || (goc->Phai == NULL)) {
            AVLNode* temp = goc->Trai ? goc->Trai : goc->Phai;

            // Nếu không có con nào (nút là lá), gán NULL cho nút hiện tại
            if (temp == NULL) {
                temp = goc;
                goc = NULL;
            } else { // Nếu có một con, gán con đó cho nút hiện tại
                *goc = *temp; // Sao chép nội dung của nút con vào nút hiện tại
            }
            free(temp); // Giải phóng bộ nhớ của nút đã xóa
        } else {
            // Nút có hai con: tìm giá trị nhỏ nhất trong cây con bên phải
            AVLNode* temp = NutGiaTriNhoNhat(goc->Phai);

            // Sao chép giá trị nhỏ nhất vào nút hiện tại
            goc->DuLieu = temp->DuLieu;
            goc->Khoa = temp->Khoa;

            // Xóa nút nhỏ nhất trong cây con bên phải
            goc->Phai = XoaKhoiCayAvl(goc->Phai, temp->Khoa, soSanh);
        }
    }

    // Nếu cây chỉ còn một nút hoặc rỗng, trả về NULL
    if (goc == NULL) {
        return goc;
    }

    return CanBangCay(goc); // Cân bằng lại cây sau khi đã xóa nút
}