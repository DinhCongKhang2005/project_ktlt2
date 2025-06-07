#ifndef CayAvl_H
#define CayAvl_H

#include "Data.h"
#include <stdlib.h>

typedef int (*HamSoSanh)(void*, void*); 
// cmp: hàm so sánh giữa 2 đối tượng, trả về 1 nếu lớn hơn, -1 nếu nhỏ hơn và 0 nếu bằng nhau
// void *duLieu: dữ liệu cần thêm vào cây AVL - tự định nghĩa kiểu dữ liệu

AVLNode* TaoNut(void *duLieu, void *khoa); // Tạo nút mới trong cây AVL
AVLNode* CanBangCay(AVLNode* nut); // Cân bằng lại cây AVL
AVLNode* ChenVaoCayAvl(AVLNode* goc, void *duLieu, void *khoa, HamSoSanh soSanh);
AVLNode* TimKiemCayAvl(AVLNode* goc, void *khoa, HamSoSanh soSanh);
AVLNode* NutGiaTriNhoNhat(AVLNode* nut); // Tìm nút có giá trị nhỏ nhất trong cây con bên trái
AVLNode* XoaKhoiCayAvl(AVLNode* goc, void *khoa, HamSoSanh soSanh); // Xóa nút trong cây AVL

#endif
