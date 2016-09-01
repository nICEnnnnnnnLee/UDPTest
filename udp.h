#ifndef UDP_H
#define UDP_H

#ifndef WIN32
	#include <netinet/in.h>    // for sockaddr_in
	#include <sys/types.h>    // for socket
	#include <sys/socket.h>    // for socket
	#include <unistd.h>     //for close
	#include <arpa/inet.h>  //for inet_addr
	//#include <sys/stat.h>
	//#include <fcntl.h>
    #include <netinet/in.h>
	typedef int SOCKET;
#else
    #include <winsock2.h>
	#include <ws2tcpip.h>
	//#include "stdafx.h"
	#pragma comment(lib,"ws2_32.lib")
	typedef int socklen_t;
#endif


#include <stdio.h>        // for printf
#include <stdlib.h>        // for exit
#include <string.h>        // for bzero

typedef struct{
    char msg[1024];
    int msgLen;
}MsgData;
class udp_conn{
public:
    bool isListen;
    struct sockaddr_in servaddr;
    struct sockaddr_in recvaddr;//存放最后一次接收的数据地址，这个设计没搞好 最好recMsg返回struct dataPacket
public:
    udp_conn();
    ~udp_conn();

    bool bindUDP(int port);
    MsgData recvMsg();
    void sendMsg(char* ip,int port,char msg[]);
    void sendMsg(char* ip,int port,char msg[],int length);
    void closeUDP();

protected:
    SOCKET sockfd;

private:
};

#endif // UDP_H
