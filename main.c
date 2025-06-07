#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "Data.h"
#include "AVL_Tree.h"
#include "Library_Service.h"
#include "Member.h"
#include "Book.h"
#include "Borrowing.h"
#include "Queue.h"


int main() {
    // Tải dữ liệu lên bảng băm
    DocThanhVienTuFile("data/member.csv");
    DocSachTuFile("data/book.csv");
    DocPhieuMuonTuFile("data/borrowing.csv");
    DocHangDoiTuFile("data/queue.csv");
    printf("Tai du lieu thanh cong\n");

    // Chạy giao diện
    GiaoDienThuVien();

    // Lưu dữ liệu từ bảng băm về file .csv
    LuuTatCaHangDoiVaoFile("data/queue.csv");
    LuuPhieuMuonVaoFile("data/borrowing.csv");
    LuuSachVaoFile("data/book.csv");
    LuuThanhVienVaoFile("data/member.csv");
    printf("Luu du lieu thanh cong\n");
    return 0;
}