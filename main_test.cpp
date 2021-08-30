//
// Created by shenhangke on 2021/8/21.
//
#include "iostream"
#include <unistd.h>
int main(int argc,char* args[]){
    int ret=fork();
    //fork之后，子进程会执行和父进行一样的指令
    if(ret==0){
        std::cout<<"this is child process"<<std::endl;
    }else{
        std::cout<<"this is parent process"<<std::endl;
    }
    std::cout<<"this is common out"<<std::endl;
}

