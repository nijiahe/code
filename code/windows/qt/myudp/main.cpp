#include <iostream>
#include "udp.h"


using namespace std;

int main(int argc,char* argv[])
{
    if( argc ==2 )
    {

    socket_send(argv[1]);
     }
     else if( argc == 1)
    {
        socket_rec();
    }
    else
    {
        printf("无当前指令\n");
    }
    return 0;
}

