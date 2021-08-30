//
// Created by shenhangke on 2021/8/19.
//
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <string>
#include <Python/Python.h>

int main(int argc,char* args[]){
    int sock= socket(PF_INET,SOCK_STREAM,0);
    assert(sock>0);
    sockaddr_in addr;
    bzero(&addr,sizeof(sockaddr_in));
    addr.sin_family=AF_INET;
    inet_pton(PF_INET,"0.0.0.0",&addr.sin_addr);
    //为什么这里要转换成网络字节序呢？
    addr.sin_port= htons(2230);
    //这里就把sock和地址进行绑定了，后面就使用sock来维持通信？
    int ret= connect(sock,(sockaddr*)&addr,sizeof(sockaddr_in));
    std::string str;
    std::cout<<"please enter the message you want send"<<std::endl;
    std::cin>>str;
    write(sock,str.c_str(), strlen(str.c_str()));
    char buff[255];
    int readNum=read(sock,buff,sizeof(buff));
    std::cout<<"has recv the message,the message is: "<<buff<<std::endl;
    close(sock);
}
