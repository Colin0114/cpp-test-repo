#include <stdio.h>
#include <errno.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

// 1. create two tcp sockets
// 2. set socket which bind last with option SOCK_REUSEADDR

// must set SO_REUSEADDR on second bind socket, then will bind success on mac

enum ReuseaddrOpt{
    REUSEADDR_FIRST,
    REUSEADDR_SECOND,
    NO_REUSEADDR
};

void try_bind(int sock, int port, struct sockaddr_in* addr);

int main(){
    int ret = 0;
    int bReuseaddr = 1;     // must be 1 or ture, or setsockopt wont take effect
    int sockGeneric, sockSpecific, firstSock, secondSock;
    struct sockaddr_in serverGeneric, serverSpecific;
    struct sockaddr_in *firstAddr = NULL, *secondAddr = NULL;

    int port = 1118;
    int genetric_first = 1;    
    ReuseaddrOpt ropt = REUSEADDR_SECOND;

    // create sockets and servers
    sockGeneric = socket(AF_INET, SOCK_STREAM, 0);
    sockSpecific = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&serverSpecific, sizeof(serverSpecific));
    bzero(&serverGeneric, sizeof(serverGeneric));
    serverSpecific.sin_family = AF_INET;
    serverSpecific.sin_port = htons(port);
    serverSpecific.sin_addr.s_addr = inet_addr("172.18.66.226"); // change to your ip addr

    serverGeneric.sin_family = AF_INET;
    serverGeneric.sin_port = htons(port);
    serverGeneric.sin_addr.s_addr = inet_addr("0.0.0.0");
    // end create

    // set SO_REUSEADDR for socket to bind
    if (genetric_first){
        firstSock = sockGeneric;
        firstAddr = &serverGeneric;
        secondSock = sockSpecific;
        secondAddr = &serverSpecific;
    }else{
        firstSock = sockSpecific;
        firstAddr = &serverSpecific;
        secondSock = sockGeneric;
        secondAddr = &serverGeneric;
    }
    
    switch(ropt){
        case REUSEADDR_FIRST:
            printf("reuseaddr on first bind socket\n");
            ret = setsockopt(firstSock, SOL_SOCKET, SO_REUSEADDR, (const void*)&bReuseaddr,sizeof(int));
            break;
        case REUSEADDR_SECOND:
            printf("reuseaddr on second bind socket\n");
            ret = setsockopt(secondSock, SOL_SOCKET, SO_REUSEADDR, (const void*)&bReuseaddr,sizeof(int));
            break;
        case NO_REUSEADDR:
            printf("no reuseaddr on any socket\n");
            break;
        default:
            break;
      }

    if( ret == -1){
        printf("setsockopt faild\n");
        return 0;
    }
    // end set SO_REUSEADDR

    // bind
    try_bind(firstSock, port, firstAddr);
    try_bind(secondSock, port, secondAddr);
    // end bind

    return 0;
}

void try_bind(int sock, int port, struct sockaddr_in* addr){
    printf("bind to addr %s:%d\n", inet_ntoa(addr->sin_addr), port);
    int ret = bind(sock, (struct sockaddr*)addr, sizeof(struct sockaddr));
    if (ret == -1){
        printf("bind faild; details: %s\n", strerror(errno));
    }else{
        printf("bind success.\n");
    }
}
