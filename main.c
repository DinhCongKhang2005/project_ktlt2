#include "Menu.h"
#include "Book.h"
#include "Member.h"
#include "Transaction.h"
#include "WaitingList.h"
#include "Utility.h"
#include <stdio.h>

int main() {
    DocDuLieuSach("sach.csv");
    DocDuLieuBanDoc("bandoc.csv");
    DocDuLieuGiaoDich("giaodich.csv");
    DocDanhSachCho("danhsachcho.csv");

    ChayMenuChinh();

    GhiDuLieuSach("sach.csv");
    GhiDuLieuBanDoc("bandoc.csv");
    GhiDuLieuGiaoDich("giaodich.csv");
    GhiDanhSachCho("danhsachcho.csv");

    return 0;
}