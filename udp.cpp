#include   "stdafx.h"
#include "udp.h"
#include "iostream.h"
udp_conn::udp_conn(){}

udp_conn::~udp_conn(){}

bool udp_conn::bindUDP(int port){
	#ifdef WIN32
		//≥ı ºªØWSA
		WORD sockVersion = MAKEWORD(2,2);
		WSADATA wsaData;
		WSAStartup(sockVersion, &wsaData);
	#endif
    //
	memset(&servaddr,0,sizeof(servaddr));
    
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	//servaddr.sin_addr.S_un.S_addr = INADDR_ANY;
    servaddr.sin_port = htons(port);
    //
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);


    if(-1==bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr)))
        return false;
    else{
        struct timeval tv;
        tv.tv_sec=1;    tv.tv_usec=0;
        setsockopt(sockfd,SOL_SOCKET,SO_RCVTIMEO,(char*)&tv,sizeof(tv));
        isListen=true;
        return true;
    }
}

MsgData udp_conn::recvMsg(){
    //ssize_t recvfrom(int s, void *buf, size_t len, int flags, struct sockaddr *from,  socklen_t *fromlen);
    //recvfrom(sockfd,msg,sizeof(msg),0,null,null);
    //recv(sockfd, msg, sizeof(msg), MSG_WAITALL);
    //int len=recv(sockfd, msg, sizeof(msg), 0);
    MsgData data;
	data.msgLen=0;

    int addr_len = sizeof(sockaddr_in);
    data.msgLen=recvfrom(sockfd, data.msg, sizeof(data.msg),0,(sockaddr *)&recvaddr,&addr_len);

    data.msg[data.msgLen]='\0';
    return data;
}

void udp_conn::sendMsg(char* ip,int port,char msg[]){
    
    struct sockaddr_in dest_addr;
	memset(&dest_addr,0,sizeof(dest_addr));
    //bzero(&dest_addr,sizeof(dest_addr));
    dest_addr.sin_family=AF_INET;
    dest_addr.sin_addr.s_addr=inet_addr(ip);//
    dest_addr.sin_port=htons(port);
    sendto(sockfd,msg,strlen(msg),0,(struct sockaddr *)&dest_addr,sizeof(dest_addr));
}

void udp_conn::sendMsg(char* ip,int port,char msg[],int length){
    
    struct sockaddr_in dest_addr;
	memset(&dest_addr,0,sizeof(dest_addr));
    //bzero(&dest_addr,sizeof(dest_addr));
    dest_addr.sin_family=AF_INET;
    dest_addr.sin_addr.s_addr=inet_addr(ip);//
    dest_addr.sin_port=htons(port);
    sendto(sockfd,msg,length,0,(struct sockaddr *)&dest_addr,sizeof(dest_addr));
}

void udp_conn::closeUDP(){
    isListen=false;
	#ifndef WIN32
		close(sockfd);
	#else
		closesocket(sockfd);
		WSACleanup();
	#endif
}