//
// Created by yejt on 18-4-30.
//
#include "codegen.h"

void autoFreeReg(int beFree, int *contrain) {
    if (isTmpReg(beFree)) {
        if (contrain != NULL && *contrain != beFree) {
            regManager->freeReg(beFree);
        }
    }
}

bool isTmpReg(int r) {
    return r >= 8 && r <= 15;
}