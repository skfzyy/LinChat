#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

static bool stop= false;
static void handle_term(int sig){
    stop= false;
}
int main(int argc,char* argv[]) {
    signal(SIGTERM,handle_term);
    const char* ip="0.0.0.0";
    int port= atoi("2230");

    int sock= socket(PF_INET/*using IPv4*/,SOCK_STREAM,0);
    assert(sock>=0);

    sockaddr_in address;
    bzero(&address,sizeof(sockaddr_in));
    //AF_INET和PF_INET是相同的值，只是一个表示协议，一个表示地址protocol or address
    address.sin_family=AF_INET;
    inet_pton(AF_INET,ip,&address.sin_addr);
    address.sin_port= htons(port);

    int ret= bind(sock,(sockaddr*)&address,sizeof(sockaddr_in));
    assert(ret!=-1);
    ret= listen(sock,5);
    assert(ret!=-1);
    while(!stop){
        unsigned int sin_size=sizeof(sockaddr_in);
        int new_fd=accept(sock,(sockaddr*)&address,&sin_size);
        assert(new_fd!=-1);
        if(!fork()){
            std::cout<<"generate a new process to handle request"<<std::endl;
//            printf("create new thread ")
            int numberBytes;
            char buff[256];
            memset(buff,0,sizeof(buff));
            if (numberBytes= recv(new_fd,buff,sizeof(buff),0)!=-1){
                std::cout<<"the recv message is: "<<buff<<std::endl;
                std::string sendStr="recv the info";
                send(new_fd,sendStr.c_str(), strlen(sendStr.c_str()),0);
                close(new_fd);
            }
        }
    }
    close(sock);
    return 0;
}
