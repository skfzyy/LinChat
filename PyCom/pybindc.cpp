//
// Created by shenhangke on 2021/8/24.
//

#include "pybindc.h"

int add(int a,int b){
    return a+b;
}

PYBIND11_MODULE(Add_package,m){
    m.doc()="test add function";
    m.def("add",&add,"add two number");
}