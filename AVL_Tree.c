#include "AVL_Tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int max(int a, int b) { return a > b ? a : b; }

AVLNode* TaoNutAVL(void *DuLieu, void *Khoa) {
    AVLNode *nut = (AVLNode *)malloc(sizeof(AVLNode));
    if (!nut) return NULL;
    nut->DuLieu = DuLieu;
    nut->Khoa = Khoa;
    nut->Cao = 1;
    nut->Trai = nut->Phai = NULL;
    return nut;
}

int ChieuCao(AVLNode *nut) {
    return nut ? nut->Cao : 0;
}

int HeSoCanBang(AVLNode *nut) {
    return nut ? ChieuCao(nut->Trai) - ChieuCao(nut->Phai) : 0;
}

void CapNhatChieuCao(AVLNode *nut) {
    if (nut)
        nut->Cao = 1 + max(ChieuCao(nut->Trai), ChieuCao(nut->Phai));
}

AVLNode* QuayPhai(AVLNode *y) {
    AVLNode *x = y->Trai;
    AVLNode *T2 = x->Phai;
    x->Phai = y;
    y->Trai = T2;
    CapNhatChieuCao(y);
    CapNhatChieuCao(x);
    return x;
}

AVLNode* QuayTrai(AVLNode *x) {
    AVLNode *y = x->Phai;
    AVLNode *T2 = y->Trai;
    y->Trai = x;
    x->Phai = T2;
    CapNhatChieuCao(x);
    CapNhatChieuCao(y);
    return y;
}

AVLNode* ChenAVL(AVLNode *goc, void *DuLieu, void *Khoa, int (*SoSanh)(const void *, const void *)) {
    if (!goc) return TaoNutAVL(DuLieu, Khoa);
    int cmp = SoSanh(Khoa, goc->Khoa);
    if (cmp < 0)
        goc->Trai = ChenAVL(goc->Trai, DuLieu, Khoa, SoSanh);
    else if (cmp > 0)
        goc->Phai = ChenAVL(goc->Phai, DuLieu, Khoa, SoSanh);
    else
        return goc;

    CapNhatChieuCao(goc);

    int cb = HeSoCanBang(goc);
    if (cb > 1 && SoSanh(Khoa, goc->Trai->Khoa) < 0)
        return QuayPhai(goc);
    if (cb < -1 && SoSanh(Khoa, goc->Phai->Khoa) > 0)
        return QuayTrai(goc);
    if (cb > 1 && SoSanh(Khoa, goc->Trai->Khoa) > 0) {
        goc->Trai = QuayTrai(goc->Trai);
        return QuayPhai(goc);
    }
    if (cb < -1 && SoSanh(Khoa, goc->Phai->Khoa) < 0) {
        goc->Phai = QuayPhai(goc->Phai);
        return QuayTrai(goc);
    }
    return goc;
}

AVLNode* TimKiemAVL(AVLNode *goc, const void *Khoa, int (*SoSanh)(const void *, const void *)) {
    if (!goc) return NULL;
    int cmp = SoSanh(Khoa, goc->Khoa);
    if (cmp == 0) return goc;
    if (cmp < 0) return TimKiemAVL(goc->Trai, Khoa, SoSanh);
    else return TimKiemAVL(goc->Phai, Khoa, SoSanh);
}

AVLNode* TimNutNhoNhat(AVLNode *nut) {
    AVLNode *hientai = nut;
    while (hientai && hientai->Trai)
        hientai = hientai->Trai;
    return hientai;
}

AVLNode* XoaAVL(AVLNode *goc, const void *Khoa, int (*SoSanh)(const void *, const void *)) {
    if (!goc) return NULL;
    int cmp = SoSanh(Khoa, goc->Khoa);
    if (cmp < 0)
        goc->Trai = XoaAVL(goc->Trai, Khoa, SoSanh);
    else if (cmp > 0)
        goc->Phai = XoaAVL(goc->Phai, Khoa, SoSanh);
    else {
        if (!goc->Trai || !goc->Phai) {
            AVLNode *tam = goc->Trai ? goc->Trai : goc->Phai;
            free(goc->Khoa);
            free(goc->DuLieu);
            free(goc);
            return tam;
        }
        AVLNode *tam = TimNutNhoNhat(goc->Phai);
        void *tmpKhoa = goc->Khoa;
        void *tmpDuLieu = goc->DuLieu;
        goc->Khoa = tam->Khoa;
        goc->DuLieu = tam->DuLieu;
        tam->Khoa = tmpKhoa;
        tam->DuLieu = tmpDuLieu;
        goc->Phai = XoaAVL(goc->Phai, tam->Khoa, SoSanh);
    }
    CapNhatChieuCao(goc);
    int cb = HeSoCanBang(goc);
    if (cb > 1 && HeSoCanBang(goc->Trai) >= 0)
        return QuayPhai(goc);
    if (cb > 1 && HeSoCanBang(goc->Trai) < 0) {
        goc->Trai = QuayTrai(goc->Trai);
        return QuayPhai(goc);
    }
    if (cb < -1 && HeSoCanBang(goc->Phai) <= 0)
        return QuayTrai(goc);
    if (cb < -1 && HeSoCanBang(goc->Phai) > 0) {
        goc->Phai = QuayPhai(goc->Phai);
        return QuayTrai(goc);
    }
    return goc;
}

void DuyetLNR(AVLNode *goc, void (*XuLy)(void *)) {
    if (!goc) return;
    DuyetLNR(goc->Trai, XuLy);
    XuLy(goc->DuLieu);
    DuyetLNR(goc->Phai, XuLy);
}

void GiaiPhongAVL(AVLNode *goc) {
    if (!goc) return;
    GiaiPhongAVL(goc->Trai);
    GiaiPhongAVL(goc->Phai);
    free(goc->Khoa);
    free(goc->DuLieu);
    free(goc);
}