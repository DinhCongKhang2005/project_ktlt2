#ifndef AVL_TREE_H
#define AVL_TREE_H

typedef struct AVLNode {
    void *DuLieu;
    void *Khoa;
    int Cao;
    struct AVLNode *Trai, *Phai;
} AVLNode;

AVLNode* ChenAVL(AVLNode *goc, void *DuLieu, void *Khoa, int (*SoSanh)(const void *, const void *));
AVLNode* TimKiemAVL(AVLNode *goc, const void *Khoa, int (*SoSanh)(const void *, const void *));
AVLNode* XoaAVL(AVLNode *goc, const void *Khoa, int (*SoSanh)(const void *, const void *));
void DuyetLNR(AVLNode *goc, void (*XuLy)(void *));
void GiaiPhongAVL(AVLNode *goc);

#endif