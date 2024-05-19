#include "../include/socket.hpp"
#include <stdio.h>
#include <string.h>

int main() 
{   
    try{
        SocketServer sockServer = SocketServer(SOCK_STREAM, 0, AF_INET, htons(8080), INADDR_ANY);
        sockServer.startTCPServer(); 

        sockServer = SocketServer(SOCK_DGRAM, 0, AF_INET, htons(8080), INADDR_ANY);
        sockServer.startUDPServer();    
    } catch(...){
        std::cout << "Error";
        throw;
    }


	return 0;
}
