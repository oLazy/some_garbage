//
// Created by eric on 29/09/18.
//
#pragma once
#ifndef Z1DAMT_Z1AMT_LIB_H
#define Z1DAMT_Z1AMT_LIB_H

#include <mat22.h>
#include <mat33.h>
#include <matrix22.h>
#include <PekSolver.h>
void cheers();
namespace mt{
    const static double pi = M_PI;
    const static permeability mu0{pi*4.e-7 * henry / meters};
    const static permittivity epsilon0{8.854187817e-12 * farad / meters};
}
#endif //Z1DAMT_Z1AMT_LIB_H
