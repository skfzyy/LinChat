//
// Created by shenhangke on 2021/8/24.
//

#ifndef LINCHAT_PYBINDC_H
#define LINCHAT_PYBINDC_H

#include <pybind11/pybind11.h>

namespace py=pybind11;

class pybindc {
public:
    int a,b;
private:
    int c,d;
public:
    int add();
};


#endif //LINCHAT_PYBINDC_H
