#define _WIN32_WINNT 0x501
#define BUF_SIZE 512
#define MAX_THREAD 100
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
using namespace std;

#pragma comment(lib,"Ws2_32.lib")
SOCKET CliSock;
ofstream fout ("C:\\9817243.txt");

void prga(unsigned char* tmpkey,int size,unsigned char* keystream)
{

  //  keystream=(char*)malloc(sizeof(char)*size);
    int i=0,j=0,index=0;
   unsigned char tmp;
    for(int x=0;x<size;x++)
    {
        i=(i+1)%256;
        j=(j+tmpkey[i])%256;
        tmp=tmpkey[i];  tmpkey[i]=tmpkey[j];    tmpkey[j]=tmp;
        keystream[x]=tmpkey[(tmpkey[i]+tmpkey[j])%256];
    }
    printf("[");
    for(int i=0;i<size;i++)printf(" %x ",keystream[i]);
    printf("]");
    return;
}

void ksa(unsigned char* key,unsigned char*s,int lenth)
{

    for(int i=0;i<256;i++)
    {
        s[i]=i;
    }
    int j=0;
    for(int i=0;i<256;i++)
    {
        j=(j+s[i]+key[i%lenth])%256;
        unsigned char tmp=s[i];
        s[i]=s[j];
        s[j]=tmp;
    }
    return;
}

void rc4(char* t,char* k)
{
    unsigned char* text=(unsigned char*)t;
    unsigned char* key=(unsigned char*)k;
    unsigned char tmpkey[256];
    ksa(key,tmpkey,(int)strlen(t));
    unsigned char keystream[(int)strlen(t)];
    prga(tmpkey,strlen(t),keystream);
   // printf("====%x====",)
    for(int i=0;i<strlen(t);i++)
    {
        text[i]=keystream[i]^text[i];
    }

    return;

}


DWORD WINAPI handle(LPVOID lpParam)
{
     int reclen = BUF_SIZE;
     char rebuf[BUF_SIZE];


        ZeroMemory(&rebuf,sizeof(rebuf));
        int result;
        result=recv(CliSock,rebuf,reclen,0);
        if(result >0)
        {
           // cout<<"rec size:"<<strlen(rebuf)<< endl;
            rc4(rebuf,"hackerneverdie");
            cout << rebuf<<" " ;
            fout <<rebuf<<" "<<flush;
            //cout << result << endl;
        }

       // strcat(rebuf,",received!!\0");
        //char *msg="testing\0";
        //cout << "msg send :" << rebuf <<endl;
		//cout << "size" << strlen(rebuf) << endl;
//cout<<"!!3"<<endl;
        //result = send(CliSock,rebuf,(int)strlen(rebuf),0);
//cout<<"!!4"<<endl;
       /* if(result==SOCKET_ERROR)
        {
      //      cout<<"!!1000"<<endl;
            cout << "send fail: " << WSAGetLastError() << endl;
            closesocket(CliSock);
            WSACleanup();
            //return 1;
        }*/
//cout<<"!!5"<<endl;
   // }

        //Sleep(10000);
       /* cout << "send finished"<<endl;
        result = shutdown(CliSock,SD_RECEIVE);
        if(result==SOCKET_ERROR)
        {
            cout << "shutdown fail: " << WSAGetLastError() << endl;
            closesocket(CliSock);
            WSACleanup();
            //return 1;
        }*/
       // cout<<"haha"<<endl;
		return 0;
}

int main(){
    WSADATA wsdata;
    char* port = "11111";
    int result = WSAStartup(MAKEWORD(2,2),&wsdata);
    if(result !=0 )
    {
        cout << "WinSock Startup fail: " << result << endl;
    }
//printf("е\пр");
    struct addrinfo *adrinfo=NULL,*ptr =NULL,hints;
    ZeroMemory(&hints,sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    result = getaddrinfo(NULL,port,&hints,&adrinfo);
    if(result!=0)
    {
        cout << "getaddrinfo failed: " << result << endl;
        WSACleanup();
        return 1;
    }

    SOCKET ServerSock = INVALID_SOCKET;

    ServerSock = socket(adrinfo->ai_family,adrinfo->ai_socktype,adrinfo->ai_protocol);

    if(ServerSock==INVALID_SOCKET)
    {
            cout << "socket open fail: " << WSAGetLastError() << endl;
            freeaddrinfo(adrinfo);
            WSACleanup();
            return 1;
    }

    result = bind(ServerSock,adrinfo->ai_addr,(int)adrinfo->ai_addrlen);
    if(result==SOCKET_ERROR){
            cout << "bind fail: " << WSAGetLastError() << endl;
            freeaddrinfo(adrinfo);
            closesocket(ServerSock);
            WSACleanup();
            return 1;
    }
    freeaddrinfo(adrinfo);

    result = listen(ServerSock,SOMAXCONN);

    if(result==SOCKET_ERROR)
    {
            cout << "LISTEN fail: " << WSAGetLastError() << endl;
            closesocket(ServerSock);
            WSACleanup();
            return 1;
    }

    CliSock=INVALID_SOCKET;
    while(true){
       // cout<<"sever"<<endl;
        CliSock = accept(ServerSock,NULL,NULL);
       // cout << " accept connection" << endl;
        if(CliSock == INVALID_SOCKET)
        {
            cout << "accept fail: " << WSAGetLastError() << endl;
            closesocket(ServerSock);
            WSACleanup();
            return 1;
        }
        //start send
        HANDLE hand = CreateThread(NULL,0,handle,NULL,0,NULL);
        //handle();
		WaitForSingleObject(hand,INFINITE);
        //cout <<"connect fiinshed "<<endl;
    }
    closesocket(CliSock);
    WSACleanup();
    return 0;
}
